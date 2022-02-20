/**
 * @file chatserver.c
 * 
 * 8.8 selectを使ったチャットサーバ
 * 
 * 1サーバプロセスで実現する
 * クライアントの1回の発言は改行文字で終わると仮定する
 * 
 * 動作確認方法
 * このプロセスを立てた後、telnet(1)を使って12345番ポートに接続
 * telnet {ip} 12345
 */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

enum {
    SERVER_PORT = 12345,
    NQUEUESIZE = 5,
    MAXCLIENTS = 10, // 最大クライアント数
};

// クライアントにつながっている記述子の一覧
int clients[MAXCLIENTS];
// 現在接続しているクライアント数
int nclients = 0;

/**
 * クライアント接続数が上限に達して接続できない場合のメッセージ送信
 */
void sorry(int ws) {
    char *message = "Sorry, it's full.\n";
    write(ws, message, strlen(message));
}

/**
 * 記述子wsを記述子一覧から取り除く
 */
void delete_client(int ws) {
    int i;

    for (i = 0; i < nclients; i++) {
        if (clients[i] == ws) {
            clients[i] = clients[nclients - 1];
            nclients--;
            break;
        }
    }
}

/**
 * ソケットwsから来る一行を全てのクライアントに送る
 */
void talks(int ws) {
    int i, cc;
    char c;

    do {
        // ソケットwsからデータを読み取る
        if ((cc = read(ws, &c, 1)) == -1) {
            perror("read");
            exit(1);
        } else if (cc == 0) {
            // EOF クライアントが通信路を切った
            shutdown(ws, SHUT_RDWR);
            close(ws);
            // クライアントの情報削除
            delete_client(ws);
            fprintf(stderr, "Connection closed on descriptor %d\n", ws);
            return;
        }

        for (i = 0; i <nclients; i++) {
            write(clients[i], &c, 1);
        }
    } while (c != '\n');
}

int main(void)
{
    int s, soval;
    struct sockaddr_in sa;

    // TCPチャットサーバ用のソケット作成
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    soval = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // bind用の情報のゼロクリア
    memset(&sa, 0, sizeof(sa));
    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT); // ホストバイトオーダーをネットワークバイトオーダーに変換した上でセットする
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(s, NQUEUESIZE)) {
        perror("listen");
        exit(1);
    }

    fprintf(stderr, "Ready. \n");

    for (;;) {
        int i, maxfd;
        fd_set readfds;

        // selectのための記述子集合を作る
        FD_ZERO(&readfds); // フラグを全部0にして初期化
        FD_SET(s, &readfds); // 接続待ちソケットを見張る
        maxfd = s;

        // つながっているクライアントからの発言がないか見張る
        for (i = 0; i < nclients; i++) {
            FD_SET(clients[i], &readfds);
            if (clients[i] > maxfd) {
                // maxfdの更新
                maxfd = clients[i];
            }
        }

        // いずれかの記述子の準備ができるまで待つ
        if (select(maxfd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(1);
        }

        // 新しい接続かどうか判定
        if (FD_ISSET(s, &readfds)) {
            struct sockaddr_in ca;
            socklen_t ca_len;
            int ws;

            ca_len = sizeof(ca);
            if ((ws = accept(s, (struct sockaddr *) &ca, &ca_len)) == -1) {
                perror("accept");
                continue;
            }

            if (nclients >= MAXCLIENTS) {
                // 満杯の場合
                sorry(ws);
                shutdown(ws, SHUT_RDWR);
                close(ws);
                fprintf(stderr, "Refused a new connection \n");
            } else {
                clients[nclients] = ws; // 記述子一覧に加える
                nclients++;
                fprintf(stderr, "Accepted a connection on descriptor %d\n", ws);
            }
        }

        // 発言があればそれを前クライアントに送る
        for (i = 0; i < nclients; i++) {
            if (FD_ISSET(clients[i], &readfds)) {
                talks(clients[i]);
                // talksはclients[]とnclientsを変えることがある
                break;
            }
        }
        // ループ先頭に戻り再びselectする
    }
}