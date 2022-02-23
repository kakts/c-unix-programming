/**
 * @file alarm.c
 * 
 * alarm(2)の確認用
 */
#include <stdio.h>
#include <unistd.h>

void loop (void) {
    int i;
    for (i = 0; i < 0xFFFFFF; i++) {
        // 時間稼ぎ用のループ
    }
}

int main(void)
{
    alarm(3);
    while (1) {
        loop(); // 時間稼ぎ
        printf(".");
        fflush(stdout);
    }
}
