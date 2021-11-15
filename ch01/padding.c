/**
 * 1.5.3 padding
 * 
 * 
 */
#include <stdio.h>

struct foo {
    char a;
    int b;
} f;

/**
 * 
 * **アラインメントとは**
 * 境界調整のこと
 * intのデータは4の倍数のアドレスに置かないといけない　などの規則がある。
 * アラインメント規則はプラットフォームごとに異なる。
 * これに反すると、bus errorや、実行速度低下や他のプログラムとのデータ交換に師匠が生じる。
 * 普通に使う分には詰め物を意識する必要がない
 * 他のプラットフォームとバイナリデータを交換する場合は詰め物に注意が必要。
 * 
 * ここではint charで合わせて5バイトなのにstructは8バイトと表示される
 */
int main (void) {
    printf("%zu, %zu, %zu\n", sizeof(char), sizeof(int), sizeof(struct foo));
    printf("%p, %p, %p\n", &f, &f.a, &f.b);
}