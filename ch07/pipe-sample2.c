/**
 * @file pipe-sample2.c
 * 
 * パイプで2つのコマンドを接続する
 * ./a.out ls wcは ls | wcと同じ
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd[2];

    pid_t pid;

    // 引数チェック
    if (argc < 3) {
        fprintf(stderr, "%s command1 command2\n", argv[0]);
    }
    
    // パイプ作成
    pipe(fd);

    if ((pid = fork()) == 0) {
        /**
         * 子プロセス command1
         * パイプの書き込み用のfdを標準出力のfdにコピーする
         * 
         * 子プロセス(command1) -> pipe fd[1] -> pipe fd[0] -> 親プロセス(command2)
         */
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        // exec でcommand1を指定して実行する
        // execlpしても、close-on-execフラグのセットしていなければ、fdは引き継がれる
        execlp(argv[1], argv[1], (char *) NULL);
    }

    /**
     * 親プロセス(command2)
     * 
     * パイプ読み込み用のfdを標準入力のfdにコピーする
     * pipe fd[0] -> 親プロセス(command2)
     */
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);

    // exec でcommand2を指定して実行する
    // execlpしても、close-on-execフラグのセットしていなければ、fdは引き継がれる
    execlp(argv[2], argv[2], (char *) NULL);

    return 0;
}
