#include "lexical.h"
#include "syntax.h"

extern Table_ident TID;

void Interpretator::interpretation()
{
    pars.analyze();
    cout << "Start execute: " << endl;
    E.execute(pars.prog);
}

void Executer::execute(Poliz & prog) {
    Stack< Lex, 100 > args;
    int i, index = 0;
    Lex lex1, lex2, lex3;
    int size = prog.get_pos();

    while (index < size) {
        args.print();
        cout << endl;
        curr_l = prog[index];
        switch (curr_l.get_type())
        {
        case LEX_INUM:
        case LEX_FNUM:
        case POLIZ_ADDRESS:
            args.push(curr_l);
            break;
        case LEX_ID:
            i = (int)curr_l.get_val();
            if (TID.var[i].assign) {
                args.push(curr_l);
                break;
            }
            else
                throw "POLIZ: indefinite identifier";
        case LEX_PLUS:
            args.push(args.pop() + args.pop());
            break;
        case LEX_MINUS:
            lex1 = args.pop();
            args.push(args.pop() - lex1);
            break;
        case LEX_MUL:
            args.push(args.pop() * args.pop());
            break;
        case LEX_DIV:
            lex1 = args.pop();
            lex1 = to_const(lex1);
            if (lex1.get_val() == 0) throw "error division by zero";
            args.push(args.pop() / lex1);
            break;
        case LEX_ASSIGN:
            lex1 = args.pop();
            //cout << "lvalue : " << lex1.v_lex.d << endl;
            lex2 = args.pop();
            lex3 = to_const(lex1);
            i = (int)lex2.get_val();
            if (lex3.get_type() == LEX_FNUM && TID.var[i].get_type() == LEX_INT)
                throw "impilcit float to int";
            //cout << "rvalue : " << lex3.v_lex.d << endl;
            TID.var[i].set_val(lex3.get_val());
            TID.var[i].assign = true;
            break;
        case LEX_PRINT:
            lex1 = args.pop();
            lex1 = to_const(lex1);
            if (lex1.get_type() == LEX_INUM)
                cout << (int)lex1.get_val() << endl;
            else
                cout << lex1.get_val() << endl;
            break;
        default:
            throw "POLIZ: unexpected elem";
        }
        ++index;
    }
    cout << "Finish of executing!!!" << endl;
}


