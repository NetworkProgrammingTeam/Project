#ifndef HISTORY_HELPER_H
#define HISTORY_HELPER_H
#include "../lib/user.h"

int match_history(user , int);  /*check whether the id was sent by user*/
void write_history(user, int);  /*write id that sent to user*/

#endif
