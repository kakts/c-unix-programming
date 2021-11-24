/**
 * @file 2-6.c
 * 
 * メモリリークが起きないようにプログラムを修正する
 */

#include <stdio.h>
#include <stdlib.h>

struct point {
    int x, y;
};

struct point *make_point(int x, int y)
{
    struct point *p = malloc(sizeof (struct point));
    p->x = x;
    p->y = y;
    return p;
}

int main(void)
{
    int x = 0, y = 0;

    // ポインタ変数の宣言はwhile外でも大丈夫
    struct point *new;
    while (1) {
        // whileでfreeさせる

        new = make_point(x, y);
        printf("(%d, %d)\n", new->x, new->y);
        x++, y++;
        free(new);
    }
}

/**
 * おそらく、whileの外でstruct piont *newをしていて、それをfreeしていない
 * whileの中で毎回ポインタを初期化するようにして、whileの最後でfreeさせる
 */
int wrong_main(void)
{
    int x = 0, y = 0;
    struct point *new;
    while (1) {
        new = make_point(x, y);
        printf("(%d, %d)\n", new->x, new->y);
        x++, y++;
    }

}