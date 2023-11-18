#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
	int fd;
	char fileName[2000],file_buffer[2000];
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	bzero(&servaddr,sizeof(servaddr));
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	
	printf("Enter text file name to send : \n");
    scanf("%s",fileName);
    sendto(fd, fileName, strlen(fileName), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));

    FILE *fp;
    fp=fopen(fileName,"r");

    if(fp)
    {
    	 printf("Reading file contents.\n");
     	fseek(fp,0,SEEK_END);
       	size_t file_size=ftell(fp);
       	fseek(fp,0,SEEK_SET);
        if(fread(file_buffer,file_size,1,fp)<=0)
        {
           	printf("Unable to copy file into buffer or empty file.\n");
           	exit(1);
        }
    }
    else
    {
    	printf("Cannot open file.\n");
    	exit(0);
    }
    printf("FILE CONTENTS TO SEND : %s\n",file_buffer);
    if(sendto(fd, file_buffer,strlen(file_buffer), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr))<0)
    {
    	printf("FILE WAS NOT SENT\n");
    }
    else
    {
    printf("FILE SENT\n");
    }
    fclose(fp);
	
}
