#include <stdint.h>

typedef struct {
    uint64_t v1;
    uint64_t v2;
} mystruct_t;

int main() {
    mystruct_t s;

    printf("%llu, %llu\n", s.v1, s.v2);

    return 0;
}
