/**
 * @file writebyte.c
 *  
 * ファイルbye.txtにデータを書く
 * 
 * ファイルの先頭から書くので、追記はしない
 */

#include <sys/types.h> // open read
#include <stdio.h> // perror printf
#include <stdlib.h> // exit
#include <sys/stat.h> // open
#include <fcntl.h> // open
#include <sys/uio.h> // read
#include <unistd.h> // close read

int main(void) 
{
    int fd;

    if ((fd = open("ch03/bye.txt", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }
    // ファイルの先頭から書き込む
    if (write(fd, "See you", 7) != 7) {
        perror("write");
        exit(1);
    }
    if (write(fd, " later!", 7) != 7) {
        perror("write");
        exit(1);
    }
    if (write(fd, "\nBye!\n", 6) != 6) {
        perror("write");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}
