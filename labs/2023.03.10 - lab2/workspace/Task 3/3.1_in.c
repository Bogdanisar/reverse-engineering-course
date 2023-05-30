// The function is strlen.
// None of these tries give the exact instructions from the PDF.
int myst2(char *str) {
    if (*str == 0) {
        return 0;
    }

    int i = 0;
    do {
        i += 1;
    } while (str[i] != 0);

    return i;

    // int i = 0;
    // while (str[i] != 0) {
    //     ++i;
    // }
    // return i;

    // int i;
    // for (i = 0; str[i] != 0; ++i) ;
    // return i;

    // int len;
    // if (*str == 0) {
    //     len = 0;
    // }
    // else {
    //     len = 0;
    //     while (str[len] != 0) {
    //         ++len;
    //     }
    // }
    // return len;
}
