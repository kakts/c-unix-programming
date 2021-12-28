/**
 * @file tinymining.c
 * 
 * 4.4.4 コード例4.7
 * ちょっとしたデータマイニング
 * 
 * 変数nameに入っている名前を、標準入力から探す。
 * stdinからのデータを語ごとにnameと比べる
 * nameに一致したらmynameを1増やす
 * 一致しなかったらnotmynameを1増やす
 * アルファベットでない文字はごみとして、その文字数をjunkcharsで数える
 * 
 * mainからprocesswordに飛ぶ時にはストリームから語が読めるようになっている状態
 * processwordからmainに戻る時にはストリームからゴミ文字が読めるようになっている
 * ungetcを使ってこの仕組みを実現している
 * 
 * assert(3)マクロは　指定した条件式が満たされていない場合にプロセスを強制的に終了する
 */
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MYNAMELEN = 15,
};

char name[] = "Rie";
int myname, notmyname, junkchars;

void processword(void);

intmain(void)
{
    int c;

    assert(strlen(name) <= MYNAMELEN);
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            // 入力ストリームのスタックに文字を戻す。 スタックが満杯の場合はEOF
            if (ungetc(c, stdin) == EOF) {
                fputs("cannot ungetc\n", stderr);
                exit(1);
            }
            processword();
        } else {
            // 該当しない文字数をカウント
            junkchars++;
        }
    }
    printf("my name %d, not my name %d, junk chars %d\n", myname, notmyname, junkchars);
    return 0;
}

void processword(void) {
    int c, i;
    char buf[MYNAMELEN + 2];
    /**
     * strcmp()で違いがわかるように、語が長いときは
     * MYNAMELEN + 1 バイト読むようにする
     */
    i = 0;
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            // bufに詰める
            buf[i] = c;
            i++;
            if (i == (sizeof(buf) - 1)) {
                while ((c = getchar()) != EOF) {
                    if (!isalpha(c)) {
                        if (ungetc(c, stdin) == EOF) {
                            fputs("cannot ungetc\n", stderr);
                            exit(1);
                        }
                        break;
                    }
                    goto wordgot;
                }
            } else {
                if (ungetc(c, stdin) == EOF) {
                    fputs("cannot ungetc\n", stderr);
                    exit(1);
                }
                goto wordgot;
            }
        }
    }

// gotoは可読性の観点から本当は使わない方が良い
wordgot:
    buf[i] = '\0';
    if (!strcmp(buf, name)) {
        myname++;
    } else {
        notmyname++;
    }
}
