/**
 * @file ch04-end-03.c
 * 
 * 4.9 章末問題 3
 * 
 * stdinからテキストファイルをよみ、そのバイト数、語数、行数を表示するプログラムを作る
 * 
 * コンパイル後、下記を実行する
 *  ./a.out ch04/ch04-end-03-txt.txt
 */
#include <stdio.h>
#include <ctype.h> // isspace
#include <stdlib.h>

enum {
    MAXLINELEN = 80,
};

/**
 * wordの始まりの文字か判定する
 * word数カウントに利用する
 */
int is_word_start(int before_char, int current_char) {
    return isspace(before_char) && !isspace(current_char);
}

int main(int argc, char const *argv[])
{

    FILE *input_fp;
    char str[MAXLINELEN];
    int c;
    int before_char = ' ';
    long long int byte_count = 0;
    long long int line_count = 1;
    long long int word_count = 0;

    // stdinからテキストファイルを読む
    if (argc != 2) {
        fprintf(stderr, "please input file name as stdio. ./a.txt");
        exit(1);
    }
    printf("read file of %s \n", argv[1]);
    // テキストファイル read onlyモードで開く
    if ((input_fp = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    // 1文字ずつ読み込む
    while((c = fgetc(input_fp)) != EOF) {
        byte_count += 1;
        if (is_word_start(before_char, c)) {
            // word数カウント
            word_count += 1;
        } else if (c == '\n') {
            line_count += 1;
        }

        before_char = c;
    }



    // ストリームから、バイト数・語数・行数を読み取る
    printf("word_count: %lld\n", word_count);
    printf("line_count: %lld\n", line_count);
    printf("byte_count: %lld\n", byte_count);
    return 0;
}