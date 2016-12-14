#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>
#include <arpa/inet.h>
#include <termios.h>
#include <time.h>
#include "lib/protocol.h"
#include "lib/login_signup.h"
#include "lib/play.h"
//-----------------------------
#define FAIL -1

//-----------------------------

//-----------------------------
int createConnection(int PORT,char IP[10])
{
		
	struct sockaddr_in serverAddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		printf("khong the tao duoc socket\n");
		return FAIL;
	}
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(IP);
	if(connect(sockfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
	printf("ket noi den server that bai\n");
	return FAIL;
	}
	printf("server duoc ket noi thanh cong ...\n");
	return 1;
}
void printMenu()
{
	printf("*************----------------**************\n");
	printf("*****           1.LOGIN               *****\n");
	printf("*****           2.SIGNUP              *****\n");
	printf("*****           3.QUIT                *****\n");
	printf("*************----------------**************\n");
	printf("	Please enter your choice : \n");
	printf("      **: ");
}
int main()
{
	
	int n,t,i;
	char c;
	protocol p;
	i=createConnection(5500,"127.0.0.1");
	if (i==FAIL)return 1;
	while(1){
		// bien t de check trang thai cua signup
		t=-1;
		printMenu();
		scanf("%d",&n);
		while(getchar()!='\n');
		if(n==3) break;
		switch(n){
			case 1: 
				loop:

				t=signIn(&p);
				printf("lala %d\n",t);
				if (t==-1) continue;
				send(sockfd,&p,sizeof(protocol),0);
				recv(sockfd,&p,sizeof(protocol),0);
				switch(p.p_state){
					case UNAUTHENTICATE: 
						printf("Ten dang nhap hoac password sai!\n");
						do{
							printf("Tiep tuc sign in?(y/n)\n");
							scanf("%c",&c);
						}while(c!='y'&&c!='Y'&&c!='n'&&c!='N');
						if (c=='y'||c=='Y') goto loop;
						continue;
						break;
					case AUTHENTICATE:
						printf("Dang nhap thanh cong!!\n");
						i=play(&p,sockfd);
						if (i==0) continue;
						break;
				}
				break;
			case 2: 
				t=signUp(&p);
				if(t==0||t==-1) continue;
				send(sockfd,&p,sizeof(protocol),0);
				recv(sockfd,&p,sizeof(protocol),0);
				switch(p.p_state){
					case SIGNUP: printf("%s\n","Ten dang nhap da ton tai!" );break;
					case CONNECTED: printf("%s\n","Dang ki thanh cong!" );break;
				}
				break;
		}
		
	}
}
