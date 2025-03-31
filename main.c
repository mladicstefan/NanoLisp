#include "mpc.h"

#ifdef _WIN32

static char buffer[2048];

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer,2048,stdin);

  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy,buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* unused) {}

#else 
#include <editline/readline.h>
#include <editline/history.h>
#endif

long eval_op(long x, char* op,long y){
  if (strcmp(op,"+") == 0) {return x+y;}
  if (strcmp(op,"-") == 0) {return x-y;}
  if (strcmp(op,"*") == 0) {return x*y;}
  if (strcmp(op,"/") == 0) {return x/y;}
  return 0;
}

int main(int argc, char** argv){
  return 0;
}
