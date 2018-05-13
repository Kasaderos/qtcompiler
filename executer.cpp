#include "lexical.h"
#include "syntax.h"
#include <cmath>
extern Table_ident TID;

void Interpretator::interpretation()
{
    pars.analyze();
    //cout << "Start execute: " << endl;
    E.execute(pars.prog);
}

void Executer::execute(Poliz & prog) {
    Stack< Lex, 100 > args;
    int i, index = 0;
    Lex lex1, lex2, lex3;
    int size = prog.get_pos();

    while (index < size) {
        //args.print();
        //cout << endl;
        curr_l = prog[index];
        switch (curr_l.get_type())
        {
        case LEX_INUM:
        case LEX_FNUM:
        case POLIZ_ADDRESS:
        case POLIZ_LABEL:
        case LEX_TRUE:
        case LEX_FALSE:
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
        case LEX_MOD:
            lex1 = args.pop();
            lex1 = to_const(lex1);
            if (lex1.get_val() == 0) throw "error division by zero";
            args.push(args.pop() % lex1);
            break;
        case LEX_ASSIGN:
            lex1 = args.pop();
            lex2 = args.pop();
            lex3 = to_const(lex1);
            i = (int)lex2.get_val();
            if (lex3.get_type() == LEX_FNUM && TID.var[i].get_type() == LEX_INT)
                throw "impilcit float to int";
            TID.var[i].set_val(lex3.get_val());
            TID.var[i].assign = true;
            break;
        case LEX_AND:
            lex1 = to_const(args.pop());
            lex2 = to_const(args.pop());
            args.push((int)lex1.get_val() && (int)lex2.get_val());
            break;
        case LEX_OR:
            lex1 = to_const(args.pop());
            lex2 = to_const(args.pop());
            args.push((int)lex1.get_val() || (int)lex2.get_val());
            break;
        case LEX_SEQ:
            lex2 = to_const(args.pop());
            lex1 = to_const(args.pop());
            args.push((int)lex1.get_val() == (int)lex2.get_val());
            break;
        case LEX_SNQ:
            lex2 = to_const(args.pop());
            lex1 = to_const(args.pop());
            args.push((int)lex1.get_val() != (int)lex2.get_val());
            break;
        case LEX_SG:
            lex2 = to_const(args.pop());
            lex1 = to_const(args.pop());
            args.push((int)lex1.get_val() > (int)lex2.get_val());
            break;
        case LEX_SGE:
            lex2 = to_const(args.pop());
            lex1 = to_const(args.pop());
            args.push((int)lex1.get_val() >= (int)lex2.get_val());
            break;
        case LEX_SL:
            lex2 = to_const(args.pop());
            lex1 = to_const(args.pop());
            args.push((int)lex1.get_val() < (int)lex2.get_val());
            break;
        case LEX_SLE:
            lex2 = to_const(args.pop());
            lex1 = to_const(args.pop());
            args.push((int)lex1.get_val() <= (int)lex2.get_val());
            break;
        case POLIZ_GO:
            index = args.pop().get_val() - 1;
            break;
        case POLIZ_FGO:
            lex1 = args.pop();
            if (!args.pop().get_val())
                index = (int)lex1.get_val() - 1;
            break;
        case LEX_PRINT:
            lex1 = args.pop();
            lex1 = to_const(lex1);
            if (lex1.get_type() == LEX_INUM)
                cout << (int)lex1.get_val() << endl;
            else
                cout << lex1.get_val() << endl;
            break;
        case LEX_INPUT:
            double d;
            cin >> d;
            lex1 = args.pop();
            i = (int)lex1.get_val();
            TID.var[i].set_val(d);
            TID.var[i].assign = true;
            break;
        case LEX_SIN:
            lex1 = args.pop();
            lex1 = to_const(lex1);
            args.push(sin(lex1.get_val()));
            break;
        case LEX_COS:
            lex1 = args.pop();
            lex1 = to_const(lex1);
            args.push(cos(lex1.get_val()));
            break;
        case LEX_LOG:
            lex1 = args.pop();
            lex1 = to_const(lex1);
            args.push(log(lex1.get_val()));
            break;
        default:
            throw "POLIZ: unexpected elem";
        }
        ++index;
    }
    //cout << "Finish of executing!!!" << endl;
}


