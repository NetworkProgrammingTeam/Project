#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "play_helper.h"
#include "random_helper.h"
#include "history_helper.h"
#include "title_helper.h"

void send_titles(protocol *p){
  p->p_state = PLAYING;
  memset(p->p_message,'\0',sizeof(p->p_message));
  int id;
  do{
    id = random_title_id();
    printf("%d\n", id);
  } while(match_history(p->p_user_info,id));
  write_history(p->p_user_info,id);
  strcpy(p->p_title.title1,get_title_from_id(id));
  strcpy(p->p_title.title2,"music");
  p->p_title.pick = -1;
  p->score = 200;
}

void send_question(protocol *p, title t){
  char f_name[256] = "title/";
  strcat(f_name,get_title_fname(t));                /*f_name = "title/ title_name"*/
  strcat(p->p_question.title,get_title_fname(t));   /*p_question.title = title_name*/
  get_question_from_title(f_name,&(p->p_question));
}
