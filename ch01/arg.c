#include <stdio.h>

/**
 * mainの引数確認用
 * *argv []は **argvと書いても同じ
 * 引数に配列を書いても、実際にはその配列の先頭要素へのポインタが渡されるから
 * 
 * argv[]の最後は必ずNULLなのでループの停止条件はargv[i] != NULLとかける
 */
int main (int argc, char *argv []) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("argv [%d] = %s\n", i, argv[i]);
    }
}