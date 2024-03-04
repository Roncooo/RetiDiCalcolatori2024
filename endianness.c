
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
    uint16_t i = 260;
    uint16_t* p = &i;
    uint8_t* c = (uint8_t*)&i;

    printf("%s\n","uint16_t i = 260;");
    printf("i:\t%lx\n",i);
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
