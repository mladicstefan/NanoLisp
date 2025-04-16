#ifndef LISPY_H
#define LISPY_H

#include "mpc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//#ifdef _WIN32
char* readline(char* prompt);
void add_history(char* unused);
//#else
//#include <editline/readline.h>
//#include <editline/history.h>
//#endif

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef lval*(*lbuiltin)(lenv*,lval*);
enum { LVAL_ERR, LVAL_NUM, LVAL_SYM,LVAL_STR,LVAL_FUNC, LVAL_SEXPR, LVAL_QEXPR };

struct lenv {
  lenv* par;
  int count;
  char** syms;
  lval** vals;
};



typedef struct lval {
  int type;

  long num;
  char* err;
  char* sym;
  char* str;

  lbuiltin func;
  lenv* env;
  lval* formals;
  lval* body;

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
lval* lval_str(char* s);
void lval_print_str(lval* v);
lval* lval_read_str(mpc_ast_t* t);
lenv* lenv_new(void);
lval* lval_copy(lval* v);
lval* lval_lambda(lval* formals,lval* body);
void lenv_del(lenv* e);
lval* lenv_get(lenv* e,lval* k);
lval* builtin_def(lenv* e,lval* a);
lval* builtin_put(lenv* e,lval* a);
lval* builtin_var(lenv* e,lval* a,char* func);
void lenv_put(lenv* e, lval* k,lval* v);
void lenv_def(lenv* e, lval*k, lval* v);
lenv* lenv_copy(lenv* e);
lval* builtin_lambda(lenv* e, lval* a);
lval* lval_call(lenv* e, lval* f, lval* a);

// conditionals
lval* builtin_if(lenv* e, lval* a);
// comparisons
lval* builtin_gt(lenv* e, lval* a);
lval* builtin_ge(lenv* e, lval* a);
lval* builtin_lt(lenv* e, lval* a);
lval* builtin_le(lenv* e, lval* a);
lval* builtin_ord(lenv* e, lval* a, char* op);
int lval_eq(lval* x, lval* y);
lval* builtin_cmp(lenv* e, lval*a, char* op);

lval* builtin_eq(lenv* e, lval* a);
lval* builtin_ne(lenv* e, lval* a); 

int main(int argc, char** argv);

char* ltype_name(int t); 
#endif
