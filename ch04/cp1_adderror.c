/**
 * @file cp1_adderror.c
 * 
 * 演習問題4.4 
 * q4.2 ファイルの複製にエラー処理を付け加える
 * getc putcを使ってファイルを複製する　引数で入力・出力ファイル名を与えられるようにする
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strerror
int main(int argc, char const *argv[])
{
    /* code */

    if (argc < 3) {
        fprintf(stderr, "usage: %s <infile> <outfile>\n", argv[0]);
        exit(1);
    }

    FILE *input_fp;
    FILE *output_fp;

    /**
     * input outputそれぞれのエラー時、perrorだとどちらのエラーかわからないので、strerror(3)を使って
     * ユーザが指定したファイル名とともにエラーの内容を表示する
     */
    if ((input_fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "fopen: %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    // 書き出し専用で開く
    if ((output_fp = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "fopen: %s: %s\n", argv[2], strerror(errno));
        exit(1);
    }

    int input_data;
    while ((input_data = getc(input_fp)) != EOF) {
        if (putc(input_data, output_fp) == EOF) {
            perror("putc");
            exit(1);
        }
    }

    if (ferror(input_fp)) {
        perror("getc");
        // getcでエラーが起きても、開いているファイルは閉じた方がいいので、exitせずにそれに続く
        // fcloseが実行されるようにしてある
    }


    if (fclose(input_fp) == -1) {
        perror("fclose");
        exit(1);
    }

    if (fclose(output_fp) == -1) {
        perror("fclose");
        exit(1);
    }


    return 0;
}
