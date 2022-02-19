/**
 * @file iserver2.c
 * 
 * TCP用サーバ client.cによって接続を受ける
 * クライアントとのコネクション確立後、サーバの画面から通信文を入力するとその通信文がクライアントに送られるようにする。
 * 通信文はキーボードで^Dをおして終わる
 */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 12345

enum {
    NQUEUESIZE = 5 // listenのための待ち行列枠数
};

void send_message(int s) {
    char buf[1024];
    
    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        if (write(s, buf, strlen(buf)) == -1) {
            fprintf(stderr, "send error\n");
            return;
        }
    }
    // fgetsでstdinからの入力が終了した場合stdinのEOFフラグが立ってしまう。
    // EOFフラグが立ったままだと、クライアントからの2回目以降の接続時にstdinからの読み込みができなくなるため
    // clearerrによってstdinのEOFフラグを削除する必要がある
    clearerr(stdin);
}

int main(void)
{
    int s, ws, soval, cc;
    struct sockaddr_in sa, ca;
    socklen_t ca_len;
    char message[1024];

    // ソケット作成
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    /**
     * アドレス再利用の設定
     */
    soval = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // ソケットに名前をつける
    memset(&sa, 0, sizeof(sa)); // ゼロクリア
    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT); // ホストバイトオーダーからネットワークバイトオーダー(short 16bit)へ変換するためにhtonsを使う
    sa.sin_addr.s_addr = htonl(INADDR_ANY); // ipとループバックアドレスなど、ホストに設定されているアドレスならどれでも受け付ける

    // bindすることにより、ソケットに名前をつける
    if (bind(s, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
        perror("bind");
        exit(1);
    }

    // 待ち行列の準備
    if (listen(s, NQUEUESIZE)) {
        perror("listen");
        exit(1);
    }

    fprintf(stderr, "Ready.\n");

    for (;;) {
        // メッセージのゼロクリア
        strcpy(message, "");
        // 接続を受け入れる。
        fprintf(stderr, "Waiting for a connetion...\n");

        ca_len = sizeof(ca);
        if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
            perror("accept");
            exit(1);
        }
        fprintf(stderr, "Connection established.\n");
        
        // クライアントに通信文を送る
        send_message(ws);

        // サーバからクライアントへの送信終了
        fprintf(stderr, "Stopping sending messages from server.");
        // 通信をとめる。
        if (shutdown(ws, SHUT_RDWR) == -1) {
            perror("shutdown");
            exit(1);
        }

        // 接続済みソケットを閉じる
        if (close(ws) == -1) {
            perror("close");
            exit(1);
        }

        // 次の要求の受け入れへ
    }
}
