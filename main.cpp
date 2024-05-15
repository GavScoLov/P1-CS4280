#include <iostream>
#include <fstream>
#include <cstring>

#include "node.h"
//#include "traversals.h"
#include "testScanner.h"

using namespace std;

int main(int argc, char* argv[]) {
        int valArgc = 0;
        char* originFile = NULL;
        const char *fileType = ".txt";
        const char *keyType = "out";
        char *file;// *baseFile;
        //FILE *userFile = NULL;
        //istream *keyFile = NULL;
        //char userInput[MAX];

        // Allocate Memory for 'argv[1]' to save to 'file'
        // Prepare 'baseFile' for use in Traversals
        if(argv[1]){
                file = (char*)malloc(sizeof(argv[1]));
                originFile = (char*)malloc(sizeof(argv[1]));
                file = argv[1];
                strcpy(originFile, file);
                strcat(file, fileType);
                valArgc = 2;
        }else{
                file = (char*)malloc(sizeof("out"));
                strcpy(file,keyType);
                originFile = strdup(keyType);
        }

        // Check Invocation
        if(argc > 2){
                // Too many arguments
                cout << "Fatal Error:\tToo many arguments" << endl;
                cout << "Proper Usage:\tP0 [filename]" << endl;
                return 0;
        }else if(argc < 2){
                valArgc = 1;
        }

        //cout << "Base File: " << originFile << endl;

        // Call Test Scanner
        //cout << "Test Scanner: Running..." << endl;
        testScanner(file, originFile, valArgc);

        //buildTree(file, originFile, valArgc);
        // Close File
        //fclose(userFile);

        return 0;
}
