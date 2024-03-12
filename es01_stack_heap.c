/**
 * ESERCIZIO 1
 * Iddentificare in un programma ricorsivo
 *  - posizione area statica
 *  - direzione di crescita e posizione di
 *     - heap
 *     - stack
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

short int global1 = 2;
short int global2 = 3;
short int uglobal1;
short int uglobal2;

void func(int i);
void* fine_heap();

void main()
{

    short int i1 = 0x0001;
    short int i2 = 0x0001;

    // char* str = binaryString(&i, sizeof(i));
    // printf("%s\n",str);
    // free(str);

    printf("\n%s\n", "AREA DELLO STACK");
    printf("0x%lx \t: %s\n", &i1, "prima variabile dello stack del main");
    printf("0x%lx \t: %s\n", &i2, "seconda variabile dello stack del main");

    func(3);

    printf("\n%s\n", "AREA DI MEMORIA DINAMICA (non è l'inizio dello heap, carica dove vuole lui)");
    void *ptr1 = malloc(256);
    printf("0x%lx \t: %s\n", ptr1, "inizio della prima area dinamica allocata dal main");

    void *temp_ptr = realloc(ptr1, 257);

    void *ptr2 = malloc(256);
    printf("0x%lx \t: %s\n", ptr2, "inizio della seconda area dinamica allocata dal main");
    printf("%s\n", "Rialloco la prima area con una dimensione uguale a quella di prima");
    void *temp = realloc(ptr1, 256);
    if (temp == NULL)
    {
        printf("\n%s\n", "Allocation failure");
        free(ptr1);
        free(ptr2);
        return;
    }
    ptr1 = temp;    // allocation succeded, continua ad usare solo ptr1
    printf("0x%lx \t: %s\n", ptr1, "puntatore riallocato");

    printf("%s\n", "Rialloco la prima area con una dimensione maggiore");
    temp = realloc(ptr1, 304);
    if (temp == NULL)
    {
        printf("\n%s\n", "Allocation failure");
        free(ptr1);
        free(ptr2);
        return;
    }
    ptr1 = temp;
    printf("0x%lx \t: %s\n", ptr1, "puntatore riallocato");

    free(ptr1);
    free(ptr2);

    printf("\n%s\n", "AREA DI MEMORIA STATICA");
    printf("0x%lx \t: %s\n", &uglobal1, "prima variabile globale non inizializzata");
    printf("0x%lx \t: %s\n", &uglobal2, "seconda variabile globale non inizializzata");
    printf("0x%lx \t: %s\n", &global1, "prima variabile globale inizializzata");
    printf("0x%lx \t: %s\n", &global2, "seconda variabile globale inizializzata");

    printf("\n%s\n", "AREA CODICE");
    printf("0x%lx \t: %s\n", main, "puntatore a main");
    printf("0x%lx \t: %s\n", func, "puntatore a func");
}   

void func(int i)
{
    if (i < 0)
        return;
    short int x = 2;

    // printf("0x%lx \t: %s\n", &i, "indirizzo del parametro di func");
    printf("0x%lx \t: %s %d %s\n", &x, "variabile dello stack della chiamata", i, "di func");
    func(i - 1);
}


// ogni tanto fa esplodere windows, meglio non chiamarla
void* fine_heap(){

    void* ptr1;
    void* ptr2;

    while(1)
    {
        ptr1 = malloc(1024*1024);
        if(ptr1 == NULL)
            return ptr2;
        ptr2 = ptr1;
        // free(ptr1);
    }

}