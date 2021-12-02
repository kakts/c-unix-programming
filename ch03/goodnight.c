/**
 * @file goodnight.c
 * 
 * 文字を変換する
 * 変更前: Good bye!\n
 * 変更後: Good night!\n
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void)
{
    int fd;

    if ((fd = open("ch03/bye.txt", O_WRONLY)) < 0) {
        perror("open");
        exit(1);
    }
    // ファイルの先頭から指定したオフセットを先頭位置にする
    if (lseek(fd, 5, SEEK_SET) == -1) {
        perror("lseek");
        exit(1);
    }
    // ファイルに書き込み lseekで既に書き込み位置は変わっている
    if (write(fd, "night!\n", 7) != 7) {
        perror("write");
        exit(1);
    }
    if (close(fd) < 0) {
        perror("close");
        exit(1);
    }
    return 0;
}