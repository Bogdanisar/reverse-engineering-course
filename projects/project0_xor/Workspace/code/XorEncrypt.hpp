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


/**
 * Example Unit types:
 * - uint8_t, if we want to xor byte-by-byte.
 * - uint32_t, if we want to xor codepoint-by-codepoint.
 * */
template<typename Unit>
class XorEncrypt {
public:

    /**
     * Counts how many times each unit occurs in 'data', makes pairs and sorts them from most frequent to least frequent.
    */
    static vector<pair<Unit,int>> computeUnitFrequencyForData(const vector<Unit>& data, int start, int step) {
        map<Unit, int> freq;

        for (int i = start; i < (int)data.size(); i += step) {
            Unit unit = data[i];
            if (freq.count(unit) == 0) {
                freq[unit] = 1;
            } else {
                freq[unit] += 1;
            }
        }

        vector<pair<Unit,int>> freqPairs(freq.begin(), freq.end());

        sort(freqPairs.begin(), freqPairs.end(), [] (const auto& p1, const auto& p2) -> bool {
            Unit unit1 = p1.first, unit2 = p2.first;
            int freq1 = p1.second, freq2 = p2.second;
            if (freq1 == freq2) {
                return unit1 < unit2;
            }
            return freq1 > freq2;
        });

        return freqPairs;
    }

    static void printFrequency(const vector<pair<Unit,int>>& freqPairs, int start, int step, Unit xorUnit, int limit = -1) {
        pv(start); pv(step); pv((int)xorUnit); pn;

        int i = 0;
        for (auto iter = freqPairs.begin(); iter != freqPairs.end(); ++iter) {
            Unit unit = iter->first;
            int freq = iter->second;

            if (i == limit) {
                break;
            }

            unit ^= xorUnit;
            printf("%5i - ", i);

            if (unit < 128 && isprint(unit)) {
                cout << "freq('" << (char)unit << "') = " << freq << '\n';
            }
            else {
                cout << "freq(" << unit << ") = " << freq << '\n';
            }

            ++i;
        }
    }

    // Given the xorUnit and the frequency array, we want to find the minimum index idx such that
    // targetUnits is included in freqPairs[0...idx].first.
    static int getMinimumFreqIndexForXorUnit(const vector<pair<Unit,int>>& freqPairs, const vector<Unit>& targetUnits, Unit xorUnit) {
        int ans = 0;

        for (Unit targetUnit : targetUnits) {
            bool found = false;

            for (int idx = 0; idx < (int)freqPairs.size(); ++idx) {
                Unit currentUnit = freqPairs[idx].first ^ xorUnit;
                if (targetUnit == currentUnit) {
                    ans = max(ans, idx);
                    found = true;
                    break;
                }
            }

            if (!found) {
                return freqPairs.size();
            }
        }

        return ans;
    }

    static bool xorUnitDecryptionHasBadUnits(const vector<pair<Unit,int>>& freqPairs, const vector<Unit>& badUnits, Unit xorUnit) {

        for (Unit badUnit : badUnits) {
            for (int idx = 0; idx < (int)freqPairs.size(); ++idx) {
                Unit currentUnit = freqPairs[idx].first ^ xorUnit;
                if (badUnit == currentUnit) {
                    return true;
                }
            }
        }

        return false;
    }

    /** Look for the xor unit that has the target units as close as possible to the most frequent units found in the decrypted data.
     *  Also, eliminate any xor units in whose decrypted data we would find units we shouldn't find (like '\0' maybe).
     */
    static pair<int, Unit> getXorUnitWithMinimumFreqIndex(const vector<pair<Unit,int>>& freqPairs,
                                                          const vector<Unit>& badUnits,
                                                          const vector<Unit>& targetUnits,
                                                          const vector<Unit>& acceptableXorUnits) {
        int minIndex = freqPairs.size();
        Unit xorUnitWithMinIndex = -1;

        for (Unit xorUnit : acceptableXorUnits) {
            if (xorUnitDecryptionHasBadUnits(freqPairs, badUnits, xorUnit)) {
                // cout << "Bad xor unit: " << xorUnit << '\n';
                continue;
            }

            int minIndexForThisXorUnit = getMinimumFreqIndexForXorUnit(freqPairs, targetUnits, xorUnit);
            // pv(xorUnit); pv(minIndexForThisXorUnit); pn;

            if (minIndex > minIndexForThisXorUnit) {
                minIndex = minIndexForThisXorUnit;
                xorUnitWithMinIndex = xorUnit;
            }
        }

        return {minIndex, xorUnitWithMinIndex};
    }

    static vector<Unit> crackEncryptedDataGivenKeyLength(const vector<Unit>& inputData,
                                                         int keyLength,
                                                         const vector<Unit>& badUnits,
                                                         const vector<Unit>& targetUnits,
                                                         const vector<Unit>& acceptableXorUnits) {
        vector<Unit> xorUnitSolution;
        bool badKey = false;

        for (int start = 0; start < keyLength; ++start) {
            vector<pair<Unit,int>> freqPairs = computeUnitFrequencyForData(inputData, start, keyLength);
            // printFrequency(freqPairs, start, keyLength, 0, 25); pn; pn;

            pair<int,Unit> pairMinFreqIdxAndXorUnit = getXorUnitWithMinimumFreqIndex(freqPairs, badUnits, targetUnits, acceptableXorUnits);
            Unit xorUnit = pairMinFreqIdxAndXorUnit.second;

            // int minFreqIdx = pairMinFreqIdxAndXorUnit.first;
            // pv(keyLength); pv(start); pv(minFreqIdx); pv(xorUnit); pv((char)xorUnit); pn;
            // printFrequency(freqPairs, start, keyLength, xorUnit, 25);
            // pn; pn;

            if ((int)xorUnit == -1) {
                badKey = true;
            }

            xorUnitSolution.push_back(xorUnit);
        }

        pv(keyLength);
        printf("xorUnitSolution = ");
        for (Unit xorUnit : xorUnitSolution) {
            cout << "[" << (int32_t)xorUnit << "]";
        }
        cout << " - ";
        for (Unit xorUnit : xorUnitSolution) {
            cout << (char)xorUnit;
        }
        cout << '\n';

        if (badKey) {
            return {};
        } else {
            return xorUnitSolution;
        }
    }

    static vector<Unit> decryptData(const vector<Unit>& inputData, const vector<Unit>& xorKey) {
        if (xorKey.size() == 0) {
            cout << "Bad xor key! Not doing any decryption...\n";
            return inputData;
        }

        const int keyLength = xorKey.size();

        vector<Unit> outputData = inputData;
        int i = 0;
        for (Unit& unit : outputData) {
            unit ^= xorKey[i++ % keyLength];
        }

        return outputData;
    }

};
