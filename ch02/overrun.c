/**
 * @file overrun.c
 * バッファオーバーランの例
 * strlenの結果に+1死忘れたため、ヌル文字書き込みがバッファオーバーランする
 */

#include <stdlib.h> // malloc
#include <string.h> // strcpy strlen

int main(void)
{
    char *s2 = "hello";
    // NULL文字分が考慮されていない
    char *s1 = malloc(strlen(s2));

    // s1にs2の内容をコピーしようとする
    strcpy(s1, s2);
}
