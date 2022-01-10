/**
 * @file writeout.c
 * 
 * q3-4
 * stdinから読んだデータをファイルoutput.fileに書く
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>


int main(void)
{
    int ofd;
    ssize_t cc;
    char buf[10240];

    if ((ofd = open("ch03/output_write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) 
    {
        perror("open");
        exit(1);
    }
    while ((cc = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
    {
        // 読み取ったバイト数だけ書き込む
        if (write(ofd, buf, cc) < cc) 
        {
            perror("write");
            exit(1);
        }
    }
    if (cc == -1)
    {
        perror("read");
        exit(1);
    }
    if (close(ofd) == -1)
    {
        perror("close");
        exit(1);
    }
    return 0;   
}