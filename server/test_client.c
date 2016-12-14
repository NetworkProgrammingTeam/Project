#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "lib/protocol.h"

void set_authenticate_state(protocol *p){
  if(p == NULL){
    p = (protocol *)malloc(sizeof(protocol));
  }
  p->p_state = AUTHENTICATE;
  strcpy(p->p_user_info.user_id,"va_dl");
  strcpy(p->p_user_info.password,"123456");
  strcpy(p->p_message,WANT_TO_PLAY);
}

void receive_title(int client_sock,protocol *p){  // call this function after request_play or answer a question
  recv(client_sock,p,sizeof(protocol),0);
  printf("T1: %s\nT2: %s\n",p->p_title.title1,p->p_title.title2);
}

void pick_title(int client_sock,protocol *p){ // call this dunction after receive 2 titles
  printf("You pick (1 or 2): ");
  int pick;
  scanf("%d",&pick);
  p->p_title.pick = pick-1;
  memset(p->p_message,'\0',sizeof(p->p_message));
  strcpy(p->p_message,SEND_TITLE);
  send(client_sock,p,sizeof(protocol),0);
}

void print_question(int client_sock,protocol *p){
  recv(client_sock,p,sizeof(protocol),0);
  question q = p->p_question;
  printf("Q: %s\nA1: %s\nA2: %s\nA3: %s\nA4: %s\n", q.question,q.answer1,q.answer2,q.answer3,q.answer4);
}

void request_play(int client_sock,protocol *p){
  set_authenticate_state(p);
  send(client_sock,p,sizeof(protocol),0);
  receive_title(client_sock,p);
  pick_title(client_sock,p);
  print_question(client_sock,p);
}

int client_sock;	/*client descriptor*/
struct sockaddr_in server_addr;	/*server address struct*/
int main(){

	protocol p;

	int bytes_sent,bytes_recv;	/*number of bytes send, receive with server*/

	client_sock=socket(AF_INET,SOCK_STREAM,0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5500);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr.sin_zero, '\0',sizeof(server_addr.sin_zero));

	/*connecting to server*/
  if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
		printf("\nError!Can not connect to sever!Client exit imediately! ");
		return -1;
	}

	//TODO
  request_play(client_sock,&p);
	close(client_sock);
	return 0;
}
