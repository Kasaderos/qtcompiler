#include <iostream>
#include <stdio.h>
#include <fstream>
#include "lexical.h"
#include "syntax.h"
using namespace std;

Table_ident TID;
void check_scan();
int main(int argc, char **argv)
{
    Interpretator interpretator(argv[1]);
    try {
        interpretator.interpretation();
    }
    catch (Lex lex) {
        cout << Scanner::LEXS[lex.get_type()] << " error" << endl;
    }
    catch (const char * str) {
        cout << str << endl;
    }
    catch (string str) {
        cout << str << endl;
    }
    catch (char c){
        cout << "char error = " << c << endl;
    }
    //check_scan();
    return 0;
}

void check_scan() {
    Scanner scan("/home/nate/nate/qtcompiler/file.txt");
    try {
        while (1) {
            Lex t = scan.gl();
            cout << t << endl;
            if (t.get_type() == LEX_END)
                break;
        }
    }
    catch (char c) {
        cout << "error" << c << endl;
    }
    TID.print();
}
