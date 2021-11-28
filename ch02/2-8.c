/**
 * @file 2-8.c
 * 
 * 
 */

#include <stdio.h>

/**
 * getsはバッファオーバーランの原因となりうる
 */
int main(void)
{
    char buf [1024];
    printf("Please type your name: ");
    fgets(buf, sizeof(buf), stdin);
    printf("hello, %s\n", buf);
    return 0;
}


/**
 * getsはバッファオーバーランの原因となりうる
 */
int orig_main(void)
{
    char buf [1024];
    printf("Please type your name: ");
    gets(buf);
    printf("hello, %s\n", buf);
}
