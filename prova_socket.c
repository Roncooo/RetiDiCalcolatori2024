#include <stdio.h>
#include <sys/socket.h>		// questa non esiste su windows, va compilato solo in ambiente linux
#include <errno.h> 
#include <netinet/in.h>		// al prof non serve questa ma per qualche motivo a me si anche da wls

int main(){
	int s;
	int t;
	char response[1000];
	struct sockaddr_in server;
	s=socket(AF_INET, SOCK_STREAM, 0);
	if(s==-1){
		printf("errno:= %d\n", errno); // 97
		perror("socket failed"); // addr fam not supported by protocol
	}

	server.sin_family = AF_INET;
	server.sin_port = 80;
	unsigned char * p;
	p = (unsigned char*) &server.sin_addr.s_addr; //indirizzo IP
	p[0] = 142;	// 142.251.209.14
	p[1] = 251;
	p[2] = 209;
	p[3] = 14;
	t = connect(s, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
	write(s, "GET /\r\n",7);
	int numero_byte = read(s, response, 999);	// al massimo 999
	response[numero_byte] = 0;	// terminatore
	printf("s = %d\n", s);	
	printf(response);
}

