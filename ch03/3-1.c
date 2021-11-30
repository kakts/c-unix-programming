/**
 * @file 3-1.c
 * 
 * ファイルを読み専用で開いて、ファイル記述しの値を表示する
 */
#include <fcntl.h> // open
#include <unistd.h> // close
#include <stdlib.h> // exit
#include <stdio.h>

int main(void) {

    // file open
    int fd = open("ch03/input.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
    }
    printf("fd: %d", fd);

    int close_success = close(fd);
    if (close_success == -1) {
        perror("close");
    }
    return 0;
}