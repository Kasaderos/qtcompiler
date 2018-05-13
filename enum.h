#ifndef ENUM_H
#define ENUM_H
enum type_lex {
    LEX_NULL,
    LEX_ASSIGN,
    LEX_COMMA,
    LEX_INT,
    LEX_FLOAT,
    LEX_STR,
    LEX_CHAR,
    LEX_BOOL,
    LEX_TRUE,
    LEX_FALSE,
    LEX_FNUM,
    LEX_INUM,
    LEX_ID,
    LEX_INPUT,
    LEX_PRINT,
    LEX_PLUS,
    LEX_MINUS,
    LEX_MUL,
    LEX_DIV,
    LEX_MOD,
    LEX_LPAREN, // )
    LEX_RPAREN, // )
    LEX_LSQR, // [
    LEX_RSQR, // ]
    LEX_BEGIN,
    LEX_END,
    LEX_IF,
    LEX_ELSE,
    LEX_WHILE,
    LEX_COLON,
    LEX_SEMICOLON,
    LEX_AND,
    LEX_OR,
    LEX_NOT,
    LEX_SEQ, // ==
    LEX_SNQ, // !=
    LEX_SG, // >
    LEX_SL, // <
    LEX_SGE, // >=
    LEX_SLE, // <=
    POLIZ_GO,
    POLIZ_FGO,
    POLIZ_LABEL,
    POLIZ_ADDRESS,
};

/*
    P     -> Dcls B
    D     -> D1 {;D1}
    D1    -> [int | float] id {,id}
    B     -> { S{;S} }
    S     -> I = E | if E B else B | while E B | print(E)
    E     -> E1 [=|<|>|!=] E1 | E1
    E1    -> T {[+|-|or] T}
    T     -> F {[*|/|and] F}
    F     -> I | N | L | not F | (E)
    L     -> true | false
    I     -> C | IC | IR
    N     -> R | NR
    C     -> a|b| ... |z|A|B| ... |Z
    R     -> 0|1|2| ... |9
*/
#endif // ENUM_H
