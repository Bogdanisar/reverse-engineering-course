// Type your code here, or load an example.
int add(int v[], int n) {
    int sum = 0;

    for (int i = 1; i <= n; ++i) {
        sum += v[i];
    }

    return sum;
}
