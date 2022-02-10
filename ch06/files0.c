/**
 * @file files0.c
 * 
 * コード例6.5 ファイル属性の情報から、ファイル種類の分布を確認する
 * 
 * st_modeは整数で、ファイルの種類、許可ビット、セットユーザIDおよびセットグループIDなどの情報をビットフラグとしてまとめて持っている。
 * このメンバの持つ情報のうち、ファイルの種類を除いた部分をファイルモードと呼ぶ
 */
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    struct stat sb;
    DIR *dp;
    struct dirent *dep;

    int i, ndir, nreg, nchr, nblk, nfifo, nsock, nlnk, nunknown;

    if (argc != 2) {
        fprintf(stderr, "usege: files0 <directory>\n");
        exit(1);
    }

    printf("%s: ", argv[1]);
    // カレントディレクトリを指定したディレクトリに移動する
    if (chdir(argv[1]) != 0) {
        printf("<cannot chdir>\n");
        return 1;
    }

    // 指定したディレクトリをオープンする
    if ((dp = opendir(".")) == NULL) {
        printf("<cannot list>\n");
        return 1;
    }

    errno = 0;
    ndir = nreg = nchr = nblk = nfifo = nsock = nlnk = nunknown = 0;

    // ディレクトリ項目を1件ずつ取得する
    while ((dep = readdir(dp)) != NULL) {
        // ディレクトリ項目に対する属性を取得する
        // lstatなので、そのファイルがシンボリックリンクの場合、そのシンボリックリンクの属性を取得
        if (lstat(dep->d_name, &sb) != 0) {
            // エラーの場合は無視する
            continue;
        }

        // st_modeは整数で、ファイルの種類、許可ビット、セットユーザIDおよびセットグループIDなどの情報をビットフラグとしてまとめて持っている。
        // このメンバの持つ情報のうち、ファイルの種類を除いた部分をファイルモードと呼ぶ
        // st_modeの値と、定数マクロ S_IFMTの論理籍を取ることにより、そのファイルの種類を取得できる
        switch (sb.st_mode & S_IFMT) {
            case S_IFDIR:
                // ディレクトリ
                ndir++;
                break;
            case S_IFREG:
                // 通常ファイル
                nreg++;
                break;
            case S_IFCHR:
                // 文字型特殊ファイル
                nchr++;
                break;
            case S_IFBLK:
                // ブロック型特殊ファイル
                nblk++;
                break;
            case S_IFIFO:
                // 名前付きパイプ(FIFO)
                nfifo++;
                break;
            case S_IFSOCK:
                // ソケット
                nsock++;
                break;
            case S_IFLNK:
                // シンボリックリンク
                nlnk++;
                break;
            default:
                // 不明ファイル種別
                nunknown++;
                break;
        }
    }
    // .と..は表示しないため、カウントを減らす
    ndir -= 2; 

    for (i = 0; i < ndir; i++) {
        putchar('/');
    }
    for (i = 0; i < nreg; i++) {
        putchar('-');
    }
    for (i = 0; i < nchr; i++) {
        putchar('%');
    }
    for (i = 0; i < nblk; i++) {
        putchar('#');
    }
    for (i = 0; i < nfifo; i++) {
        putchar('|');
    }
    for (i = 0; i < nsock; i++) {
        putchar('=');
    }
    for (i = 0; i < nlnk; i++) {
        putchar('@');
    }
    for (i = 0; i < nunknown; i++) {
        putchar('?');
    }
    putchar('\n');
    closedir(dp);
    return 0;
}
