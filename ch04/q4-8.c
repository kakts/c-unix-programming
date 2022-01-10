/**
 * @file q4-8.c
 * 
 * フラッシュのタイミング
 * 
 * stdoutに書いたデータがwrite(2)されるのはどの文を時効した時か？
 * stderrについてはどうか？
 * 
 * stderrは、stderrに出力されたときにwrite(2)される
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int age;
    printf("Welcome!\n"); // 1: 改行で終わるのですぐに出力
    printf("your age: "); // 2: バッファに残る
    fprintf(stderr, "Input "); // 3: stderrへの出力 2より先に表示される
    scanf("%d", &age); // 4: scanfにより、全ての行バッファリングのストリームがフラッシュされるのでこのときに2が表示される
    printf("Your age is %d", age); // 5: 改行がないのでバッファにたまる
    fprintf(stderr, "Thank you!"); // 6: stderrへの出力のため即座に表示される
    printf("\nBye!"); // 7: 改行で始まるので、この実行で5が表示されるが、改行文字のあとのBye!の部分はバッファに残る
    sleep(3);
    exit(0); // 8: exitの呼び出しでストリームがフラッシュされるので、7のBye!が表示される
}