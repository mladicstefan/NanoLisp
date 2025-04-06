#ifndef LISPY_H
#define LISPY_H

#include "mpc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
char* readline(char* prompt);
void add_history(char* unused);
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

#define LASSERT(args, cond, err) \
  if (!(cond)) { lval_del(args); return lval_err(err); }

enum { LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR };

typedef struct lval {
  int type;
  long num;
  char* err;
  char* sym;
  int count;
  struct lval** cell;
} lval;

lval* lval_num(long x);
lval* lval_err(char* m);
lval* lval_sym(char* s);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
void lval_del(lval* v);
lval* lval_add(lval* v, lval* x);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
void lval_print(lval* v);
void lval_expr_print(lval* v, char open, char close);
void lval_println(lval* v);
lval* builtin_op(lval* a, char* op);
lval* lval_eval(lval* v);
lval* lval_eval_sexpr(lval* v);
lval* lval_read_num(mpc_ast_t* t);
lval* lval_read(mpc_ast_t* t);
lval* builtin_head(lval* a);
lval* builtin_tail(lval* a);
lval* builtin_list(lval* a);
lval* builtin_eval(lval* a);
lval* builtin_join(lval* a);
lval* lval_join(lval* x, lval* y);
lval* builtin(lval* a, char* func);
int main(int argc, char** argv);

#endif
