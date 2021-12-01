/**
 * @file 3-8.c
 * 
 * ファイル input.fileを output.fileに複製する
 * 
 * コマンドでcp input.file output.fileとしたときと同様の動作をするようにする
 */
#include <sys/types.h> // open read
#include <stdio.h> // perror printf
#include <stdlib.h> // exit
#include <sys/stat.h> // open
#include <fcntl.h> // open
#include <sys/uio.h> // read
#include <unistd.h> // close read

int main(void) {
    // input.file open
    int input_fd = open("ch03/input.file", O_RDONLY);
    if (input_fd == -1) {
        perror("open input.file");
        exit(1);
    }

    // output.file open
    // ファイルがない場合は作る必要があるのでO_CREATを指定
    int output_fd = open("ch03/output.file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        perror("open output.file");
        exit(1);
    }

    char buf[10];
    ssize_t cc;
    // readした内容をoutput.fileにwrite
    while ((cc = read(input_fd, buf, sizeof(buf))) > 0) {
        // readで読み出し成功したバイト数だけoutput_fdに書き込む
        ssize_t write_cc = write(output_fd, buf, cc);
        if (write_cc == -1) {
            perror("write");
        }
    }
    if (cc == -1) {
        perror("read");
        exit(1);
    }
    // cc = 0; エラーなしでEOFに達した

    if (close(input_fd) == -1) {
        perror("close");
    }
    if (close(output_fd) == -1) {
        perror("close");
    }
    printf("copy to output.file succeed\n");
    return 0;
}