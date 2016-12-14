#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "user.h"
#include "question.h"
#include "answer.h"
#include "title.h"

enum{
  CONNECTED, SIGNUP, UNAUTHENTICATE, AUTHENTICATE, READY, PLAYING
};

#define WANT_TO_SIGNUP  "i want to signup"
#define WANT_TO_SIGNIN  "i want to signin"
#define ALLOW_TO_SIGNUP "you are allowed to signup"
#define WANT_TO_PLAY "i want to play"
#define I_AM_READY "i am ready"
#define ALLOW_PLAY "you are allowed to play"
#define SEND_TITLE "send title"

typedef struct protocol{
  int p_state;
  user p_user_info;
  title p_title;
  question p_question;
  int score;
  answer p_answer;
  char p_message[256];
}protocol;
#endif
