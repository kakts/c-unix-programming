/**
 * @file 2-7.c
 * 
 * dangling pointerの解消
 */

#include <stdio.h>
#include <stdlib.h>

struct point {
    int x, y;
};

/**
 * dangling pointerが存在しないバージョン
 */
int wrong_main(void)
{
    struct point *p = malloc(sizeof(struct point));
    int *q = &p->x;
    p->x = 10; p->y = 20;
    printf("%d\n", *q);
    // printfで使用したあとにfreeする
    free(p);
}

/**
 * dangling pointerが存在する
 */
int wrong_main(void)
{
    struct point *p = malloc(sizeof(struct point));
    int *q = &p->x;
    p->x = 10; p->y = 20;
    free(p);
    // pをfreeした後にpのメンバ変数xへのポインタを参照している
    printf("%d\n", *q);
}