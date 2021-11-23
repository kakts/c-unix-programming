/**
 * @file discr.c
 * 
 * 1.6.2 弁別子
 * 共用体の最後に格納したメンバを覚えておく変数や構造体のメンバを 弁別子discriminatorという
 * 共用体を使うために弁別子を使うのは良いこと
 * 構造体を使って、弁別子と共用体を1つにカプセル化するともっとよい
 */
#include <stdio.h>

union foo {
    int i;
    double d;
};
enum Type {
    Int,
    Double
};

struct bar {
    enum Type type; // 弁別子
    union foo u; // 共用体
};

int main(void)
{
    struct bar x;

    // uのメンバdに格納したら、dに格納したことをtypeに記録する
    x.u.d = 12.34;
    x.type = Double;

    printf("discr is :%u", x.type);
}