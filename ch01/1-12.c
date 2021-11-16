/**
 * struct rectangle
 * 長方形と、その長方形を操作する関数を定義して使う
 */
#include <stdio.h>

// 長方形
struct rectangle {
    unsigned int x, y, width, height;
};

// 長方形のデータの表示
void rect_print(struct rectangle *p) {
    printf("rect_print: \n");
    printf("x : y : width : height \n");
    printf("%d : %d : %d : %d\n", p->x, p->y, p->width, p->height);
};

// 面積計算
int rect_area(struct rectangle *p) {
    return p->width * p->height;
}

// 移動1
void rect_move1(struct rectangle *p, unsigned int dx, unsigned int dy) {
    p->x += dx;
    p->y += dy;
    printf("rect moved to (x, y)=(%d, %d)\n", p->x, p->y);
}

// 移動2
// 引数の長方形を修正せずに移動後の長方形を戻り値として返す
struct rectangle rect_move2(struct rectangle r, unsigned int dx, unsigned int dy) {
    r.x += dx;
    r.y += dy;
    return r;
}

// 指定したx, y座標の点が、長方形に含まれているか
int point_is_included(struct rectangle *p, int x, int y) {
    return (p->x <= x) && (x <= p->x + p->width)
        && (p->y <= y) && (y <= p->y + p->height);
}

int rect_is_overlapped2(struct rectangle *p1, struct rectangle *p2) {
    // p2の各頂点が、p1に含まれているかをチェックする
    return point_is_included(p1, p2->x, p2->y)
        || point_is_included(p1, p2->x + p2->width, p2->y)
        || point_is_included(p1, p2->x, p2->y + p2->height)
        || point_is_included(p1, p2->x + p2->width, p2->y + p2->height);

}

// 2つの長方形が重なっているかを判定
// 重なっている場合は1 そうでない場合は0
// 辺や頂点が接触している場合は重なっている
int rect_is_overlapped(struct rectangle *p1, struct rectangle *p2) {
    // それぞれの長方形をベースにして比較する
    return rect_is_overlapped2(p1, p2) || rect_is_overlapped2(p2, p1);
}


int main(void) {
    struct rectangle data1 = {1, 10, 3, 7};
    rect_print(&data1);

    // 面積
    int area = rect_area(&data1);
    printf("area is %d\n", area);

    rect_move1(&data1, 5, 6);

    struct rectangle data2 = rect_move2(data1, 30, 40);
    rect_print(&data2);

    printf("%d\n", rect_is_overlapped(&data1, &data1));
    printf("%d\n", rect_is_overlapped(&data1, &data2));
}