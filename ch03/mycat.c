/**
 * @file mycat.c
 * 
 * 3.18 章末問題1
 * 指定されたファイルを連結して標準出力に出力するプログラム mycat.cを作る
 * 
 * ```bash
    ./mycat aaa bbb ccc
    ```

    とすると、ファイルaaa, bbb ,cccをこの順序で連結した結果が出力されるようにする

    引数が指定されない場合はstdinから読まれたデータをそのまま標準出力に出力する
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../sub/mysub.h" // mysub.cをリンクする

const int MAX_BYTE_STR = 4096;

/**
 * stdinから文字列を読み込んでそのまま表示する
 */
void read_from_stdin() {
    // stdinから読み込む
    // +1はヌル文字用
    char buf[MAX_BYTE_STR + 1];
    fgets(buf, MAX_BYTE_STR, stdin);
    // 読み込んだ値を表示する
    printf("%s", buf);
    return;
}

/**
 * stdinから文字列を読み込んでそのまま表示する
 */
void read_and_concat_from_file(int argc, char const *argv[]) {
    // 開くファイルのfd一覧
    int fd_list[argc - 1];

    char buf[MAX_BYTE_STR * argc];

    char read_buf_list[argc - 1][MAX_BYTE_STR];
    int READ_BYTE = 64;

    // 全ファイルの通算バイト数
    int read_cc = 0;
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            perror("open");
            exit(1);
        }
        int cc = 0;
        char file_buf[READ_BYTE];
        while ((cc = read(fd, read_buf_list[i - 1], sizeof(read_buf_list[i - 1]))) > 0) {
            read_cc += cc;
        }
        fd_list[i] = fd;
    }

    // WIP ファイルを連結して表示させる
    for (int i = 0; i < argc - 1; i++) {
        strcat(buf, read_buf_list[i]);
    }

    // 連結したものを表示させる
    printf("finish\n%s:\n", buf);
}

int main(int argc, char const *argv[])
{
    // 引数取得
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("arg:%d, %s\n", argc, argv[i]);
    }
    if (argc > 1) {
        // 引数指定あり
        read_and_concat_from_file(argc, argv);
    } else {
        // 引数指定なしの場合はstdinから読み込む
        while (1) {
            read_from_stdin();
        }
    }

    /* code */
    return 0;
}

