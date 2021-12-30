/**
 * @file acctadd.c
 * 
 * コード例4.8 家計簿プログラム
 * 
 * 今日の支出を家計簿ファイルに追加する
 * 家計簿ファイルはテキストファイル
 * 1項目1行 日付、金額,使途を記録する
 */
#include <stdio.h> 
#include <string.h> // strchr
#include <time.h>

#define ACCTBOOK "ch04/acctbook.txt"
enum {
    MAXLINELEN = 80,
    BUFLEN = MAXLINELEN + 1,
};

int main(void)
{
    // file stream
    FILE *fp;

    char buf[BUFLEN];
    char item[BUFLEN], value[BUFLEN];
    time_t unixtime;
    struct tm now;
    int year, month, day;
    double val;
    char *p;

    /**
     * 日付をシステムの時刻から得る
     */

    // unixtimeで取得
    unixtime = time(NULL);
    // time_tの時刻から、日付の情報を得てstruct tmの変数に入れる
    localtime_r(&unixtime, &now);
    year = now.tm_year + 1900;
    month = now.tm_mon + 1; // tm_mon = 0..11
    day = now.tm_mday;

    // ファイルオープン
    fp = fopen(ACCTBOOK, "a");
    for (;;) {
        fputs("item?", stderr);
        // stdinから読み込み、itemに入れる
        fgets(item, sizeof(item), stdin);

        if (feof(stdin)) {
            break;
        }
        if ((p = strchr(item, '\n')) != NULL) {
            // \nを切り落とす
            *p = '\0';
        }
        fputs("value? ", stderr);
        // stdinから読み込み、valueに入れる
        fgets(value, sizeof(value), stdin);
        if (sscanf(value, "%lf", &val) != 1) {
            fprintf(stderr, "value \"%s\" invalid; ignored\n", value);
            continue;
        }
        if (snprintf(buf, sizeof(buf), "%04d/%02d/%02d %.2f %s\n", year, month, day, val, item) >= sizeof(buf)) {
            buf[sizeof(buf) - 2] = '\n';
            fprintf(stderr, "Warning: entry too long; truncated to \n%s", buf);
        }
        fputs(buf, fp);
    }
    fclose(fp);
    putc('\n', stderr);
    return 0;

}