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

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef lval*(*lbuiltin)(lenv*,lval*);
enum { LVAL_ERR, LVAL_NUM, LVAL_SYM,LVAL_FUNC, LVAL_SEXPR, LVAL_QEXPR };

struct lenv {
  int count;
  char** syms;
  lval** vals;
};


typedef struct lval {
  int type;

  long num;
  char* err;
  char* sym;
  lbuiltin func;

  int count;
  struct lval** cell;
} lval;


lval* lval_num(long x);
lval* lval_err(char* fmt,...);
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
lval* builtin_op(lenv* e,lval* a, char* op);
lval* builtin_add(lenv* e, lval* a);
lval* builtin_sub(lenv* e, lval* a);
lval* builtin_mul(lenv* e, lval* a);
lval* builtin_div(lenv* e, lval* a);
lval* lval_eval(lenv* e,lval* v);
lval* lval_eval_sexpr(lenv* e,lval* v);
lval* lval_read_num(mpc_ast_t* t);
lval* lval_read(mpc_ast_t* t);
lval* builtin_head(lenv* e,lval* a);
lval* builtin_tail(lenv* ,lval* a);
lval* builtin_list(lenv* e,lval* a);
lval* builtin_eval(lenv* e,lval* a);
lval* builtin_join(lenv* e,lval* a);
lval* lval_join(lval* x, lval* y);
lval* builtin(lenv* e,lval* a, char* func);
lval* builtin_def(lenv* e,lval* a);
lval* lval_func(lbuiltin func);
lenv* lenv_new(void);
lval* lval_copy(lval* v);
void lenv_del(lenv* e);
lval* lenv_get(lenv* e,lval* k);
void lenv_put(lenv* e, lval* k,lval* v);
int main(int argc, char** argv);

#endif
