/**
 * ESERCIZIO 2
 * Determinare se l'architettura è little endian o 
 * big endian. Scrivere poi una funzione che inverte 
 * l'ordine dei dati in una variabile int a 32 bit.
*/

#include <stdint.h>

void endianness(){
    uint16_t i = 1;
    uint8_t* c = (uint8_t*)&i;
    if(*c==0)
        printf("%s","Big Endian");
    else
        printf("%s","Little Endian");
}

int main(){
    uint16_t i = 0x0102;   // unsigned short
    uint16_t* p = &i;
    uint8_t* c = (uint8_t*)&i;

    printf("uint16_t i = 0x%lx;\n",i);
    printf("\n","");

    printf("%s\n","uint16_t* p = &i;");
    printf("p:\t%lx\n",p);
    printf("*p:\t%lx\n",*p);
    printf("p+1:\t%lx\n",p+1);
    printf("*p+1:\t%lx\n",*(p+1));
    printf("\n","");

    printf("%s\n","uint8_t* c = (char*)&i;");
    printf("c:\t%lx\n",c);
    printf("*c:\t%lx\n",*c);
    printf("c+1:\t%lx\n",c+1);
    printf("*c+1:\t%lx\n",*(c+1));
    printf("\n","");

    endianness();
}