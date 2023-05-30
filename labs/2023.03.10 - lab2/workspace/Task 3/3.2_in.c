
// This computes elements of the Fibonacci sequence.
unsigned long long myst4(unsigned long long n) {
    if (n <= 1) {
        return n;
    }

    return myst4(n-1) + myst4(n-2);
}
