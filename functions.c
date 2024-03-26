#include <stdint.h>
/*
TYPE        DIMENSION (byte)            stdint.h
char		1				            int8_t
short int	2				            int16_t
int		    4			    	        int32_t
long		4 in 32 bit architecture	int32_t
            8 in 64 bit architecture	int64_t
long long	8				            int64_t
*/


/**
 * This function lets you convert a variable to 
 * a string with its binary representation.
 * To indicate the variable you need to provide
 *  - the pointer to its location
 *  - the size in bytes
 * The function returns a pointer to a c-style string
 * that can be printed with printf("%s", str);
 * 
 * Usage:
 *      uint16_t i = 0xF0F0;
 *      char* str = binaryString(&i, sizeof(i));
 *      printf("%s", str);
 *      free(str);
 * 
*/
uint8_t* binaryString(void* ptr, uint16_t nbytes){
    uint8_t* p = (uint8_t*)ptr;
    uint32_t nbit = 8*nbytes;
    uint8_t* str = malloc(nbit+1);
    uint8_t mask;
    for(int16_t i=0; i<nbytes; i++){
        mask = 0x01;
        for(uint32_t j=0; j<8; j++){
            if( (p[i]&mask) == 0)
                str[i*8+j] = '0';
            else
                str[i*8+j] = '1';
            
            mask = mask << 1;
        }
    }
    str[nbit] = 0;    // terminator
    return str;
}


void main(){
    uint16_t i = 0x0001;
    char* str = binaryString(&i, sizeof(i));
    printf("%s", str);
    free(str);
}
