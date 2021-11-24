#include <stdlib.h> // malloc

int main(void)
{
    int *p = malloc(sizeof(int));
    *p = 10;
    // ↑で確保したメモリはfreeされておらず、参照がないのでfreeできない
    p = malloc(sizeof(int));
}