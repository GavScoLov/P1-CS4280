#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>

#include "testScanner.h"
#include "scanner.h"
#include "node.h"
#include "token.h"

using namespace std;

int fsaTable[13][18] = {
        //Digit,   a-z,   A-Z,    WS,   EOF,     %,     .,     !,     *,     ",     ?,     ,,     ;,     $,     #, NewLn, ERROR
        { ERR01,    s2,    s2,    s1, FIN04,    s4,    s6,    s6,    s7, ERR01,    s9,   s11, ERR01, ERR01,   s13,    s1, ERR02 },      // S1
        {    s3, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR02 },      // S2
        {    s3, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, FIN01, ERR02 },      // S3
        {    s5, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR01, ERR02 },      // S4
        {    s5, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, FIN02, ERR02 },      // S5
        { FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, ERR02 },      // S6
        { FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03,    s8, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, ERR02 },      // S7
        { FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, ERR02 },      // S8
        { FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03,   s10, FIN03, FIN03, ERR02 },      // S9
        { FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, ERR02 },      // S10
        { FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03,   s12, FIN03, FIN03, FIN03, ERR02 },      // S11
        { FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, FIN03, ERR02 },      // S12
        {   s13,   s13,   s13,   s13,   s13,   s13,   s13,   s13,   s13,   s13,   s13,   s13,   s13,   s13, FIN00,   s13,   s13 }       // S13
};

int getCharVal(char ch){
        int ascii = ch; // Get ASCII value of character
        if(ascii >= 48 && ascii <= 57){
                return 0;       // Digits
        }else if(ascii >= 97 && ascii <= 122){
                return 1;       // Lowercase
        }else if(ascii >= 65 && ascii <= 90){
                return 2;       // Uppercase
        }else if(ascii == 32){
                return 3;       // Whitespace
        }else if(ascii == EOF){
                return 4;       // EOF Token
        }else if(ascii == 37){
                return 5;       // %
        }else if(ascii == 46){
                return 6;       // .
        }else if(ascii == 33){
                return 7;       // !
        }else if(ascii == 42){
                return 8;       // *
        }else if(ascii == 34){
                return 9;       // "
        }else if(ascii == 63){
                return 10;      // ?
        }else if(ascii == 44){
                return 11;      // ,
        }else if(ascii == 59){
                return 12;      // ;
        }else if(ascii == 36){
                return 13;      // $
        }else if(ascii == 35){
                return 14;      // #
        }else if(ascii == 10){
                return 15;      // Newline Token
        }else{
                return 16;      // Anything Else
        }
}
/*
string scanner(char* file, char* baseFile, string prevInstance, string prevLine){
        string token = fsaDriver(file, baseFile, prevInstance, prevLine);
        return token;
}*/


//string fsaDriver(char* file, char* baseFile, string prevInstance, string prevLine){
string scanner(char* file, char* baseFile, string prevInstance, string prevLine){
        // Initialization/Declaration:
        int k = 0, x = 0, w = 0, lineCount = 0;// addLine = 0;
        int currentState = s1;
        char fileData;
        char fileArr[MAX];
        char fileWord[MAX];
        //bool eofReached = false;
        string words[MAX];      // Array of Words from File
        string tokenErr = "";
        string token = "";
        string tokenType = "";
        string tokenInstance = "";
        int tokenLine = 0;

        // Open File for Reading
        FILE *filePtr = fopen(file, "r");
        // Check if file opened correctly
        if(filePtr){
                // Read words separated by WS into an array of strings
                while(fscanf(filePtr, " %s", fileWord) == 1 && k < MAX){
                        words[k] = fileWord;
                        k++;
                }
                // Rewind file pointer
                rewind(filePtr);
                // Loop through file and store each character into 'fileArr'
                while(fscanf(filePtr, "%c", &fileData) == 1){
                        fileArr[x] = fileData;
                        x++;
                }
                w = x;
        }else{
                cout << "PROGRAM ERROR: File Not Found" << endl;
                token = "FileError";
                return token;
        }
        fclose(filePtr);

        // Start For Loop where Previous Token Left off
        int prevLength = prevInstance.length();
        int prevCol = 0;
        if(prevLength >= w){
                tokenType = "EOFTk~";
                return tokenType;
        }
        string strTokenLine = prevLine;
        for(int z = prevLength; z < w; z++){
                // Get fsaTable column value
                int colNum = getCharVal(fileArr[z]);
                int fsa = fsaTable[currentState][colNum];

                if(colNum != 3){
                        if(colNum != 15){
                                tokenInstance += fileArr[z];
                        }else if(colNum == 15)
                                strTokenLine += "1";
                }else if(colNum == 3){
                        if(tokenInstance[0] == '#'){
                                tokenInstance += " ";
                        }
                }
                //cout << "Arr: " << fileArr[z] << " Col: " << colNum << " Fsa: " << fsa << endl;
                if(fsa != 0){
                        // Final States
                        if(fsa == FIN00){
                                tokenType = "Comment";
                //              tokenInstance += " ";
                        }else if(fsa == FIN01){
                                tokenType = "T1";
                        }else if(fsa == FIN02){
                                tokenType = "T2";
                        }else if(fsa == FIN03){
                                tokenType = "T3";
                        }else if(fsa == FIN04){
                                if(colNum == 15)
                                        tokenInstance = "NL";
                                tokenType = "EOFTk";
                        }else if(fsa == ERR01 || fsa == ERR02){
                                if(fsa == ERR01){
                                        tokenErr = "01";
                                        cout << "SCANNER ERROR: " << tokenInstance << " on line: " << strTokenLine << endl;
                                }else{
                                        tokenErr = "02";
                                        cout << "SCANNER ERROR: " << tokenInstance << " is an unaccepted character on line: " << strTokenLine << endl;
                                }
                                token = (("ERR~") + (tokenErr + "~") + (strTokenLine + "~"));
                                return token;
                        }
                        if(fsa == FIN00 || fsa == FIN01 || fsa == FIN02 || fsa == FIN03 || fsa == FIN04){
                                token = ((tokenType + "~") + ((tokenInstance + "~") + (strTokenLine + "~")));
                                return token;
                        }
                }
                prevCol = colNum;
                currentState = fsa;
                x = z;
        }
        if(x == w-1 || x == w){
                token = "Empty";
                return token;
        }
}
