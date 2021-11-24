/**
 * @file 2-4.c
 * 
 * 
 */

#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1 [] = "hello", s2 [10] = "";
    // strcpyは第1引数がコピー先
    strcpy(s2, s1);
    printf("%s\n", s2);
}