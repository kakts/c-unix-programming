/**
 * @file 1-15.c
 * 
 * union any_t char int float double
 */
#include <stdio.h>
#include <assert.h> // assert

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
};

// any_t型とそのデータのdiscrをカプセル化したもの
struct any_t2 {
    enum any_discr discr;
    union any_t u;
};

struct any_t2 any_add2 (struct any_t2 x, struct any_t2 y) {
    struct any_t2 ret;
    if (x.discr != y.discr) {
        fprintf(stderr, "different type addition");
        assert(0);
    }
    ret.discr = x.discr;
    switch (x.discr) {
    case ANY_CHAR:
        ret.u.c = x.u.c + y.u.c;
    case ANY_INT:
        ret.u.i = x.u.i + y.u.i;
    case ANY_FLOAT:
        ret.u.f = x.u.f + y.u.f;
    case ANY_DOUBLE:
        ret.u.d = x.u.d + y.u.d;
    default:
        printf("not matched discr");
    }
    return ret;
};

int main(void)
{

    union any_t a1, a2;
    a1.i = 10;
    a2.i = 20;

    struct any_t2 x, y;
    x.discr = ANY_INT;
    y.discr = ANY_INT;
    x.u = a1;
    y.u = a2;

    union any_t res;
    enum any_discr discr = ANY_INT;
    res = any_add(a1, a2, discr);

    printf("result. discr: %d, data: %d\n", discr, res.i);

    struct any_t2 res_t2;
    res_t2 = any_add2(x, y);
    printf("result any_t2. discr: %d, data: %d\n", res_t2.discr, res_t2.u.i);
}