/**
 * @file popen--sample.c
 * 
 * コード例7.4 popenとpcloseの例
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    char buf[1024];

    // ls -l *c | wcのコマンドの実行結果を読み取れるストリームを取得
    if ((fp = popen("ls -l ch07/*.c | wc", "r")) == NULL) {
        perror("popen");
        exit(1);
    }

    fgets(buf, sizeof(buf), fp);

    printf("%s", buf);
    pclose(fp);
}