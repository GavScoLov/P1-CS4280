// Gavin Love - CS4280 - Token Header
// Define all token types here:
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

using namespace std;



// T1:
// Begin with single letter: (a-z;A-Z)
// Followed by 1 or more: (0-9)

// T2:
// Begin with: (%)
// Followed by 1 or more: (0-9)

// T3:
// (.) (!) (,) (,;) (?) (?$) (*) (*")

typedef enum {
        ERR01 = -1,      // {char} cannot follow {char}
        ERR02 = -2,      // No Token begins with {char}
        s1 = 0, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13,
        FIN00 = 1000,    // Comment
        FIN01 = 1001,    // Token Type : T1
        FIN02 = 1002,    // Token Type : T2
        FIN03 = 1003,    // Token Type : T3
        FIN04 = 1004     // Token Type : EOF
} state;

#endif
