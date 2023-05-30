
// The compiler wants to avoid using the 'div' instruction (which is expensive).
// So, instead, it simulates (n / 17) by
// (n * 16/17 * 1/16) which is
// (n *= [(16/17 + epsilon) * 2^64]; n >>= 64; n >>= 4), where
// -1085102592571150095 = [(16/17 + epsilon) * 2^64]
unsigned long long my_function(unsigned long long n) {
    return n / 17;
}
