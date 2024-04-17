#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> // per htons

struct sockaddr_in srvaddr;
struct sockaddr_in remote;

int main()
{
	int s, t, s2;

	char *request[3000];
	char *response[3000];

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1)
	{
		perror("Socket fallita");
		return 1;
	}

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(8000); // usiamo questo perché è già usato 80 dal server vero, l'importante è che noi sappiamo quale sia, deve essere noto per noi
	srvaddr.sin_addr.s_addr = 0;		// posso anche non scriverlo

	t = bind(s, (struct sockaddr *)&srvaddr, sizeof(struct sockaddr_in));
	if (t == -1)
	{
		perror("Bind fallita");
		return 1;
	}

	t = listen(s, 5);
	if (t == -1)
	{
		perror("Listen fallita");
		return 1;
	}

	while(1){

			int len = sizeof(struct sockaddr);
			s2 = accept(s, (struct sockadd *)&remote, &len); // passiamo tutto per riferimento perché accept deve modificarla
			if (s2 == -1)
			{
				perror("Accept fallita");
				return 1;
			}

			// ora possiamo leggere la richiesta
			t = read(s2, request, 3000);
			if (t == -1)
			{
				perror("Read fallita");
				return 1;
			}
			request[t] = 0;
			printf("Richiesta %s\n", request);

			// ora possiamo rispondere (full response)
			sprintf(response, "HTTP/1.1 200 OK\r\nConnect:close\n\n<html><h1>Funziono!</h1>");
			write(s2, response, strlen(response));
			close(s2);

	}
}
