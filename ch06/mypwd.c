/**
 * @file mypwd.c
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char buf[PATH_MAX + 1];
    if (getcwd(buf, sizeof(buf)) == NULL) {
        perror("getcwd");
        exit(1);
    }
    printf("%s\n", buf);
    return 0;
}