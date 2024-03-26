#include <stdio.h>
#include <stdint.h>

int main1()
{
    short int c; // occupa due byte
    short int *p = &c;
    c = 65;
    printf("%d\n", c);  // 65
    printf("%x\n", c);  // 41
    printf("%lx\n", &c);// 4000 (solo il primo indirizzo, anche se occupa due byte)
    *p = 90;
    printf("%c\n", c);  // Z
    *(p + 1) = 0x20;
    return 0;
}

