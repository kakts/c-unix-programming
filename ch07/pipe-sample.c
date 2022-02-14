/**
 * @file pipe-sample.c
 * 
 * pipeの使用例
 * プロセス間通信でなく、パイプに書いたデータを自分で読むだけ
 * 
 * pipe(fd[2])実行により、fdの配列の2要素にファイル記述子がセットされる 
 * - fd[0]: パイプの読み込み口を表すファイル記述子
 * - fd[1]: パイプの書き込み口を表すファイル記述子
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(void)
{
    int fd[2], nbytes;
    char buf [1024];

    // パイプの作成
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // pipeで受け取った書き込み用のファイル記述子をしていして書き込む
    /**
     * バッファの最大値を超えて書き込んだ時、バッファが溢れてwriteは永遠にブロックし続ける。
     * その場合次のreadに処理が映らないので、ブロックしたまま実行が進まなくなる
     */
    write(fd[1], "Hello\n", 6);

    /**
     * パイプから読む
     * 
     * writeによりパイプに対して書き込まれたデータは、パイプが管理しているバッファに書き込まれる。
     * readによって、そのバッファのデータを読み込む。
     * read時に、バッファにデータがない場合は、バッファにデータが入ってくるまでブロックされる
     * 
     */
    nbytes = read(fd[0], buf, sizeof(buf));

    // 読み込んだデータを標準出力に書き出す
    write(STDOUT_FILENO, buf, nbytes);

    // パイプの後始末。
    close(fd[0]);
    close(fd[1]);
    
    return 0;
}