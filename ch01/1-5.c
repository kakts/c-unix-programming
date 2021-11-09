#include <stdio.h>
#include <unistd.h> // rmdir
#include <stdlib.h>
int main(void) {
    int res = rmdir("./ch01/foo");
    if (res == -1) {
        perror("rmdir");
        exit(1);
    }
    exit(0);
}