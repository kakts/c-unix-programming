#include <stdio.h>

struct point {
    int x;
    int y;
};

enum style {
    SOLID, // 直線
    DASHED, // 破線
    DOTTED // 点線
};

struct line {
    struct point *point1;
    struct point *point2;
    enum style line;
};

void print_line_data(struct line *data) {
    printf("line data\n");
    printf("point1. (x,y)=(%d,%d)\n", data->point1->x, data->point1->y);
    printf("point2. (x,y)=(%d,%d)\n", data->point2->x, data->point2->y);
    printf("style: %d\n", data->line);
}

int main(void) {
    struct point point1 = {
        10,
        20
    };
    struct point point2 = {
        4,
        5
    };
    
    struct line data1 = {
        &point1,
        &point2,
        DASHED
    };

    struct point point3 = {
        4,
        6
    };
    struct point point4 = {
        8,
        9
    };
    
    struct line data2 = {
        &point3,
        &point4,
        DOTTED
    };


    struct line data_list[] = {data1, data2};
    int size_of_data_list = sizeof(data_list) / sizeof(struct line);
    for (int i = 0; i < size_of_data_list; i++) {
        printf("---------------------\n");
        printf("data %d\n", i);
        print_line_data(&data_list[i]);
    }

}