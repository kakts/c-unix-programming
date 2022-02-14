/**
 * @file iredirect.c
 * 
 * 演習問題7.1 
 * コード例7.1を参考
 * 標準入力のリダイレクトをするプログラム
 * 
 * ./iredirect foo grep abcを実行すると grep abc < fooと同じ効果が得られる
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

    // リダイレクト元の入力用ファイルをオープンする
    fd = open(argv[1], O_RDONLY, 0666);

    // 標準出力に指定したファイルのfdをコピーする。
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    // 指定したコマンドを実行する。 stdinはファイルの内容から読み込む
    execvp(argv[2], &argv[2]);
    return 0;
}
