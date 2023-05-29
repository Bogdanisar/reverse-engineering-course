#include <set>
#include <sstream>

#include "decrypt.h"
#include "FileUtils.hpp"
#include "XorEncrypt.hpp"


const char * const JsonSampleFile = "input/jsonSample_input2.json";
const char * const InitialTaskFile = "input/_data 8 bogdan.burcea.json";
const char * const InitialTaskFileDecrypted = "input/_data 8 bogdan.burcea_decrypted.json";
const char * const TaskFileUTF8Reconverted = "temp/runTaskCodepoints_utf8_reconverted.json";
const char * const TaskFileTestDecrypt = "temp/_data 8_test_decrypt.json";
const char * const TaskFileTestDecryptNoExt = "temp/_data 8_test_decrypt";


void PrintBytesOfTaskFile() {
    vector<uint8_t> bytes = FileUtils::getBytesOfBinaryFile(InitialTaskFile);
    pv(bytes.size()); pn;

    for (int i = 0; i < 30; ++i) {
        pv(i); pv((int)bytes[i]); pn;
    }
}

void PrintCodePointsOfTaskFile() {
    vector<uint32_t> codePoints = FileUtils::getCodePointsOfUTF8File(InitialTaskFile);
    pv(codePoints.size()); pn;

    for (int i = 0; i < 30; ++i) {
        pv(i); pv(codePoints[i]); pn;
    }
}

void PrintFrequencyForWholeFile(const char * const file) {
    vector<uint32_t> codePoints = FileUtils::getCodePointsOfUTF8File(file);
    auto freqPairs = XorEncrypt<uint32_t>::computeUnitFrequencyForData(codePoints, 0, 1);
    XorEncrypt<uint32_t>::printFrequency(freqPairs, 0, 1, 0, -1);
}

void PrintFrequencyForFileSliceGivenXorCodePoint(const char * const file, int start, int keyLength, uint32_t xorKey) {
    vector<uint32_t> codePoints = FileUtils::getCodePointsOfUTF8File(file);
    auto freqPairs = XorEncrypt<uint32_t>::computeUnitFrequencyForData(codePoints, start, keyLength);
    XorEncrypt<uint32_t>::printFrequency(freqPairs, start, keyLength, xorKey, -1);
}

void TestCodePointConversionAndBack() {
    vector<uint32_t> codePoints = FileUtils::getCodePointsOfUTF8File(JsonSampleFile);
    FileUtils::writeCodePointsToUTF8File(codePoints, TaskFileUTF8Reconverted);
}

void Solve() {
    vector<uint32_t> codePoints = FileUtils::getCodePointsOfUTF8File(InitialTaskFile);


    vector<uint32_t> badCodePoints;
    for (int i = 0; i < 32; ++i) {
        if (9 <= i && i <= 13) {
            // 9 -> Horizontal tab (\t) -> OK.
            // 10 -> Newline (\n) -> OK.
            // 11 -> Vertical Tab (\v) -> OK.
            // 12 -> Feed (\f) -> OK.
            // 13 -> Carriage Return (\r) -> OK.
            continue;
        }

        badCodePoints.push_back(i);
    }
    badCodePoints.push_back(127);


    // const string key = " ";
    // const string key = " {}\":,\naeiou";
    const string key = " {}\":,\naeiouhtps/";
    const vector<uint32_t> targetCodePoints(key.begin(), key.end());


    vector<uint32_t> acceptableXorCodePoints;
    for (uint32_t i = 'A'; i <= 'Z'; ++i) { acceptableXorCodePoints.push_back(i); }
    for (uint32_t i = 'a'; i <= 'z'; ++i) { acceptableXorCodePoints.push_back(i); }


    int minKeyLength = 5, maxKeyLength = 9;
    // minKeyLength = maxKeyLength = 8;
    for (int keyLength = minKeyLength; keyLength <= maxKeyLength; ++keyLength) {
        vector<uint32_t> xorKey;
        xorKey = XorEncrypt<uint32_t>::crackEncryptedDataGivenKeyLength(codePoints,
                                                                        keyLength,
                                                                        badCodePoints,
                                                                        targetCodePoints,
                                                                        acceptableXorCodePoints);
        auto decryptedCodePoints = XorEncrypt<uint32_t>::decryptData(codePoints, xorKey);

        string outputFile = string(TaskFileTestDecryptNoExt);
        outputFile.append(1, '0' + keyLength);
        outputFile += ".json";

        FileUtils::writeCodePointsToUTF8File(decryptedCodePoints, outputFile.c_str());
        pn;
    }
}

void TestDecrypt() {
    vector<uint32_t> codePoints = FileUtils::getCodePointsOfUTF8File(InitialTaskFile);
    vector<uint32_t> xorKey = {'C','s','y','x','H','T','Z','Q',};
    codePoints = XorEncrypt<uint32_t>::decryptData(codePoints, xorKey);
    FileUtils::writeCodePointsToUTF8File(codePoints, TaskFileTestDecrypt);
}

int main() {
    // PrintBytesOfTaskFile();
    // PrintCodePointsOfTaskFile();
    // PrintFrequencyForWholeFile(InitialTaskFile);
    // PrintFrequencyForFileSliceGivenXorCodePoint(InitialTaskFile, 0, 8, 'C');
    // PrintFrequencyForWholeFile(InitialTaskFileDecrypted);
    // TestCodePointConversionAndBack();
    Solve();
    // TestDecrypt();

    return 0;
}

