/**
 * @file q4-7.c
 * struct person 型の構造体10個からなる配列 struct person a[10]にデータが入っているとする
この配列をそのまあmpersondata.dbという名のファイルにfwriteを使って格納するコードを書く
 */
#include <stdio.h>
#include <stdlib.h>
// データ項目ごとのバイト数
enum {
    NAMELEN = 32, // 名前
    PHONELEN = 16, // 電話番号
    DATA_NUM = 10,
};

// 各ユーザのデータ
struct person {
    char name[NAMELEN + 1];
    char phone[PHONELEN + 1];
    int isprivate; 
};

int main(void)
{
    struct person a[DATA_NUM] = {
        {
            "test1",
            "09000000001",
            0
        },
        {
            "test2",
            "09000000002",
            0
        },
        {
            "test3",
            "09000000003",
            0
        },
        {
            "test4",
            "09000000004",
            1
        },
        {
            "test5",
            "09000000005",
            1
        },
        {
            "test6",
            "09000000006",
            1
        },
        {
            "test7",
            "09000000007",
            0
        },
        {
            "test8",
            "09000000008",
            0
        },
        {
            "test9",
            "09000000009",
            0
        },
        {
            "test10",
            "09000000010",
            0
        },
    };
    FILE *person_data_fp;

    person_data_fp = fopen("ch04/persondata.db", "a");
    if (person_data_fp == NULL) {
        perror("fopen");
        exit(1);
    }

    if (fwrite(a, sizeof(struct person), DATA_NUM, person_data_fp) < DATA_NUM) {
        perror("fwrite");
        exit(1);
    }

    fclose(person_data_fp);
}