#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "login_helper.h"
#include "../lib/protocol.h"

void allow_signup(protocol *p){
  p->p_state = SIGNUP;
  memset(p->p_message,'\0',sizeof(p->p_message));
  strcat(p->p_message,"you are allowed to sign up");
}

void do_signup(protocol *p){
  user u = p->p_user_info;
  char f_name[256] = "users/";
  strcat(f_name,u.user_id);
  if(access(f_name, F_OK) != -1){ // User is exist
    p->p_state = SIGNUP;
    memset(p->p_message,'\0',sizeof(p->p_message));
    strcat(p->p_message,"sign up fail");
  } else{
    FILE *f;
    f = fopen(f_name,"w");
    if(f){
      fprintf(f, "%s", u.password);
    } else{
      printf("Loi mo file \n");
      //TODO sign up fail
    }
    fclose(f);
    p->p_state = CONNECTED;
    memset(p->p_message,'\0',sizeof(p->p_message));
    strcat(p->p_message,"done sign up");
  }
}

void allow_signin(protocol *p){
  p->p_state = UNAUTHENTICATE;
  memset(p->p_message,'\0',sizeof(p->p_message));
  strcat(p->p_message,"you are allowed to sign in");
}

void do_signin(protocol *p){
  user u = p->p_user_info;
  char f_name[256] = "users/";
  strcat(f_name,u.user_id);
  FILE *f = fopen(f_name,"r");
  if(f != NULL){
    char pass[32];
    fscanf(f,"%s",pass);
    if(!strcmp(pass,u.password)){
      p->p_state = AUTHENTICATE;
    } else{
      p->p_state = UNAUTHENTICATE;
    }
  } else{
      p->p_state = UNAUTHENTICATE;
  }
}
