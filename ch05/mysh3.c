/**
 * @file mysh3.c
 * 
 * バックグラウンド実行対応シェル
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../sub/mysub.h"
#include "../sub/myvec.h" // strtovec

enum {
    MAXARGV = 100,
};

int main(void)
{
    char cmd[1024];
    char *av[MAXARGV];
    int ac, status, bg;
    pid_t cpid, zpid;

    for (;;) {
        // ゾンビがいたらwaitする
        // WNOHANGを指定　それ以上waitされるべき子プロセスがなければwaitpidは戻り値0で戻る
        while ((zpid = waitpid(-1, &status, WNOHANG)) > 0) {
            fprintf(stderr, "process %d salvaged\n", zpid);
        }

        if (zpid == -1 && errno != ECHILD) {
            perror("waitpid(2)");
            exit(1);
        }

        getstr("@ ", cmd, sizeof(cmd));
        if (feof(stdin)) {
            exit(0);
        } else if (ferror(stdin)) {
            perror("getstr");
            exit(1);
        }

        if ((ac = strtovec(cmd, av, MAXARGV)) > MAXARGV) {
            fputs("argument list too long\n", stderr);
            continue;
        }

        // 最後のヌルポインタの分を省く
        ac--;
        if (ac == 0) {
            // 入力がない場合
            continue;
        }
        if (!strcmp(av[ac - 1], "&")) {
            av[ac - 1] = NULL;
            ac--;
            bg = 1;
            if (ac == 0) {
                fputs("invalid null command\n", stderr);
                continue;
            }
        } else {
            bg = 0;
        }
        if ((cpid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if (cpid == 0) {
            // 子プロセス
            execvp(av[0], av);
            perror(av[0]);
            exit(1);
        }

        // 親プロセス
        if (!bg) {
            // 子プロセスを待つ
            if (waitpid(cpid, &status, 0) == (pid_t) -1) {
                perror("waitpid(1)");
                exit(1);
            }
            // フォアグラウンドのプロセスが終了した
            fprintf(stderr, "process %d finished \n", cpid);
        }
    }
    exit(0);
}