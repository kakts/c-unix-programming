/**
 * @file 1-8.c
 * strlolにlong型の範囲を超える大きな数を与えた場合
 * エラーにならずLONG_MAX(int 64最大値 9223372036854775807)が返る
 * また整数を表さない文字列("10xyz")を与えてもエラーにならず、10が返る。
 * xを発見した時点で変換をやめて、それまでの変換結果を返すのがその理由
 * 
 * ./a.out 9223372036854775808
 * 9223372036854775807
 * 
 * ./a.out 10xyz
 * 10
 * 
 * このプログラムを修正して、上の実行例をエラーとするようにエラー処理のコードを加える
 */

#include <stdlib.h> // strtol
#include <stdio.h> // printf
#include <errno.h> // ERANGE
#include <limits.h> // strtol LONG_MAX

int main (int argc, char *argv[]) {

    // 注意点として、errnoが実行時にすでに0以外の場合、正常でも予期せぬ不具合になるので
    // strtolの実行前にerrnoを0に設定しておく
    // SUSv4[6]に strtol関数は成功時にはerrnoを変更しないとあるので、この方法が使える
    errno = 0;
    
    // strtolの第1引数に変な文字が入っているかの検知には、strtolの第2引数を使う
    // strtolは変換をやめた位置を第2引数にセットする
    char* test = NULL;
    long val = strtol (argv[1], &test, 0);
    printf("LONG_MAX is %ld\n", LONG_MAX);
    if (val == LONG_MAX) {
        // 範囲越えエラーの場合errnoにERANGEがセットされる
        if (errno == ERANGE) {
            int old_errno = errno;
            perror("strtol: ERANGE");

            exit(1);
        }
    } else if (test != NULL) {
        printf("strtol: data cannot be parsed all. test:%s", test);
        exit(1);
    }
    printf("success test:%s \n", test);
    printf("%ld\n", val);
}

/**
 * 本に記載の正解版
 */
int main2(int argc, char *argv[]) {
    long val;
    char *end;

    errno = 0;
    val = strtol(argv[1], &end, 0);
    if (errno != 0) {
        // 何かしらエラーがあったらperrorで終了
        perror("strtol");
        exit(1);
    }
    // NULL文字でない = 変な文字が入っていたエラー
    if (end[0] != '\0') {
        fprintf(stderr, "Non-digit character: %c\n", end [0]);
        exit(1);
    }
    printf("%ld\n", val);
}