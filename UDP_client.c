#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#define MAX 1024
#define PORT 8080
int main() {
	
	int network_socket;
	char buffer[MAX];
	const char *hello = "Hello from client!";
	
	// creation of client socket
	network_socket = socket(AF_INET,SOCK_DGRAM,0);
	if(network_socket < 0)
	{
		perror("Socket creation failed!");
		exit(EXIT_FAILURE);
	}
	
	// define server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	int n;
	socklen_t len;
	
	// sendto function in UDP sends the hello message to server
	sendto(network_socket,(const char *)hello,strlen(hello),MSG_CONFIRM,(const struct sockaddr *)&server_address, sizeof(server_address));
	
	printf("Message sent to server!");
	
	len = sizeof(server_address);
	
	// recvfrom recieves the message from server
	n = recvfrom(network_socket,buffer,MAX,MSG_WAITALL,(struct sockaddr *)&server_address, &len);
	
	buffer[n] = '\0';
	printf("\nServer: %s\n",buffer);
	
	close(network_socket);
	return 0;
	}
