#include "decrypt.h"


const char * const JsonSampleLargeInputFile = "input/jsonSample_input2.json";
const char * const JsonSampleLargeOutputFile = "temp/jsonSample_output.json";
const char * const JsonSampleLargeOutputDecryptedFile = "temp/jsonSample_output_decrypted.json";
const char * const JsonSampleLargeOutputDecryptedFileNoExt = "temp/jsonSample_output_decrypted";


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

void EncryptFile(const string& input, const string& output) {
    const string key = "MySecKey";
    vector<unsigned char> xorKey(key.begin(), key.end());

    // Encryption and decryption are the same.
    decryptPerByte(input.c_str(), output.c_str(), xorKey);
}

void Solve() {
    vector<unsigned char> badBytes;
    for (int i = 1; i < 32; ++i) {
        if (9 <= i && i <= 13) {
            // 9 -> Horizontal tab (\t) -> OK.
            // 10 -> Newline (\n) -> OK.
            // 11 -> Vertical Tab (\v) -> OK.
            // 12 -> Feed (\f) -> OK.
            // 13 -> Carriage Return (\r) -> OK.
            continue;
        }

        badBytes.push_back(i);
    }

    // badBytes = {127};

    // const vector<unsigned char> targetChars = {'\"', ':', ',', '\n', '{', '}', 'a', 'e', 'i', 'o', 'u'};
    // const vector<unsigned char> targetChars = {'\0', '\"', ':', ',', '\n', '{', '}', 'a', 'e', 'i', 'o', 'u'};
    // const vector<unsigned char> targetChars = {'\0'};
    const vector<unsigned char> targetChars = {'{', '\n', ' ', ',', 'k', 'e', 'y', '"', ':', 's', 'z', 'n', 'e', 'k', '}'};
    // const vector<unsigned char> targetChars = {'{', '\n', ' ', ',', 'k', 'e', 'y', '"', ':', 's', 'z', 'n', 'e', 'k', '}',
    //                                            '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // crackEncryptedFileGivenKeyLength(JsonSampleLargeOutputFile, JsonSampleLargeOutputDecryptedFileNoExt, 8, badBytes, targetChars);

    for (int keyLength = 5; keyLength <= 9; ++keyLength) {
        crackEncryptedFileGivenKeyLength(JsonSampleLargeOutputFile, JsonSampleLargeOutputDecryptedFileNoExt, keyLength, badBytes, targetChars);
    }
}

int main() {
    // GetFrequencyOfWholeFile(JsonSampleLargeInputFile);
    // GetFrequencyOfFile(JsonSampleLargeInputFile);
    // GetFrequencyOfFile(JsonSampleLargeOutputFile);
    EncryptFile(JsonSampleLargeInputFile, JsonSampleLargeOutputFile);
    EncryptFile(JsonSampleLargeOutputFile, JsonSampleLargeOutputDecryptedFile);
    Solve();

    return 0;
}

