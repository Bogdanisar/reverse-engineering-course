#include <set>
#include <sstream>

#include "decrypt.cpp"


const char * const InitialTaskFile = "task/input/_data 8 bogdan.burcea.json";
const char * const ShiftedTaskFile = "task/shifted/data_shifted_0.json";
const char * const TaskDecryptedFileNoExt = "task/output/data_decrypted";
const char * const TaskShiftedFileNoExt = "task/shifted/data_shifted_";
const char * const TaskCustomBinaryJson = "task/custom_binary_json.json";


void ShiftFile() {
    for (int numLeftShift = 0; numLeftShift <= 7; ++numLeftShift) {
        stringstream ss;
        ss << numLeftShift;

        string outputFile = TaskShiftedFileNoExt;
        outputFile += ss.str();
        outputFile += ".json";

        shiftBitsInBinaryFile(InitialTaskFile, outputFile.c_str(), numLeftShift);
        pn;

        for (int i = 0; i < 4; ++i) {
            int byte = getByteAtIndex(outputFile.c_str(), i);
            pv(i); pv(byte); pn;
        }
        pn;
    }
}

void GetFrequencyOfWholeFile(const char * const file) {
    auto freqPairs = computeByteFrequencyForFile(file, 0, 1);
    printFrequency(freqPairs, 0, 1, 0);
}

void GetFrequencyOfFile(const char * const file) {
    pv(file); pn;

    int fileSize = getFileSize(file);
    pv(fileSize); pn;

    for (int keyLength = 5; keyLength <= 9; ++keyLength) {
        for (int start = 0; start < keyLength; ++start) {
            auto freqPairs = computeByteFrequencyForFile(file, start, keyLength);
            printFrequency(freqPairs, start, keyLength, 0, 4);
        }
    }
}

void GetPossibleFirstBytesOfFile() {
    for (int bytePosition = 0; bytePosition < 4; ++bytePosition) {
        unsigned char encryptedByte = getByteAtIndex(ShiftedTaskFile, bytePosition);

        map<unsigned char, unsigned char> possibleDecryptedBytesToXorByte;
        for (int xorByte = 0; xorByte < 256; ++xorByte) {
            if (isAcceptableXorByte(xorByte)) {
                unsigned char decryptedByte = encryptedByte ^ xorByte;
                possibleDecryptedBytesToXorByte[decryptedByte] = xorByte;
            }
        }

        for (auto p : possibleDecryptedBytesToXorByte) {
            unsigned char possibleDecryptedByte = p.first;
            unsigned char xorByte = p.second;

            if (isprint(possibleDecryptedByte)) {
                pv(bytePosition); pv(xorByte); pv((int)possibleDecryptedByte); pv(possibleDecryptedByte); pn;
            } else {
                pv(bytePosition); pv(xorByte); pv((int)possibleDecryptedByte); pn;
            }
        }
        pn;
    }
}

void TryAnalysisOnFirstByte() {
    int start = 0, step = 5;

    unsigned char encryptedByte = getByteAtIndex(ShiftedTaskFile, start);
    auto freqPairs = computeByteFrequencyForFile(ShiftedTaskFile, start, step);

    vector<unsigned char> targetBytes = {'{', '[', ' ', '\t', '\n', '\v', '\f', '\r', '\0', '\"'};
    for (unsigned char targetByte : targetBytes) {
        unsigned char xorByte = encryptedByte ^ targetByte;
        if (!isAcceptableXorByte(xorByte)) {
            printf("Bad xor byte: %hhu\n\n", xorByte);
            continue;
        }

        pv((int)encryptedByte); pv(targetByte); pv(xorByte); pn;
        printFrequency(freqPairs, start, step, xorByte, 30);
        pn;
    }
}

void TestDecrypt() {
    string dest = string(TaskDecryptedFileNoExt) + "_test.json";

    // string key = "C23456";
    // string key = "ZTZTZT";
    string key = "ZQCsyxHT"; // <----. But it only decrypts some continuous parts of the file correctly and some others are junk??

    pv(key); pn;
    vector<unsigned char> xorKey(key.begin(), key.end());

    decryptPerByte(InitialTaskFile, dest.c_str(), xorKey, false); // don't ignore any bytes.
    // decryptPerByte(InitialTaskFile, dest.c_str(), xorKey, true); // ignore bad bytes.

    // GetFrequencyOfWholeFile(dest.c_str());
}

void TestWriteBytesToFile() {
    vector<unsigned char> bytes;

    // string json = "{\"message\": \"\v'asd'\v\"}";
    string json = "{ \"key\": \"színek\" }";

    for (char c : json) {
        bytes.push_back(c);
    }

    FILE *fout = fopen(TaskCustomBinaryJson, "wb");
    assert(fout);

    for (unsigned char b : bytes) {
        assert( fwrite(&b, sizeof(unsigned char), 1, fout) == 1 );
    }

    assert( fclose(fout) == 0 );
}

void Solve() {
    vector<unsigned char> badBytes;

    // for (int i = 0; i < 32; ++i) {
    //     if (9 <= i && i <= 13) {
    //         // 9 -> Horizontal tab (\t) -> OK.
    //         // 10 -> Newline (\n) -> OK.
    //         // 11 -> Vertical Tab (\v) -> OK.
    //         // 12 -> Feed (\f) -> OK.
    //         // 13 -> Carriage Return (\r) -> OK.
    //         continue;
    //     }

    //     badBytes.push_back(i);
    // }

    // badBytes = {};
    // // for (int i = 176; i <= 191; ++i) {
    // for (int i = 176; i <= 207; ++i) {
    // // for (int i = 176; i <= 223; ++i) {
    //     badBytes.push_back(i);
    // }

    // badBytes = {1, 2, 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    // badBytes = {127};
    // badBytes = {0};
    // badBytes = {176, 177, 178};
    badBytes = {130, 131, 136};


    // const string targetBytes = "\":, \n{}[]aeiou";
    // const string targetBytes = "\":, \n{}[]";
    // const string targetBytes = "\":,{}[]";
    // const string targetBytes = "\":, \n{}[]aeiou0123456789";
    // const string targetBytes = "\":,{}";
    // const string targetBytes = "\":,";
    // const string targetBytes = "\":, \n{}";
    // const string targetBytes = "\":, \r\n{}";
    // const string targetBytes = "\":, \n{}[]aeiouAEIOU";
    // const string targetBytes = "\":, \n{}[]rtaeiou";
    // const string targetBytes = "\":, \n{}[]rt";
    // const string targetBytes = "\":, \n{}[]rt/";
    // const string targetBytes = "\":, \n{}[]rt/htp";
    // const vector<unsigned char> targetBytes = {'\0', '\n', '\"', ':', ',', ' ', '{', '}', '[', ']', 'a', 'e', 'i', 'o', 'u'};
    // const vector<unsigned char> targetBytes = {'\0', '\"', ':', ',', '{', '}', '[', ']'};
    // const vector<unsigned char> targetBytes = {'\0', '\"', ':', ',', '{', '}'};
    // const vector<unsigned char> targetBytes = {'\n', '\"', ':', ',', ' ', '{', '}', '[', ']', 'a', 'e', 'i', 'o', 'u'};
    // const vector<unsigned char> targetBytes = {'a', 'e', 'i', 'o', 'u'};
    const vector<unsigned char> targetBytes = {' '};
    // const vector<unsigned char> targetBytes = {' ', '/', ':', 'h', 't', 'p', 's'};
    // const vector<unsigned char> targetBytes = {' ', '/', ':', 'h', 't', 'p', 's', 'w'};
    // const vector<unsigned char> targetBytes = {' ', '/', ':', 'h', 't', 'p', 's', 'w', '?', '&'};
    // const vector<unsigned char> targetBytes = {' ', '/', ':', 'h', 't', 'p', 's', 'w', '?', 'g', 'i', 't'};


    // crackEncryptedFileGivenKeyLength(TaskFile, TaskDecryptedFileNoExt, 6, targetBytes);

    // for (int keyLength = 5; keyLength <= 9; ++keyLength) {
    for (int keyLength = 4; keyLength <= 10; ++keyLength) {
        crackEncryptedFileGivenKeyLength(ShiftedTaskFile, TaskDecryptedFileNoExt, keyLength, badBytes, targetBytes);
    }
}

int main() {
    // ShiftFile();
    // GetFrequencyOfBaseFile();
    // GetPossibleFirstBytesOfFile();
    // TryAnalysisOnFirstByte();
    TestDecrypt();
    // TestWriteBytesToFile();
    // Solve();

    return 0;
}

