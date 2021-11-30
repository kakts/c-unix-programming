/**
 * @file readhello.c
 * 
 * ファイルhello.txtから10バイトずつデータを読むプログラム
 * 
 * このプログラムはhello.txtから読んだデータの中身は使ってない
 * read(2)は読んでデータをヌル文字終端(文字列の最後にヌル文字\0を置いて、文字列の終わりを示すこと)
 * をしない。
 * そのためbufの内容を文字列として使うとおかしなことになる
 * そのまま表示するとbufに続くメモリ領域のゴミデータまで文字として表示されて画面が崩れたり、
 * 読み書きしてはいけないメモリ領域に対して読み書きしてプロセスが強制終了することがある
 */
#include <sys/types.h> // open read
#include <stdio.h> // perror printf
#include <stdlib.h> // exit
#include <sys/stat.h> // open
#include <fcntl.h> // open
#include <sys/uio.h> // read
#include <unistd.h> // close read

int main(void) {
    int fd;
    ssize_t cc;
    char buf[10];

    // 読みとり専用でファイルを開く
    if ((fd = open("ch03/hello.txt", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }
    // sizeof(buf)がコンパイル時にバッファの大きさ(10byte)になる
    while((cc = read(fd, buf, sizeof(buf))) > 0) {
        // ccに読んだバイト数 bufに読んだデータが入っている
        printf("%d bytes read\n", (int) cc);
    }
    if (cc == -1) {
        perror("read");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}