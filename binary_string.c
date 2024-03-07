
#include <stdint.h>

/*
TIPO        DIMENSIONE (byte)           std int.h
char		1				            int8_t
short int	2				            int16_t
int		    4			    	        int32_t
long		4 se architettura 32 bit	int32_t
            8 se architettura 64 bit	int64_t
long long	8				            int64_t
*/

// using uint16_t i'm allowing up to 65535 bytes
uint8_t* everythingToBinaryString(void* ptr, uint16_t nbytes){
    uint8_t* p = (uint8_t*)ptr;
    uint32_t nbit = 8*nbytes;
    uint8_t* str = malloc(nbit);
    str[nbit-1] = 0;    // terminatore
    uint8_t mask;
    for(int16_t i=0; i<nbytes; i++){
        mask = 0x01;
        for(uint32_t j=0; j<8; j++){
            if(p[i*8+j]&mask > 0)
                str[i*8+j] = 1;
            else
                str[i*8+j] = 0;
            
            mask = mask << 1;
        }
    }

    return str;

}

void main(){
    uint16_t i = 0xFFFF;
    printf("%d\n", i);
    printf("%d\n", sizeof(i));

    char * str = everythingToBinaryString(&i, sizeof(i));
    printf("%s", *str);
}