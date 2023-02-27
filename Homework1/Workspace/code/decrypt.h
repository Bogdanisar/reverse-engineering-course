#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <sys/stat.h>

#define pv(x) do { std::cout<<#x<<" = "<<(x)<<"; ";std::cout.flush(); } while (0)
#define pn do { std::cout<<std::endl; } while (0)

using namespace std;


// The xor key contains only lowercase and uppercase letters (see task description).
bool isAcceptableXorByte(unsigned char xorByte) {
    return
           ('a' <= xorByte && xorByte <= 'z')
        || ('A' <= xorByte && xorByte <= 'Z')
        // || ('0' <= xorByte && xorByte <= '0')
    ;
}

bool charIsPrintableAscii(unsigned char uc) {
    return (uc < 128) && (isprint(uc) || isspace(uc));
}

void decryptPerByte(const char *infile, const char *outfile, const vector<unsigned char>& xorKey, bool ignoreBadChar = false) {
    FILE *fin = fopen(infile, "rb");
    FILE *fout = fopen(outfile, "wb");
    assert(fin && fout);

    unsigned char uc;
    int idx = 0;
    while (fread(&uc, sizeof(uc), 1, fin) == 1) {
        uc = (uc ^ xorKey[idx++ % xorKey.size()]);

        if (charIsPrintableAscii(uc) || !ignoreBadChar) {
           assert(fwrite(&uc, sizeof(uc), 1, fout) == 1);
        }
    }

    assert( fclose(fin) == 0 );
    assert( fclose(fout) == 0 );
}


unsigned long long getFileSize(const char *file) {
    struct stat st;
    stat(file, &st);
    unsigned long long size = st.st_size;
    printf("Size of file '%s': %llu\n", file, size);

    return size;
}

unsigned char getByteAtIndex(const char *file, int index) {
    FILE *fin = fopen(file, "rb");
    assert(fin);

    assert( fseek(fin, index, SEEK_SET) == 0 );
    unsigned char uc;
    assert( fread(&uc, sizeof(uc), 1, fin) == 1 );

    assert( fclose(fin) == 0 );

    return uc;
}

void shiftBitsInBinaryFile(const char * const input, const char * const output, const int nBitShift) {
    // printf("test\n"); fflush(stdout);

    const unsigned long long maxInputBitSize = 20'000'000;
    unsigned long long inputByteSize = getFileSize(input);
    unsigned long long inputBitSize = inputByteSize * 8;
    assert(inputBitSize < maxInputBitSize);

    bitset<maxInputBitSize> bits;

    FILE *fin = fopen(input, "rb");
    assert(fin);

    unsigned char byte;
    int i = 0;
    while (fread(&byte, sizeof(byte), 1, fin) == 1) {
        for (int b = 7; b >= 0; --b) {
            int currBit = ((byte >> b) & 1);
            bits.set(i++, currBit);
        }
    }
    assert( fclose(fin) == 0 );
    assert(i == inputBitSize);


    // It's a right shift because bitset positions start from the right.
    bits >>= nBitShift;


    // Write it.
    FILE *fout = fopen(output, "wb");
    assert(fout);

    int numLostBytes = (nBitShift + 7) / 8;
    pv(nBitShift); pv(numLostBytes); pn;
    printf("bits:");
    for (int k = 0; k < 32; ++k) {
        if (k % 8 == 0) {
            printf(" ");
        }
        printf("%i", (int)bits.test(k));
    }
    pn;

    i = 0;
    for (int byteIdx = 1; byteIdx <= inputByteSize - numLostBytes; ++byteIdx) {
        unsigned char currentByte = 0;
        for (int bitIdx = 7; bitIdx >= 0; --bitIdx) {
            int currentBit = bits.test(i++);
            currentByte |= (currentBit << bitIdx);
        }
        assert( fwrite(&currentByte, sizeof(currentByte), 1, fout) == 1 );
    }
    assert( fclose(fout) == 0 );
}

vector<pair<int,int>> computeByteFrequencyForFile(const char * const file, int start, int step) {
    vector<int> freq(256, 0);

    FILE *fin = fopen(file, "rb");
    assert(fin);

    assert( fseek(fin, start, SEEK_SET) == 0 );

    unsigned char uc;
    while (fread(&uc, sizeof(uc), 1, fin) == 1) {
        freq[uc] += 1;

        int ret = fseek(fin, step - 1, SEEK_CUR);
        if (ret != 0) {
            break;
        }
    }

    assert( fclose(fin) == 0 );

    vector<pair<int,int>> freqPairs;
    for (int i = 0; i < 256; ++i) {
        freqPairs.push_back({i,freq[i]});
    }

    sort(freqPairs.begin(), freqPairs.end(), [] (const auto& p1, const auto& p2) -> bool {
        if (p1.second == p2.second) {
            return p1.first < p2.first;
        }
        return p1.second > p2.second;
    });

    return freqPairs;
}

void printFrequency(const vector<pair<int,int>>& freqPairs, int start, int step, unsigned char xorByte, int limit = -1) {
    pv(start); pv(step); pv((int)xorByte); pn;

    int i = 0;
    for (auto iter = freqPairs.begin(); iter != freqPairs.end(); ++iter) {
        unsigned char byte = iter->first;
        int freq = iter->second;

        // if (freq == 0) {
        //     break;
        // }

        if (i == limit) {
            break;
        }

        byte ^= xorByte;
        if (isprint(byte)) {
            printf("[%3i] - freq('%c') = %i\n", i, (char)byte, freq);
        }
        else {
            printf("[%3i] - freq(%3hhu) = %i\n", i, byte, freq);
        }

        ++i;
    }
}

// Given the xorByte and the frequency array, we want to find the minimum index idx such that
// targetBytes is included in freqPairs[0...idx].first.
int getMinimumFreqIndexForXorByte(const vector<pair<int,int>>& freqPairs, const vector<unsigned char>& targetBytes, unsigned char xorByte) {
    int ans = -1;

    for (unsigned char targetByte : targetBytes) {
        for (int idx = 0; idx < 256; ++idx) {
            int currentChar = freqPairs[idx].first ^ xorByte;
            if (targetByte == currentChar) {
                ans = max(ans, idx);
            }
        }
    }

    return ans;
}

bool xorByteDecryptionHasBadBytes(const vector<pair<int,int>>& freqPairs, const vector<unsigned char>& badBytes, unsigned char xorByte) {

    for (unsigned char badByte : badBytes) {
        for (int idx = 0; idx < 256; ++idx) {
            int currentChar = freqPairs[idx].first ^ xorByte;
            int currentFreq = freqPairs[idx].second;

            if (badByte == currentChar && currentFreq != 0) { // this should be what we want but it doesn't work :/ on the task file.
            // if (badByte == currentChar && currentFreq > 100) {
                return true;
            }
        }
    }

    return false;
}

/** Look for the xorByte that has the target chars as close as possible to the most frequent bytes found in the decrypyed file.
 *  Also, eliminate any xorByte in whose decrypted file we would find characters we shouldn't find like '\0'.
 */
pair<int,unsigned char> getXorByteWithMinimumFreqIndex(const vector<pair<int,int>>& freqPairs,
                                                       const vector<unsigned char>& badBytes,
                                                       const vector<unsigned char>& targetBytes) {
    int minIndex = 300;
    unsigned char xorByteWithMinIndex = -1;

    auto checkXorByte = [&](unsigned char xorByte) -> void {
        if (xorByteDecryptionHasBadBytes(freqPairs, badBytes, xorByte)) {
            // printf("bad xorByte: %hhu\n", xorByte);
            return;
        }

        int minIndexForThisXorByte = getMinimumFreqIndexForXorByte(freqPairs, targetBytes, xorByte);
        // pv(xorByte); pv(minIndexForThisXorByte); pn;

        if (minIndex > minIndexForThisXorByte) {
            minIndex = minIndexForThisXorByte;
            xorByteWithMinIndex = xorByte;
        }
    };

    for (int xorByte = 0; xorByte < 256; ++xorByte) {
        if (isAcceptableXorByte(xorByte)) {
            checkXorByte(xorByte);
        }
    }

    return {minIndex, xorByteWithMinIndex};
}

void crackEncryptedFileGivenKeyLength(const char * const encFile,
                                      const char * const crackedFileNoExt,
                                      int keyLength,
                                      const vector<unsigned char>& badBytes,
                                      const vector<unsigned char>& targetBytes) {
    vector<unsigned char> xorKeySolution;

    for (int start = 0; start < keyLength; ++start) {
        auto freqPairs = computeByteFrequencyForFile(encFile, start, keyLength);
        // printFrequency(freqPairs, start, keyLength, 0, 25); pn; pn;

        pair<int,int> pairMinFreqIdxAndXorByte = getXorByteWithMinimumFreqIndex(freqPairs, badBytes, targetBytes);
        int minFreqIdx = pairMinFreqIdxAndXorByte.first;
        unsigned char xorByte = pairMinFreqIdxAndXorByte.second;

        // pv(keyLength); pv(start); pv(minFreqIdx); pv(xorByte); pv((char)xorByte); pn;
        // printFrequency(freqPairs, start, keyLength, xorByte, 30);
        // pn; pn;

        xorKeySolution.push_back(xorByte);
    }

    pv(keyLength);
    printf("xorKeySolution: ");
    for (unsigned char uc : xorKeySolution) {
        printf("[%hhu]", uc);
    }
    printf(" - ");
    for (unsigned char uc : xorKeySolution) {
        printf("%c", (char)uc);
    }
    printf("\n");

    stringstream ss;
    ss << keyLength;

    string crackedFilePathCurr = crackedFileNoExt;
    crackedFilePathCurr += '_';
    crackedFilePathCurr += ss.str();
    crackedFilePathCurr += ".json";

    decryptPerByte(encFile, crackedFilePathCurr.c_str(), xorKeySolution);

    getByteAtIndex(crackedFilePathCurr.c_str(), 0);
}
