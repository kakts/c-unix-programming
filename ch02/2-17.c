/**
 * @file 2-17.c
 * 
 * ポインタpを次のnバイト境界、つまりnの倍数のアドレスに切り上げるマクロROUNDUP(p, n)を定義する
 * ポインタとunsigned intのサイズは同じ、 nは2の冪乗の整数と仮定する
 * 
 * e.g. ROUNDUP(100, 4)は100、 ROUNDUP(101, 4)は104 ROUNDUP(104, 4)は104を返す
 */

#define ROUNDUP(p, n) ((((unsigned int)(p)) + ((n) - 1)) & ~((n) - 1))