#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "user.h"
#include "question.h"
#include "answer.h"

enum{
  CONNECTED, SIGNUP, UNAUTHENTICATE, AUTHENTICATE, READY, PLAYING
};

#define WANT_TO_SIGNUP  "i want to signup"
#define WANT_TO_SIGNIN  "i want to signin"
#define ALLOW_TO_SIGNUP "you are allowed to signup"

typedef struct protocol{
  int p_state;
  user p_user_info;
  question p_question;
  int score;
  answer p_answer;
  char p_message[256];
}protocol;
#endif
