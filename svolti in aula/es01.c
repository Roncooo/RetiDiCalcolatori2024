#include <stdio.h>
#include <stdlib.h>

int globalvar = 0; // variabile globale (statica)

int es1()
{

    // analizzo lo stack
    int s1;
    int s2;
    printf("variabili locali della funzione\n");
    printf("%p\n", &s1); // %p formato per stampare gli indirizzi
    printf("%p\n", &s2);
    // le variabili locali si trovano nello stack, vedo se gli indirizzi delle due variabili
    // locali crescono (stack cresce verso il basso) o diminuiscono (stack cresce verso l'alto)

    // analizzo lo heap
    int *p1 = (int *)malloc(sizeof(int));
    int *p2 = (int *)malloc(sizeof(int));
    printf("memoria allocata dinamicamente\n");
    printf("%p\n", p1);
    printf("%p\n", p2);
    // la memoria allocata dinamicamente si trova nello heap, vedo se gli indirizzi dei due spazi
    // di memoria allocata crescono (heap cresce verso il basso) o diminuiscono (heap cresce verso l'alto)

    // nota: nello stack vanno a finire le variabili locali ma anche il record (stack) di attivazione della
    // funzione (tutto ciò che serve alla funzione per poter ritornare)

    // lo stack cresce DALL'ALTO VERSO IL BASSO, l'heap cresce DAL BASSO VERSO L'ALTO

    return 0;
}

int main()
{
    int p3;
    printf("variabile stack nel main\n");
    printf("%p\n", &p3);
    es1();
    printf("variabile globale statica");
    printf("%p\n", &globalvar);
    return 0;
}