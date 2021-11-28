/**
 * @file 2-11.c
 */


#include <stdio.h>

struct rectangle {
    int width, height
};

typedef struct rectangle Rectangle;

typedef int *Intptr;

typedef int IntArray_2_3[2][3];

typedef void (*FuncPtr) (int);