#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "title_helper.h"

char *get_title_from_id(int t_id){
  char *t_name;
  t_name = (char *)malloc(64);
  FILE *f;
  f = fopen("title/title_id","r");
  int i;
  char s[256];
  for(i=0; i<= t_id; i++){
    memset(s,'\0',strlen(s));
    fscanf(f,"%[^\n]\n",s);
  }
  for(i=0; s[i] != '|'; i++)
  strcat(t_name,s+2);
  fclose(f);
  return t_name;
}

char *get_title_fname(title t){
  int pick = t.pick;
  char *title_fname;
  title_fname = (char *)malloc(256);
  if(pick == 0){
    strcpy(title_fname,t.title1);
  } else if(pick == 1){
    strcpy(title_fname,t.title2);
  } else{
    //TODO
  }
  return title_fname;
}

void get_question_from_title(char *f_name, question *q){
  FILE *f;
  f = fopen(f_name,"r");
  if(f != NULL){
    int i;
    int pos = random_from_0_to_max(7);
    char s[256];
    for(i = 0; i <= pos; i++){
      memset(s,'\0',sizeof(s));
  		fscanf(f,"%[^\n]\n",s);
    }
    char *token = strtok(s,"|");	// token = id
		q->question_id = atoi(token);
		token = strtok(NULL,"|");	// token = question
		strcpy(q->question,token);
		token = strtok(NULL,"|");	// token = answer1
		strcpy(q->answer1,token);
		token = strtok(NULL,"|");	// token = answer2
		strcpy(q->answer2,token);
		token = strtok(NULL,"|");	// token = answer3
		strcpy(q->answer3,token);
		token = strtok(NULL,"|");	// token = answer4
		strcpy(q->answer4,token);
  }
  fclose(f);
}
