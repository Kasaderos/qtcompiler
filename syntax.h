#ifndef SYNTAX_H
#define SYNTAX_H
#include "lexical.h"

template <class T, int max_size > class Stack
{
    T *s;
    int size;
    int top;
public:
    Stack();
    ~Stack();
    void reset();
    void push(T i);
    T pop();
    T get_top();
    bool is_empty();
    bool is_full();
    void print();
};

class Poliz {
    Lex *p;
    int pos;
    int size;
public:
    Poliz(int max_size);
    ~Poliz();
    void put_lex(Lex l);
    void put_lex(Lex l, int place);
    void blank();
    int get_pos();
    Lex & operator[] (int index);
    void print();
};

class Parser {
    Lex curr_l;
    Lex tmp;
    type_lex curr_t;
    type_lex type;
    double curr_v;
    Scanner scan;
    Stack < int, 100 > st_int;
    Stack < Lex, 100 > st_lex;
    void P();
    void D();
    void D1();
    void B();
    void S();
    void E();
    void E1();
    void T();
    void F();

    void dec();
    void check_id();
    void check_op();
    void check_not();
    void eq_type();
public:
    Poliz prog;
    Parser(const char * program);
    void analyze();
    void gl();
    void gln();
};

class Executer {
    Lex curr_l;
public:
    void execute(Poliz & prog);
};

class Interpretator {
    Parser pars;
    Executer E;
public:
    Interpretator(char * program) : pars(program) {};
    void interpretation();
};

#endif // SYNTAX_H
