#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <vector>

#define pv(x) std::cout<<#x<<" = "<<(x)<<"; ";std::cout.flush()
#define pn std::cout<<std::endl

using namespace std;


unsigned int getFileSize(const char *const file) {
    struct stat st;
    stat(file, &st);
    return st.st_size;
}

string readFileBytes(const char * const file) {
    unsigned int inputFileSize = getFileSize(file);
    char *allInputBytes = (char*)calloc(inputFileSize, sizeof(char));
    assert(allInputBytes != NULL);

    FILE *fin = fopen(file, "rb");
    assert(fin != NULL);

    size_t bytesRead = fread(allInputBytes, sizeof(char), inputFileSize, fin);
    assert((unsigned int)bytesRead == inputFileSize);

    assert(fclose(fin) == 0);

    string ret(allInputBytes, inputFileSize);
    free(allInputBytes);
    return ret;
}

char decryptByte(char encryptedByte, int randValue) {
    vector<char> foundBytes;
    for (int possibleByte = -128; possibleByte <= 127; ++possibleByte) {
        if ((char)(possibleByte + randValue) == encryptedByte) {
            foundBytes.push_back(possibleByte);
        }
    }

    assert(foundBytes.size() == 1);
    return foundBytes[0];
}

void writeBytesToFile(const string& bytes, const string& file) {
    FILE *fout = fopen(file.c_str(), "wb");
    assert(fout != NULL);

    size_t bytesWritten = fwrite(bytes.c_str(), sizeof(char), bytes.size(), fout);
    assert(bytesWritten == bytes.size());

    assert(fclose(fout) == 0);
}

void decryptFile(const char * const inputFile, unsigned int seed) {
    unsigned int inputFileSize = getFileSize(inputFile);
    pv(inputFileSize); pn;

    string allInputBytes = readFileBytes(inputFile);
    assert((unsigned int)allInputBytes.size() == inputFileSize);

    string token = "fmi_re_course";
    size_t tokenStartIndex = allInputBytes.rfind(token);
    assert(tokenStartIndex != string::npos);
    size_t tokenEndIndex = tokenStartIndex + token.size();

    string encryptedFileContents = allInputBytes.substr(0, tokenStartIndex);
    string encryptedFileName = allInputBytes.substr(tokenEndIndex);

    srand(seed);
    string decryptedFileContents;
    for (char encryptedByte : encryptedFileContents) {
        int randValue = rand();
        decryptedFileContents += decryptByte(encryptedByte, randValue);
    }
    // pv(decryptedFileContents.substr(0, 10)); pn;

    string decryptedFileName;
    for (char encryptedByte : encryptedFileName) {
        int randValue = rand();
        decryptedFileName += decryptByte(encryptedByte, randValue);
    }
    decryptedFileName = "decrypted/" + decryptedFileName;
    pv(decryptedFileName); pn;

    system("mkdir ./decrypted");

    reverse(decryptedFileContents.begin(), decryptedFileContents.end());
    writeBytesToFile(decryptedFileContents, decryptedFileName);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: '%s' inputFile seed\n", argv[0]);
        exit(-1);
    }

    const char * const inputFile = argv[1];
    unsigned int seed;
    sscanf(argv[2], "%u", &seed);

    pv(inputFile); pn;
    pv(seed); pn;

    decryptFile(inputFile, seed);

    return 0;
}
