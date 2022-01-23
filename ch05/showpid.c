/**
 * @file showpid.c
 * 
 * プロセスIDの取得
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf("pid = %d\n", getpid());
    exit(0);
}

