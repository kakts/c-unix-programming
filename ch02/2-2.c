/**
 * @file 2-2.c
 * 
 * wrong_mainのコードにあるポインタの間違いを見つけて修正する
 */

#include <termios.h>
#include <unistd.h>

// int wrong_main(void)
// {
//     struct termios *tp;
//     tcgetattr(STDIN_FILENO, tp);
// }

/**
 * wrong_mainではポインタ変数tpが未初期化
 * tcgetattrにはtermios構造体へのポインタを渡す必要がある
 * termios構造体を格納する変数tを定義して、&tを渡すようにする
 */
int main(void)
{
    // ポインタ変数tpを初期化する
    struct termios tp;
    tcgetattr(STDIN_FILENO, &tp);
}