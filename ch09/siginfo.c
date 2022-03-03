/**
 * @file siginfo.c
 * 
 * sigactionのSA_SIGINFOフラグの例
 * SA_SIGINFOをセットするとき、シグナルハンドラの引数は3つにする。
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// SA_SIGINFOフラグをセットする場合、シグナルハンドラの引数3つ指定する。そのなかでsiginfo_t型のポインタの引数に
// シグナルの情報があり、それを利用できる
void handler(int sig, siginfo_t *info, void *q)
{
    fprintf(stderr, "faulting address = %p\n", info->si_addr);
}

int main(void)
{
    struct sigaction act;
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGBUS, &act, NULL);

    {
        int *p = (int*) 0x123;
        printf("%d\n", *p);
    }
}