#include <string.h>
#include "protocol.h"
#include <stdio.h>
int sockfd;


void get_pass(char pass[]){
	int i=0;

	while(1){
		pass[i]=getchar();
		if(pass[i]== '\n') break;
		//printf("*");
		i++;
	};
	pass[i]='\0';
}

// static struct termios old, new;
// void initTermios(int echo) {
// 	tcgetattr(0, &old);
// 	new = old;
// 	new.c_lflag &= ~ICANON;
// 	new.c_lflag &= echo ? ECHO : ~ECHO;
// 	tcsetattr(0, TCSANOW, &new);
// }

// void resetTermios(void) {
//   tcsetattr(0, TCSANOW, &old);
// }

// char getch_(int echo) {
// 	char ch;
// 	initTermios(echo);
// 	ch = getchar();
// 	resetTermios();
// 	return ch;
// }

// char getch(void) {
//     return getch_(0);
// }
//request signup
int requestSignup(protocol *p){
	p->p_state=CONNECTED;
	strcpy(p->p_message,WANT_TO_SIGNUP);
	send(sockfd,p,sizeof(protocol),0);
	recv(sockfd,p,sizeof(protocol),0);
	if (p->p_state==SIGNUP)return 1;
	else return 0;
}
//tao giao dien dang nhap va luu vao giao thuc chuyen di
int signUp(protocol *p)
{
	int i;	//test request signup
	char t;
	char temp[32];//test comfirmation of password
	i=requestSignup(p);
	if (i==0) return -1;
	memset(p->p_message,'\0',sizeof(p->p_message));
	do{
		printf("Account: ");
		gets(p->p_user_info.user_id);
		printf("Password: ");
		get_pass(p->p_user_info.password);
		printf("\nComfirmation:\n");
		get_pass(temp);
		if(!strcmp(p->p_user_info.password,temp)){
			return 1;
		}
		else {
			printf("%s\n","Signup error!");
			printf("Do you want enter again(y/n)\n");
			t=getchar();
			while(getchar()!='\n');
		}
	}while(t=='y');
	return 0;
}

//reqest sigin
int requestSignin(protocol *p){
	p->p_state = CONNECTED;
	strcpy(p->p_message,WANT_TO_SIGNIN);
	send(sockfd,p,sizeof(protocol),0);
	recv(sockfd,p,sizeof(protocol),0);
	if (p->p_state==UNAUTHENTICATE)return 1;
	else return 0;

}
int signIn(protocol *p){
	int i;//bien kiem tra request signin
	i=requestSignin(p);
	if(i==0)return -1;
	memset(p->p_message,'\0',sizeof(p->p_message));
	printf("Account: ");
	gets(p->p_user_info.user_id);
	printf("Password: ");
	get_pass(p->p_user_info.password);
	return 1;

}
