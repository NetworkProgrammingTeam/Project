#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include "protocol.h"
#define TIME_OUT 15000

void printMenuPlay()
{
	printf("*************----------------**************\n");
	printf("*****           1.PLAY                *****\n");
	printf("*****           2.QUIT                *****\n");
	printf("*************----------------**************\n");
	printf("	Please enter your choice : \n");
	printf("      **: ");
}
char get_answer(int time_out)
{
    struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
    char answer;

    if( poll(&mypoll, 1, time_out) )
    {
        scanf("%c", &answer);
        while(getchar()!='\n');
        return answer;
    }
    else return 'F';
}

void delay()
{
	printf(" The game will start in: \n");
	get_answer(2000);
	printf("3...\n");
	get_answer(2000);
	printf("2...\n");
	get_answer(2000);
	printf("1....\n");
	get_answer(1000);
}
int choseTitle(protocol *p){
	int i;
	do{
		i=-1;
		printf("------Moi chon giua hai chu de sau------\n");
		printf("Chu de 1: %s\n", (p->p_title).title1);
		printf("Chu de 2: %s\n", (p->p_title).title2);
		printf("------Ban chon?\n");
		scanf("%d",&i);while(getchar()!='\n');
		i--;
	}while(i!=0&&i!=1);
	return i;
}


int play(protocol *p,int sockfd){
	//srand(time(NULL));
	int n,i;
	char c;
	loop:
	printMenuPlay();
	scanf("%d",&n);while(getchar()!='\n');
	if(n==2) return 0;
	else if (n==1){
		strcpy(p->p_message,WANT_TO_PLAY);
		send(sockfd,p,sizeof(protocol),0);
		recv(sockfd,p,sizeof(protocol),0);
		if(p->p_state != PLAYING) return -1;//server error
		do{
			printf("ARE YOU READY?(y/n)\n");
			scanf("%c",&c);
		}while(c!='y'&&c!='Y'&&c!='n'&&c!='N');
		if (c=='y'||c=='Y'){
			delay();
			(p->p_title).pick = choseTitle(p);
			send(sockfd,p,sizeof(protocol),0);
			recv(sockfd,p,sizeof(protocol),0);
			return 1;
		}
		else goto loop;
	}
	else goto loop;
}
