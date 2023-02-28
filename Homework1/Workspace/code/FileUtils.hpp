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

#include "common.h"

using namespace std;


class FileUtils {
public:
    static vector<uint8_t> getBytesOfBinaryFile(const char * const file) {
        vector<uint8_t> bytes;

        FILE *fin = fopen(file, "rb");
        assert(fin);

        uint8_t byte;
        while (fread(&byte, sizeof(byte), 1, fin) == 1) {
            bytes.push_back(byte);
        }

        assert( fclose(fin) == 0 );

        return bytes;
    }

    static vector<uint32_t> getCodePointsOfUTF8File(const char * const file) {
        const char * const tempFile = "temp/FileUtilsTemp.txt";

        char command[1000] = {};
        sprintf(command, "python3 ../code/UTF8CodePointConverter.py utf8-cp \"%s\" \"%s\"", file, tempFile);
        pv(command); pn;
        assert( system(command) == 0);

        vector<uint32_t> codePoints;
        ifstream fin(tempFile);
        uint32_t codePoint;
        while (fin >> codePoint) {
            codePoints.push_back(codePoint);
        }

        return codePoints;
    }

    static void writeCodePointsToUTF8File(const vector<uint32_t>& data, const char * const outputFile) {
        const char * const tempFile = "temp/FileUtilsWriteCPTemp.txt";

        ofstream tout(tempFile);
        for (uint32_t unit : data) {
            tout << unit << '\n';
        }
        tout.close();

        char command[1000] = {};
        sprintf(command, "python3 ../code/UTF8CodePointConverter.py cp-utf8 \"%s\" \"%s\"", tempFile, outputFile);
        pv(command); pn;
        assert( system(command) == 0);
    }
};

