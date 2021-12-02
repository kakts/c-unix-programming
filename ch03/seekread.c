/**
 * @file seekread.c
 * 
 * 演習3.6  位置決めをしてから読む
 * ファイルinput.fileを開き、ファイル位置10に位置決めしてから5バイト読み、その5バイトを
 * 表示するプログラムを作る
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    int fd = open("ch03/input.file", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    off_t pos = lseek(fd, 0, SEEK_CUR);
    printf("open file. pos: %lld\n", pos);

    pos = lseek(fd, 10, SEEK_SET);
    printf("move pos to %lld\n", pos);


    // ファイル位置10から5バイト読み込む
    int read_byte = 5;
    char buf[read_byte];
    if (read(fd, buf, read_byte) < read_byte) {
        perror("read");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    fflush(stdout);
    if (write(STDOUT_FILENO, buf, read_byte) < read_byte) {
        perror("write");
        exit(1);
    }
    putchar('\n');

    return 0;
}