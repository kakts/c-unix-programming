/**
 * @file getpath.c
 * 
 * ch05 5.2 q5.6
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *env_name = "PATH";

    char *path_str;
    if ((path_str = getenv(env_name)) != NULL) {
        printf("PATH = %s\n", path_str);
    } else {
        printf("PATH not set\n");
    }

    return 0;

}