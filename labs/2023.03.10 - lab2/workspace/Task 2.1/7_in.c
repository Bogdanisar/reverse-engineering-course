#include <stdint.h>

typedef struct {
    uint64_t v1;
    struct mystruct_t *next;
} mystruct_t;

mystruct_t * get_last(mystruct_t *head) {
    mystruct_t *cur = head;

    while (cur->next != 0) {
        cur = cur->next;
    }

    return cur;
}
