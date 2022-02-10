/**
 * @file stat0.c
 * 
 * stat(2)を使ってファイル属性を取得
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // statの戻り値の型。 ファイル属性
    struct stat sb;
    if (stat(argv[1], &sb) != 0) {
        perror("stat");
        exit(1);
    }

    printf("Information for %s:\n", argv[1]);
    printf(" st_ino = %d\n", (int) sb.st_ino);
    printf(" st_mode = %d\n", (int) sb.st_mode);
    printf(" st_nlink = %d\n", (int) sb.st_nlink);
    printf(" st_uid = %d\n", (int) sb.st_uid);
    printf(" st_gid = %d\n", (int) sb.st_gid);
    printf(" st_size = %d\n", (int) sb.st_size);

    return 0;
}
