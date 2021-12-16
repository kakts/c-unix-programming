/**
 * @file linecp.c
 * 
 * コード例4.5
 * テキストファイルを一行ずつ複製する
 */
#include <errno.h> // errno
#include <stdio.h> // fclose fgets fopen fputs perror
#include <stdlib.h> // exit
#include <string.h> // strerror

enum {
    LINELEN = 1024,
};

int main(int argc, char const *argv[])
{
    FILE *ifp, *ofp;
    char buf[LINELEN];

    if (argc != 3) {
        fputs("usage: linecp <infile> <outfile> \n", stderr);
        exit(1);
    }

    if ((ifp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "fopen: %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    // 書き出し専用で開く
    if ((ofp = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "fopen: %s: %s\n", argv[2], strerror(errno));
        exit(1);
    }

    // ifpからbufのサイズだけ読み取って、NULLにならない限りループする
    while (fgets(buf, sizeof(buf), ifp) != NULL) {
        // ofpに対してバッファの内容を一行書き込む
        if (fputs(buf, ofp) == EOF) {
            perror("fputs");
        }
    }
    if (fclose(ifp) == -1) {
        perror("fclose");
        exit(1);
    }

    if (fclose(ofp) == -1) {
        perror("fclose");
        exit(1);
    }

    return 0;
}
