#include <stdio.h>
#include <stdint.h>

/*
 * htonl and htons reverse the byte order on a little endian machine and are no ops on big endian machines
 */

char is_big_endian(){
        uint16_t x = 1;
        char* ptr = (char *) &x;
        return (*ptr)==0;
}


uint32_t my_htonl(uint32_t host_long){

        if(is_big_endian())
                return host_long;

        uint32_t net_long = (host_long>>16) + (host_long<<16);

        return net_long;

}

uint16_t my_htons(uint16_t host_short){

        if(is_big_endian())
                return host_short;

        uint16_t net_short = ((host_short&0xff00)>>8) + ((host_short&0x00ff)<<8);
        return net_short;
}


int main(){

        printf("Is big endian: %d\n", is_big_endian());

        uint32_t l = 0x1234ABCD;
        uint32_t net_long = htonl(l);
        uint32_t my_net_long = my_htonl(l);
        printf("uint32_tvalue \t%lx\n", l);
        printf("htonl \t\t%lx\n", net_long);
        printf("my_htonl \t%lx\n\n", my_net_long);

        uint16_t s = 0xABCD;
        uint16_t net_short = htons(s);
        uint16_t my_net_short = my_htons(s);
        printf("uint16_t value \t%x\n", s);
        printf("htons \t\t%x\n", net_short);
        printf("my_htons \t%x\n", my_net_short);



}