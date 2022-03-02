/**
 * @file whackamole.c
 * 
 * もぐらたたき
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int out = 0; // 1 もぐらがでている 0 でていない
int hit = 0;
int miss = 0;

void whack(int sig)
{
    signal (SIGINT, whack); // SVR4の場合はコメントを外す
    if (out) {
        putchar('!');
        hit++;
        out = 0;
    } else {
        miss++;
    }
}

int main(void)
{
    int i;

    setbuf(stdout, NULL);

    srandom((unsigned long) time(NULL));
    signal(SIGINT, whack);

    printf("*** Whack-a-Mole ***\nInterruput (^C) "
            "to hit the mole. Game time is 15 seconds.\n");

    for (i = 3; i > 0; i--) {
        printf("%d", i);
        sleep(1);
    }

    printf("Start!\n");
    for (i = 0; i < 15; i++) {
        if (out) {
            if (random() % 3 < 2) {
                // 2/3の確率で顔を引っ込める
                out = 0;
                putchar('_');
            }
        } else if (random() % 6 == 0) {
            // 1/6の確率で顔を出す
            out = 1;
            putchar('O');
        }
        sleep(1);
    }

    printf("\nFinish!\n");
    printf("hit = %d, miss = %d\n", hit, miss);
    printf("Your score is %d points!\n", hit - miss);
    return 0;
}