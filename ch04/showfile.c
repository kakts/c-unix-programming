/**
 * @file showfile.c
 * ファイルの内容を表示する
 */
#include <stdio.h>
#include <stdlib.h>

#define INFILE "ch04/hello.txt"

int main(void)
{
    FILE *fp;
    int c;

    if ((fp = fopen(INFILE, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    // ファイルから読み込んでstdoutに書く
    while((c = getc(fp)) != EOF) {
        putchar(c);
    }
    if (fclose(fp) == EOF) {
        perror("fclose");
        exit(1);
    }
    return 0;
}