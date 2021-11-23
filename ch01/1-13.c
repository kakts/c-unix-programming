/**
 * @file 1-13.c
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stddef.h> // offsetof

struct foo {
    char c1;
    int i;
    char c2;
    long double ld;
};

int main(void) {
    struct foo f = {
        'a',
        10,
        'b',
        15
    };
    printf("c1: %c, int: %d, c2: %c, long: %Lf\n", f.c1, f.i, f.c2, f.ld);
    printf("size: c1: %zu, int: %zu, c2: %zu, long: %zu\n", sizeof(f.c1), sizeof(f.i), sizeof(f.c2), sizeof(f.ld));
    printf("offsetof: c1: %zu, int: %zu, c2: %zu, long: %zu\n",
        offsetof(struct foo, c1),
        offsetof(struct foo, i) - offsetof(struct foo, c1) - sizeof(f.c1),
        offsetof(struct foo, c2) - offsetof(struct foo, i) - sizeof(f.i),
        offsetof(struct foo, ld) - offsetof(struct foo, c2) - sizeof(f.c2));
    printf("alignof: char: %zu, int: %zu, long double: %zu\n", __alignof__(char), __alignof__(int), __alignof__(long double));
    return 0;
}