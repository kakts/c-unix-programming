/**
 * @file failed_for_coredump.c
 * 
 * コアダンプ確認用プログラム
 * わざとセグメンテーションフォルトを起こしてコアダンプを確認するためのもの
 */

#include <stdio.h>
int main(void)
{
    int *p = NULL;
    printf("%d\n", *p);
}