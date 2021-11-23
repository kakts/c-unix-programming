/**
 * @file bad-union.c
 * 
 * 1.6.1 共用体の誤用令
 * 
 * 共用体は最後に格納したメンバと同じ値を使用する必要がある
 * 利用する場合は開発者がメンバの使用を管理しないといけない
 */
#include <stdio.h>

union foo {
    int i;
    double d;
};

int main(void)
{
    union foo x;
    x.d = 12.34; // doubleの変数dを格納

    printf("%f\n", x.d); // OK 最後に格納したメンバdと一致
    printf("%d\n", x.i); // NG 最後に格納したメンバと不一致
}
