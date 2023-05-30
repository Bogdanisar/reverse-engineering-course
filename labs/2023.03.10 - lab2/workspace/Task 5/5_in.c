#include <stdio.h>
#include <stdint.h>

// gcc -masm=intel -S 5_in.c -o 5_in.S

int main() {
    // printf("%llu\n", (unsigned long long)(0x1337cafe ^ 0xdeadc0de)); fflush(stdout);
    // Key is: 3449424416;

    uint64_t secret_value = 0xdeadc0de;
    uint64_t user_input;

    scanf("%llu", &user_input);

    user_input ^= 0x1337cafe;

    if (user_input == secret_value)
        puts("Correct!");
    else
        puts("Wrong");

    return 0;
}
