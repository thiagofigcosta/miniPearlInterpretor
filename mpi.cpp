#include <iostream>
#include "lexical/LexicalAnalysis.hpp"
#include "syntactical/SyntacticalAnalysis.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s [MiniPerl File]\n", argv[0]);
        return 1;
    }
    try {
        LexicalAnalysis l(argv[1]);
        SyntacticalAnalysis s(l);
        s.start();
    } catch (std::string msg) {
        fprintf(stderr, "Internal error: %s\n", msg.c_str());
        return 2;
    }
    return 0;
}
