/**
 * 1-10.c
 * 
 * 2次元座標(x, y)を表す構造体struct pointを定義する x, yはintとする
 * 
 */

#include <stdio.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};

// point型のp1とp2が同一(x, yがともに等しい)か判定する
// 等しい場合は1
int point_is_equal(struct point *p1, struct point *p2) {
    return (p1->x == p2->x) && (p1->y == p2->y);
}

int main(int argc, char *argv[]) {
    struct point origin_data = {1, 10};
    if (argc < 3) {
        printf("Please input x and y.");
        exit(1);
    }
    struct point input_data = {atoi(argv[1]), atoi(argv[2])};

    int result = point_is_equal(&origin_data, &input_data);
    if (result) {
        printf("success. matched.");
    } else {
        printf("failed. not matched.");
    }
    return 0;
}