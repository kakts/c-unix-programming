/**
 * @file diary1.c
 * 
 * 日記帳プログラム
 * - 日記を書く。使う人は日付を入力してから、その日の日記を書く
 * - 日記を読む　入力された日付の日記を表示する
 */
#include <stdio.h>
#include <stdlib.h>
#include "../sub/mysub.h"
#include <string.h>

enum {
    MAXLINE = 1024,
};

void writediary(void);
void readdiary(void);

int main(void)
{
    int cmd;

    for (;;) {
        cmd = getint("1=write, 2=read, 3=end: ");
        switch (cmd) {
            case 1:
                writediary();
                break;
            case 2:
                readdiary();
                break;
            case 3:
                return 0;
            default:
                fputs("unknown command\n", stderr);
                break;
        }
    }
}

/**
 * 日記を書く
 */
void writediary(void) {
    FILE *fp;
    char date[MAXLINE], s[MAXLINE];

    char file_dir[MAXLINE + 30];
    getstr("date (MMDD): ", date, sizeof(date));

    sprintf(file_dir, "./ch04/diary/%s", date);
    // 日記ファイルを書き込み専用で開く
    fp = fopen(file_dir, "w");
    // stdinから入力したものをファイルに書き込む
    while (fgets(s, sizeof(s), stdin) != NULL) {
        fputs(s, fp);
    }
    // EOFか?
    if (feof(stdin)) {
        // ストリームエラー発生時に、そのストリームにエラーのフラグがついた状態になる
        // これを消すためにclearerrを使う。
        clearerr(stdin);
    } else {
        perror("fgets");
        exit(1);
    }
    fclose(fp);
}

/**
 * 日記を読む
 * 指定した日付のファイルを開いて読み取る
 */
void readdiary(void) {
    FILE *fp;
    char date[MAXLINE], s[MAXLINE];

    char file_dir[MAXLINE + 30];

    getstr("date (MMDD): ", date, sizeof(date));
    printf("-----read from %s\n", file_dir);
    sprintf(file_dir, "./ch04/diary/%s", date);
    // 日記ファイルを読み取り専用で開く
    fp = fopen(file_dir, "r");
    // 日記ファイルのストリームから読み取る
    while (fgets(s, sizeof(s), fp) != NULL) {
        // ファイルの内容をstdoutに出力する
        fputs(s, stdout);
    }
    if (ferror(fp)) {
        // エラー?
        perror("fgets");
        exit(1);
    }
    fclose(fp);
}

