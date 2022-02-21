/**
 * @file client_name.c
 * 
 * ソケットクライアント
 * 接続先がホスト名を指定し、それをIPに解決するバージョン
 * サーバにコネクション接続リクエストを送り、サーバから受信したデータをそのまま画面に表示する
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h> // inet_addr
#include <arpa/inet.h> // htons, inet_addr
#include <sys/uio.h> // read write
#include <unistd.h>
#include <netdb.h>

#define SERVER_NAME "localhost"
#define SERVER_PORT 12345

int main(void)
{
    int s, cc;

    struct sockaddr_in sa;
    char buf[1024];

    // ホスト名解決用の型
    struct hostent *hp;

    // ホスト名の解決
    if ((hp = gethostbyname(SERVER_NAME)) == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    // ソケット作成 IPv4 TCP
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 接続先の名前を作る IPとポート番号の情報を指定する
    memset(&sa, 0, sizeof(sa)); // ゼロクリア
    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT); // ホストバイトオーダーからネットワークバイトオーダー(short 16bit)へ変換するためにhtonsを使う
    // 名前解決したデータをsa.sin_addrに入れる
    // その際に、型が違うのでmemmoveをつかってバイトごとにコピーする
    memmove(&sa.sin_addr, hp->h_addr_list[0], sizeof(sa.sin_addr));


    // サーバに接続
    fprintf(stderr, "Connectiong to the server ...\n");
    if (connect(s, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
        perror("connect");
        exit(1);
    }
    fprintf(stderr, "Connected.\n");

    // サーバから通信文を受け取り、画面に表示
    fprintf(stderr, "Message from the server:\n\n");
    // クライアントの場合、サーバからEOFが変える時にreadの戻り値が0になる。　0にならない間はreadを続ける
    while((cc = read(s, buf, sizeof(buf))) > 0) {
        // readで読み取ったバイト数だけ、bufで受け取ったデータをstdoutに書き込む
        write(STDOUT_FILENO, buf, cc);
    }

    if (cc == -1) {
        perror("read");
        exit(1);
    }
    fprintf(stderr, "\n\nFinished receiving.\n");

    // 通信を止める
    if (shutdown(s, SHUT_RDWR) == -1) {
        perror("shutdown");
        exit(1);
    }

    // ソケットを閉じる
    fprintf(stderr, "Closing client socket.\n");
    if (close(s) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}