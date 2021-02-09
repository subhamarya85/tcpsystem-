#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>


#include<sys/time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/select.h>

#define PORT 9999
#define SA struct sockaddr
int max_client[5];
fd_set readfd,writefd;

/*int message(int clientfd,int client_no)
{

	int x,n;
	char buff[256];

	if((x=recv(clientfd,buff,sizeof(buff),0))<0)
	{
		close(clientfd);
		printf(" Error in reciveing message from client : %d",client_no);
		for(int i=0;i<clientfd;++i)
		{
			if(max_client[i]==clientfd)
			{
				max_client[i]=0;
				break;
			}
		}
	}
	else
	{
		recv(clientfd,buff,sizeof(buff),0);
		printf("From client %d : %s\t To client : ",client_no,buff);
		//bzero(buff,sizeof(buff));

		write(clientfd,buff,sizeof(buff));
	}

	return 0;

}



void func(int sockfd)
{
	struct sockaddr_in cli;
	int clientfd,len,i,n=0;
	len=sizeof(cli);

	if(FD_ISSET(sockfd,&readfd))
	{
		clientfd=accept(sockfd,(SA*)&cli,&len);

		if(clientfd>0)
		{
			printf(" client connected from port %d\n",ntohs(cli.sin_port));
			send(clientfd,"you are now connected to server\n",32,0);
			for(i=0;i<5;++i)
			{
				if(max_client[i]==0)
				{
					max_client[i]=clientfd;
					send(clientfd,"connected succesfully\n",21,0);
					break;

				}

			}
			if(i==5)
				printf("server busy\n");



		}
		else
		{
			printf("connection failed\n");
			exit(0);
		}
	}

	

		for(i=0;i<5;++i)
		{
			if(FD_ISSET(max_client[i],&readfd))
			{
				message(max_client[i],i);
			}
		}
	

			


}*/


int main()
{

	char buff[256];


	int sockfd,nRet,Maxfd,sd,clientfd,len;
	struct sockaddr_in servaddr,cli;
        
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd<0)
	{
		printf("Socket creation failed");
		exit(0);
	}
	else
	{

		printf("[+] Socket created successfully\n");
	}


	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);


	nRet=bind(sockfd,(SA*)&servaddr,sizeof(servaddr));

	if(nRet<0)
	{
		printf("Bind to local port failed");
		exit(0);
	}
	else
	{
		printf("[+] Binded to local port succesfully\n");

	}

	nRet=listen(sockfd,5);


	if(nRet<0)
	{

		printf("Server listining failed");
		exit(0);
	}
	else
	{
		printf("[+] Server listening\n");
	}


	
	struct timeval tv;

	tv.tv_sec=10;
	tv.tv_usec=0;


	len=sizeof(cli);





	while(1)
	{
               
		FD_ZERO(&readfd);


		FD_SET(sockfd,&readfd);
                Maxfd=sockfd;
		for(int n=0;n<5;++n)
		{
			sd=max_client[n];

			if(sd>0)
				FD_SET(sockfd,&readfd);
			if(Maxfd<sd)
				Maxfd=sd;

		}


		nRet=select(Maxfd+1,&readfd,&writefd,NULL,&tv);

                if(nRet<0)
		{
			printf("select error\n");
		}


		if(FD_ISSET(sockfd,&readfd))
		{
			clientfd=accept(sockfd,(SA*)&cli,&len);

			if(clientfd<0)
			{
				printf("connection failed\n");
				exit(0);
			}

			printf("Connection accepted\n");

			printf("Client connected from port : %d\n",ntohs(cli.sin_port));
		

			for(int i=0;i<5;++i)
			{
				if(max_client[i]==0)
				{
					max_client[i]=clientfd;
                                	send(max_client[i],"hii",3,0);
					break;

				}
			}

			puts("message sent successfully\n");
			

		}
		bzero(buff,sizeof(buff));
		for(int i=0;i<5;++i)
		{
			printf("%d\n",max_client[i]);
			sleep(5);
			sd=max_client[i];
			if(FD_ISSET(sd,&readfd))
			{
				puts("hi\n");
				printf("hi");
				if((read(sd,buff,sizeof(buff)))==0)
				{
					close(sd);

					printf("Client id %d dissconnected\n",sd);
					max_client[i]=0;
				}
				
			}

		}



		
	      	
	}


}
