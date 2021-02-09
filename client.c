#include<stdio.h>
#include<stdlib.h>
#include<string.h>



#include<sys/socket.h>
#include<sys/types.h>



#include<netdb.h>
#include<netinet/in.h>


#define PORT 9999
#define MAX 256
#define SA struct sockaddr



void func(int sockfd)
{

	int n;
	char buff[MAX];

	for(;;)
	{
		bzero(buff,MAX);

		

	
		read(sockfd,buff,sizeof(buff));

		printf("\n From Server :  %s",buff);
		
                printf("Enter the string : ");

		n=0;
		while((buff[n++]=getchar())!='\n')
			;
        	bzero(buff,sizeof(buff));
		write(sockfd,buff,sizeof(buff));
		/*if((strncmp("exit",buff,4))==0)
		{
			printf(" server exit \n");
			break;
		}*/

	}

}





int main()
{

	system("clear");

	int sockfd;

	struct sockaddr_in servaddr,cli;

	sockfd=socket(AF_INET,SOCK_STREAM,0);


	if(sockfd<0)
	{
		printf("Socket creation failed....\n");
		exit(0);
	}
	else
	{
		printf("[+] Socket created successfully\n");

	}


	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");


	if((connect(sockfd,(SA*)&servaddr,sizeof(servaddr)))<0)
	{
		printf("Connection with server failed....\n");
		exit(0);
	}
	else
	{
		printf("[+] connected to server\n");

	}

	func(sockfd);


	close(sockfd);




	return 0;
}
