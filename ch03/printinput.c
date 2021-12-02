/**
 * @file printinput.c
 * 
 * q3.5
 * ファイルinput.fileの内容を画面に表示する
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void) {
    int input_fd = open("ch03/input.file", O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        exit(1);
    }
    char buf[10];
    ssize_t cc;
    while ((cc = read(input_fd, buf, sizeof(buf))) > 0) {
        // stdoutに対してファイルから読み取ったデータを書き出す
        if (write(STDOUT_FILENO, buf, cc) < cc) {
            // 指定したバイト数分書き出せていない場合はエラー
            perror("write");
            exit(1);
        }
    }
    if (cc == -1) {
        perror("read");
        exit(1);
    }

    if (close(input_fd) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}