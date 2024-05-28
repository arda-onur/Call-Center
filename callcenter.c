//ARDA ONUR S018752
#include<stdio.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<pthread.h> 


void *connection_handler(void *);
pthread_mutex_t client_mutex;
#define maxclient 4;
int clientnumber = 0;


int main(int argc , char *argv[])
{ 
        

	int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;

    
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	pthread_mutex_init(&client_mutex, NULL);
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	//--------------------------------------------------------------------------------------------------
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
            clientnumber++;
            
            
        if(clientnumber > 3){
            char *message = "full";
            write(client_sock , message, strlen(message));
            printf("Disconnected. \n");
            shutdown(client_sock,2);
            close(client_sock);
            --clientnumber;
        }
         
		
          
            
            
            puts("Connection accepted");
            

		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = client_sock;
	    //PTHREAD FOR THE CONNECTIONS
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}
		
		
		
        
		
	}
	
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	close(socket_desc);
	return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	int sock = *(int*)socket_desc;
	int read_size;
	char *message , client_message[2000];

	int i = 0;
		while (clientnumber == 3)
		{
			
			if(i == 0){
			puts("One client is in waiting room");
            char* messagem = "wait";
            write(sock, messagem, strlen(messagem)); 
			i++;
			}
			 
		}
		    char* messagemm = "go";
            write(sock, messagemm, strlen(messagemm)); 
	    
	
	
	
    
    time_t limit= 10;
    time_t beginning = time(NULL);
    time_t current;
   
	//Receive a message from client
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{
		    current = time(NULL);
        if (current - beginning > limit) {
            message = "exceeded";
            write(sock, message, strlen(message));
            puts("Client disconnected due to time limit exceeded.");
    
            shutdown(sock, 2);
            close(sock);
            --clientnumber;
            return 0;
        }
        write(sock, client_message, strlen(client_message));
        memset(client_message, 0, sizeof client_message);


    
            
   


    }
	if(read_size == 0)
	{
	
		puts("Client disconnected");
               --clientnumber;
        		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
		
	//Free the socket pointer
	free(socket_desc);
	
	return 0;
}
