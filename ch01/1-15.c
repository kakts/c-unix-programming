/**
 * @file 1-15.c
 * 
 * union any_t char int float double
 */
#include <stdio.h>

union any_t {
    char c;
    int i;
    float f;
    double d;
};

// any_tに格納されている型を指定するenum
enum any_discr {
    ANY_CHAR,
    ANY_INT,
    ANY_FLOAT,
    ANY_DOUBLE
};

// any_tのunion typeの変数同士を加算する関数
union any_t any_add(union any_t a1, union any_t a2, enum any_discr discr) {
    union any_t ret;

    switch (discr) {
        case ANY_CHAR:
            ret.c = a1.c + a2.c;
        case ANY_INT:
            ret.i = a1.i + a2.i;
        case ANY_FLOAT:
            ret.f = a1.f + a2.f;
        case ANY_DOUBLE:
            ret.d = a1.d + a2.d;
        default:
            printf("not matched discr");
    }
    return ret;
}

int main(void) {

    union any_t a1, a2;
    a1.i = 10;
    a2.i = 20;

    union any_t res;
    enum any_discr discr = ANY_INT;
    res = any_add(a1, a2, discr);

    printf("result. discr: %d, data: %d", discr, res.i);
}