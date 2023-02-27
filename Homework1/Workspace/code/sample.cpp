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


using namespace std;


bool charIsPrintableAscii(unsigned char uc) {
    return (uc < 128) && (isprint(uc) || isspace(uc));
}

void decryptPerByte(const char *infile, const char *outfile, const vector<unsigned char>& xorKey, bool ignoreBadChar = false) {
    FILE *fin = fopen(infile, "rb");
    FILE *fout = fopen(outfile, "wb");
    assert(fin); assert(fout);

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

int main() {
    const string key = "ZQCsyxHT";
    vector<unsigned char> xorKey(key.begin(), key.end());

    decryptPerByte("input/_data 8 bogdan.burcea.json", "temp/_data 8 bogdan.burcea_sample_dec.json", xorKey);

    return 0;
}
