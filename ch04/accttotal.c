/**
 * @file accttotal.c
 * 
 * q4.6 acctbook.txtを読み、引数で指定した日の支出総額を計算して表示させる
 * 
 * cat ch04/acctbook.txt
 * 2021/12/30 100.00 pc
 * 2021/12/30 2000.00 ccc
 * 
 * この時に
 * ./accttotal 21/12/30
 * 2021/12/30 2100.00
 * 
 * となるようにする
 * 
 * 年として100未満の数が指定されたら、2000年代であると解釈する
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ACCTBOOK "ch04/acctbook.txt"

enum {
    MAXDATELEN = 12,
    MAXLINELEN = 80,
    BUFLEN = MAXDATELEN + 1,

};

int main(int argc, char const *argv[])
{
    FILE *fp;
    int year, month, day;
    char date[MAXDATELEN];
    char str[MAXLINELEN];
    if (argc != 2) {
        fprintf(stderr, "please set arg like year/month/day eg) ./a.out 21/12/30");
        exit(1);
    }
    /* code */
    // year month dayの3つの変数に入力成功できたかどうかのチェック
    if (sscanf(argv[1], "%d/%d/%d", &year, &month, &day) != 3) {
        fprintf(stderr, "value \"%s\" invalid: ignored\n", argv[1]);
    }

    // yearが100未満の場合、2000年台であると解釈する
    if (year < 100) {
        year += 2000;
    }

    // ${year}/${month}/${day}にする
    sprintf(date, "%d/%d/%d", year, month, day);

    // 家計簿ファイルをオープンする
    if ((fp = fopen(ACCTBOOK, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    int record_count = 0;
    double read_price = 0.0;
    double sum_price = 0.0;
    // 1行ずつ読み込み
    while(fgets(str, MAXLINELEN, fp) != NULL) {
        // 先頭がdateに一致する場合、数値を加算する
        if (strncmp(str, date, 10) == 0) {
            record_count += 1;
             
            // 自分の解答 sscanf(str, "%04d/%02d/%02d %lf %s\n", &read_year, &read_month, &read_day, &read_price, &read_description) != 5
            // *関係ない部分は変数に入れずに捨てたい場合は *というオプションを使う
            if (sscanf(str, "%*s %lf", &read_price) != 1) {
                fprintf(stderr, "value \"%s\" invalid; ignored\n", str);
                exit(1);
            }

            sum_price += read_price;
        }
    }
    printf("result recourd_count: %d, date: %s, sum_price %.2f\n", record_count, date, sum_price);
    fclose(fp);
    return 0;
}
