#include <stdio.h>
#include <sys/socket.h>		// questa non esiste su windows, va compilato solo in ambiente linux
#include <errno.h> 
#include <netinet/in.h>		// al prof non serve questa ma per qualche motivo a me si anche da wls

int main(){
	int s;
	int t;
	int i;
	char response[100000];
	struct sockaddr_in server;
	s=socket(AF_INET, SOCK_STREAM, 0);
	if(s==-1){
		printf("errno:= %d\n", errno); // 97
		perror("socket failed"); // addr fam not supported by protocol
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	unsigned char * p;
	p = (unsigned char*) &server.sin_addr.s_addr; //indirizzo IP
	p[0] = 142;
	p[1] = 250;
	p[2] = 200;
	p[3] = 142;

	t = connect(s, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
	write(s, "GET /\r\n",7);

	for(i=0; t=read(s, response+i, 99999-i); i+=t)
		printf("t=%d\n",t);

	response[i] = 0;	// terminatore
	printf("s = %d\n\n", s);	
	printf("%s\n\n",response);
}

