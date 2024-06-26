/*
 * Come fare un Web client con il protocollo 1.1?
 *
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
 * 	request http/1.1 =  "GET / HTTP/1.1\r\n\r\n"
 *
 * La differenza principale rispetto ai protocolli 0.9 e 1.0 è che 
 * con l'1.1 la connessione non termina quando termina il file.
 * Per ottenere un comportamento come in http0.9 e 1.0 potrei fare questa request
 * 	GET / HTTP/1.1\r\nConnection: close\r\n\r\n
 * 	Ma non avrebbe più senso l'1.1
 *
 * Quindi cambia la tecnica per la lettura. Se faccio come ho fatto per
 * http0.9 e 1.0 funziona tutto ma si blocca dopo aver finito la lettura
 * perché non è terminata la connessione. Aspettando un un bel po', la connessione
 * viene terminata automaticamente e quindi si può vedere la response.
 * Notiamo che la response contiene
 *  - HTTP/1.1 200 OK
 *  - un po' di header che per il momento non ci interessano
 *  - Transfer-Encoding: chunked
 *  - una linea vuota (un'altro CRLF)
 *  - dimensione del chunk inviato: 4ea8
 *  - chunk di entity body
 *  - nuova dimensione
 *  - nuovo chunk e via così finché la nuova dimensione è 0 
 *
 * 
 * 4) Usare read per leggere una risposta
 *	Occorre fare un ciclo
 *	for(i=0; current_length=read(s, response+i, max_length-i); i+=current_length){}
 */

#include <stdio.h>	// printf
#include <sys/types.h>	// socket, connect
#include <sys/socket.h>	// socket, connect
#include <netinet/ip.h> // sockaddr_in
#include <unistd.h> 	// write, read
#include <string.h>	// strlen


struct header{
	char* n;	// name
	char* v;	// value 
} h[100];		// creating an array

#define max_response_length 60000
char response[max_response_length];

#define max_header_length 10000
char header_buffer[max_header_length];

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
	
	char * request1_1 = "GET / HTTP/1.1\r\n\r\n";
	write(s, request1_1, strlen(request1_1));

	int current_length;

	// PARSING DEGLI HEADER fatto durante la lettura per risparmiare tempo
	// leggiamo un char alla volta
	int i;	// scorre i caratteri
	int j;	// conta gli header
	char * statusline=h[0].n=response;	// status line
	for(i=0, j=0; read(s, response+i, 1); i++){
		// se trovo CRLF vuol dire che subito dopo inizia un nuovo header
		if(response[i-1]=="\r" && response[i]=="\n"){
			j++;
			h[j].n = &response[i+1];	// segno l'inizio di un nuovo header
			response[i-1]=0;			// terminatore del precedente h.v
			// se il precedente header è vuoto, ho finito
			if(h[j-1].n[0]==0){
				break;
			}

		}	
		
		// se sono arrivato a : e
		// non ho ancora segnato l'inizio del valore (che di default è 0)
		if((response[i]==":") && (!h[j].n)){	
			h[j].v = response+i;
			response[i]=0;	// terminatore del nome dell'header
		}

	}
	
	
	// close(s);

	// leggere l'entity body usando l'informazione sulla lunghezza

	response[max_response_length-1] = 0;
	printf("%s\n", response);
}

