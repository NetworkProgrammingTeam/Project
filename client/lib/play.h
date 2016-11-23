#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "protocol.h"
#include "login_signup.h"

void printMenuPlay()
{
	printf("*************----------------**************\n");
	printf("*****           1.PLAY                *****\n");
	printf("*****           2.QUIT                *****\n");
	printf("*************----------------**************\n");
	printf("	Please enter your choice : \n");
	printf("      **: ");
}
void delay(int x){
	int i=0;
	x=x*1000000;
	for(i;i<x;i++){

	}
}

int play(protocol *p){
	int n;
	char c;
	loop:
	printMenuPlay();
	scanf("%d",&n);while(getchar()!='\n');
	if(n==2) return 0;
	else if (n==1){
		strcpy(p->p_message,WANT_TO_PLAY);
		send(sockfd,p,sizeof(protocol),0);
		recv(sockfd,p,sizeof(protocol),0);
		do{
			printf("ARE YOU READY?(y/n)\n");
			scanf("%c",&c);
		}while(c!='y'||c!='Y'||c!='n'||c!='N');
		if (c=='y'||c=='Y'){
			strcpy(p->p_message,I_AM_READY);
			send(sockfd,p,sizeof(protocol),0);
			recv(sockfd,p,sizeof(protocol),0);
			printf("3...");delay(3);
			printf("2..");delay(2);
			printf("1..\n");delay(1);
			printf("START!!!!\n");
			return 1;
		}
		else goto loop;
	}
	else goto loop;
}
