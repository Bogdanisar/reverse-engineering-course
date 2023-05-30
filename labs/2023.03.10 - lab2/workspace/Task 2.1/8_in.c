// Compilatorul face n>>1 pt. nr. pozitive si (n+3)>>1 pentru numere negative
int div4(int n) {
    return n / 4;
}

// Compilatorul face n>>5 pt. nr. pozitive si (n+31)>>5 pentru numere negative
int div32(int n) {
    return n / 32;
}

// Multiplication and shifting with magic numbers
int div5(int n) {
    return n / 5;
}

int mult4(int n) {
    return n * 4;
}

int mult32(int n) {
    return n * 32;
}

int mult5(int n) {
    return n * 5;
}

// No optimizations possible here
int mult(int n) {
    return n * 30;
}
