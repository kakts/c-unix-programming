/**
 * @file hop.c
 * 
 * hop　と書いて3バイトだけファイルの末尾に向かって位置決めする　を8回繰り返す
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>

int main(void)
{
    int fd = open("ch03/hop.out", O_RDWR | O_TRUNC | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    int cc;
    int pos;

    // 現在の位置を取得
    pos = lseek(fd, 0, SEEK_CUR);
    printf("first: pos: %d\n", pos);

    int hop_bytes = 3;
    for (int i = 0; i < 8; i++) {
        if ((cc = write(fd, "hop", hop_bytes)) < hop_bytes) {
            perror("write");
            exit(1);
        }
        // 現在の位置から3バイト後方に位置決めする
        pos = lseek(fd, hop_bytes, SEEK_CUR);
        printf("current i: %d, pos: %d\n", i, pos);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}