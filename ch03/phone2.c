/**
 * @file phone2.c
 * 
 * 電話帳プログラム
 * 1ユーザあたり、電話番号、名前、項目タイプ(仕事・プライベート)を登録できるようにする
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

#define PHONEBOOK "phone2x.dat" // 電話帳ファイルの名前

// データ項目ごとのバイト数
enum {
    NAMELEN = 32, // 名前
    PHONELEN = 16, // 電話番号
};

// 各ユーザのデータ
struct person {
    char name[NAMELEN + 1];
    char phone[PHONELEN + 1];
    int isprivate; 
};

size_t PERSON_DATA_LEN = sizeof(struct person);

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
    struct person data;

    recno = getint("record number? ");
    // recno * RECLEN がファイルにおける項目recnoの先頭位置
    if (lseek(fd, recno * PERSON_DATA_LEN, SEEK_SET) == -1) {
        perror("lseek");
        return;
    }
    if ((cc = read(fd, &data, PERSON_DATA_LEN)) < 0) {
        perror("read");
        return;
    }
    if (cc == 0) {
        printf("no item\n");
    } else {
        printf("record = %d \n name = \"%s\",\n phone = %s,\n isprivate = %d\n", recno, data.name, data.phone, data.isprivate);
    }
    return;
}

/**
 * input
 */
void input(int fd) {
    int recno;
    char name[NAMELEN + 1]; // +1はヌル文字のため
    char phone[PHONELEN + 1]; // +1はヌル文字のため
    int isprivate;
    struct person data;

    // 領域を0で埋めてゴミを無くす
    memset(data.name, 0, sizeof(data.name));
    memset(data.phone, 0, sizeof(data.phone));
    recno = getint("record number? ");
    // 位置を指定した項目の先頭に変更する 1データのサイズはPERSON_DATA_LEN 先頭から recno * RECLENにする
    if (lseek(fd, recno * PERSON_DATA_LEN, SEEK_SET) == -1) {
        perror("lseek");
        return;
    }

    getstr("name? ", data.name, sizeof(name));
    getstr("phone? ", data.phone, sizeof(phone));
    data.isprivate = getint("data.isprivate? ");
    if (data.isprivate > 1) {
        perror("getint: isprivate");
        return;
    }
    if (write(fd, &data, PERSON_DATA_LEN) != PERSON_DATA_LEN) {
        perror("write");
        return;
    }

    return;

}