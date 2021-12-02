/**
 * @file phone1.c
 * 
 * 電話帳プログラム
 * 1項目あたり名前だけ 32バイトのデータを持たせる
 * 
 * sub/mysub.cもコンパイルしてリンクさせる必要がある
 * gcc ch03/phone1.c sub/mysub.c -o phone1
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../sub/mysub.h" // mysub.cをリンクする

#define PHONEBOOK "phone1.dat" // 電話帳ファイルの名前

enum {
    RECLEN = 32, // ファイル内での1項目の長さ
};

// 関数のプロトタイプ宣言
void show(int);
void input(int);

int main(void)
{
    int fd, cmd;
    int finish;
    if ((fd = open(PHONEBOOK, O_RDWR | O_CREAT, 0666)) < 0) {
        perror("open");
        exit(1);
    }
    finish = 0;
    while(!finish) {
        // コマンドの取得
        cmd = getint("command (0=show, 1=input, 2=end)? ");
        switch (cmd) {
            case 0:
                show(fd);
                break;
            case 1:
                input(fd);
                break;
            case 2:
                // 繰り返しを抜ける
                finish = 1;
                break;
            default:
                fprintf(stderr, "unknown command%d\n", cmd);
                break;
        }
    }
    if (close(fd) < 0) {
        perror("close");
        exit(1);
    }
    return 0;
}

/**
 * 表示
 */
void show(int fd) {
    int recno;
    ssize_t cc;
    char rec[RECLEN + 1];

    rec[RECLEN] = '\0';
    recno = getint("record number? ");
    // recno * RECLEN がファイルにおける項目recnoの先頭位置
    if (lseek(fd, recno *RECLEN, SEEK_SET) == -1) {
        perror("lseek");
        return;
    }
    if ((cc = read(fd, rec, RECLEN)) < 0) {
        perror("read");
        return;
    }
    if (cc == 0) {
        printf("no item\n");
    } else {
        printf("item = \"%s\"\n", rec);
    }
    return;
}

/**
 * input
 */
void input(int fd) {
    int recno;
    char rec[RECLEN + 1]; // +1はヌル文字のため

    // 領域を0で埋めてゴミを無くす
    memset(rec, 0, sizeof(rec));
    recno = getint("record number? ");
    // 位置を指定した項目の先頭に変更する 1項目32バイトなので 先頭から recno * RECLENにする
    if (lseek(fd, recno * RECLEN, SEEK_SET) == -1) {
        perror("lseek");
        return;
    }

    getstr("name? ", rec, sizeof(rec));
    if (write(fd, rec, RECLEN) != RECLEN) {
        perror("write");
        return;
    }
    return;

}