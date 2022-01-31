/**
 * @file showenv.c
 * 
 * 5.2 q5.5 全ての環境変数とその値を表示するプログラム
 */
#include <stdio.h>

// 外部変数 environを参照するため
extern char **environ;

int main(void)
{
    char **p = environ;
    while (*p != NULL) {
        printf("%s\n", *p);
        p++; // pをインクリメントすると次の要素
    }
    return 0;
}