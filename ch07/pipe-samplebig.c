/**
 * @file pipe-samplebig.c
 * 
 * pipeの使用例
 * プロセス間通信でなく、パイプに書いたデータを自分で読むだけ
 * 
 * 演習問題7.2 
 * コード例7.2を参考にし、パイプ中のバッファよりも大きいサイズ(例1MB)を書き込むとパイプが詰まり、
 * ブロックしたまま実行できなくなることを確認する
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

// 適当に大きいサイズを定義
enum {SIZE = 1024 * 1024};

int main(void)
{
    int fd[2], nbytes;
    char buf [SIZE], buf2 [SIZE];

    // パイプの作成
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // pipeで受け取った書き込み用のファイル記述子をしていして書き込む
    /**
     * ここでブロックし続ける
     *
     * バッファの最大値を超えて書き込んだ時、バッファが溢れてwriteは永遠にブロックし続ける。
     * その場合次のreadに処理が映らないので、ブロックしたまま実行が進まなくなる
     */
    write(fd[1], buf2, sizeof(buf2));

    /**
     * パイプから読む
     * 
     * writeによりパイプに対して書き込まれたデータは、パイプが管理しているバッファに書き込まれる。
     * readによって、そのバッファのデータを読み込む。
     * read時に、バッファにデータがない場合は、バッファにデータが入ってくるまでブロックされる
     * 
     */
    nbytes = read(fd[0], buf, sizeof(buf));

    // パイプの後始末。
    close(fd[0]);
    close(fd[1]);
    
    return 0;
}