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
#include "functions.h"

void main(){

    short int i = 0x1234;
    char* str = binaryString(&i, sizeof(i));
    printf("%s",str);
    free(str);

}