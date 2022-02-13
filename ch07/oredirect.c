/**
 * @file oredirect.c
 * 標準出力のリダイレクト
 * 
 * ./a.out foo ls -lとすると、 ls -lの標準出力をファイルfooにリダイレクトして実行する
 * つまり　ls -. > fooと同じ
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd;
    if (argc < 3) {
        fprintf(stderr, "%s filename command [arg...]\n", argv[0]);
        exit(1);
    }

    // リダイレクト先のファイルをオープンする
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    // 標準出力に指定したファイルのfdをコピーする。
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    execvp(argv[2], &argv[2]);
    return 0;
}
