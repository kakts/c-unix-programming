/**
 * @file 1-14.c
 * 
 * 形を表現する共用体 union shapeを定義
 * 
 * 取りうる形は 長方形、三角形、円のいずれかとする
 */
#include <stdio.h>

// 長方形
struct rectangle {
    int x, y, height, width;
};

// 三角形
struct triangle {
    int x1, y1, x2, y2, x3, y3;
};

// 円
struct circle {
    int x, y, r;
};

union shape {
    struct rectangle r;
    struct triangle t;
    struct circle c;
};

int main(void) {
    struct rectangle r = {
        4, 5, 10, 20
    };
    struct triangle t = {
        1,1,
        2,2,
        3,3
    };
    struct circle c = {
        10, 20, 3
    };

    union shape s;
    s.c = c;

    printf("s.x: %d, s.y: %d, s.r: %d", s.c.x, s.c.y, s.c.r);

}

