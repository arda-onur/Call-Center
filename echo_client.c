/*
	ARDA ONUR S018752
*/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];

int main(int argc , char *argv[])
{
	
	size_t strlen(const char *);
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
	 
	
	//-----------------------------------------------------------------------------------------------------
	//keep communicating with server
	while(1)
	{	
		recv(sock , server_reply , 2000 , 0);
        

          if( strcmp(server_reply,"full") == 0){
		puts("You cannot enter the call, Please try again");
		break;
	 }else if(strcmp(server_reply,"wait") == 0){
		puts("You are in waiting room");
		memset(server_reply, 0, sizeof server_reply);
		recv(sock , server_reply , 2000 , 0);

	   while(strcmp(server_reply,"go") != 0){

	   }
		
	 }
         memset(server_reply, 0, sizeof server_reply);
		while (1) {
		 memset(server_reply, 0, sizeof server_reply);
        printf("Enter message : ");
		scanf("%s" , message);

		
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
		
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		
		if(strcmp(server_reply,"exceeded") == 0){
			puts("Disconnected due to exceeding time");
			break;
		}
		
		printf("Server reply: %s\n", server_reply);
		memset(message, 0, sizeof message);
		memset(server_reply, 0, sizeof server_reply);
	
		}
		
		break;
	}
	
	close(sock);
	return 0;
}

