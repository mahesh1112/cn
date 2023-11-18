#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
int main() {
	// create a socket
	int network_socket;
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	// check for error while connection
	if(connection_status == -1)
	{
		printf("Theres was an error in making connection!\n\n");
	}

	// recieve data from the server
	char buffer[256] = {0};
	recv(network_socket,&buffer,sizeof(buffer),0);

	printf("The server send the response: %s\n",buffer);
	
	char message[256];
	printf("Send message to server: ");
	scanf("%s", message);
	send(network_socket,message,strlen(message),0);
	
	close(network_socket);
	return 0;
}
