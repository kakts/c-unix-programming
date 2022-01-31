/**
 * @file setuser.c
 * 
 * ch05 5.2 環境変数の値を変更する
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("USER is %s\n", getenv("USER"));
    if (setenv("USER", "johndoe", 1) == -1) {
        perror("setenv");
        exit(1);
    }
    printf("USER is now %s\n", getenv("USER"));
    return 0;
}