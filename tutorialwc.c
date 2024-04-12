/*
 * Come fare un Web client?
 * 1) Creare un socket (man 2 socket)
 *	int socket(int domain, int type, int protocol);
 *	domain = AF_INET
 *	type = SOCK_STREAM
 *	protocol = 0 = IPPROTO_TCP
 * 2) Connettere il socket al server (man 2 connect)
 * 	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 *	sockfd è il numero ritornato da socket
 *	addr è un puntatore a un generico sockaddr che noi specifichiamo come dice man 7 ip
 * 		struct sockaddr_in {
               		sa_family_t    sin_family; // address family: AF_INET 
               		in_port_t      sin_port;   // port in network byte order: htons(80) 
               		struct in_addr sin_addr;   // internet address
           	};
           	struct in_addr {
               		uint32_t       s_addr;     // address in network byte order 
           	};
	per trovare l'ip usiamo nslookup www.google.com
 * 3) Usare write per fare una richiesta 
 * 	write(s, request, strlen(request));
 * 	request:
 * 		http/0.9: "GET /\r\n"
 * 		http/1.0:
 * 		http/1.1:	
 *
 * 4) Usare read per leggere una risposta
 *	Occorre fare un ciclo
 *	for(i=0; current_length=read(s, response+i, max_length-i); i+=current_length){}
 *
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>

int main(){
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// printf("%d",s);
	struct sockaddr_in addr_in;
	struct sockaddr * addr = (struct sockaddr *) & addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(80);
	unsigned char * ip =(unsigned char *) &addr_in.sin_addr.s_addr;
	
	// 142.251.209.36
	ip[0] = 142;
	ip[1] = 251;
	ip[2] = 209;
	ip[3] = 36;
	int c = connect(s, addr, sizeof(addr_in));
	
	char * request = "GET /\r\n";
	write(s, request, strlen(request));

	int max_length = 60000;
	char response[max_length];
	int current_length;
	int i;
	for(i=0; current_length=read(s, response+i, max_length-i); i+=current_length){
		printf("Current_lenght: %d\n", current_length);
	}
	printf("Total_length: %d\n", i);

	response[max_length-1] = 0;
	printf("%s\n", response);
}

