// Gavin Love - CS4280 - TestScanner
#include <iostream>
#include <string>
#include <cstdlib> // For std::atoi

#include "node.h"
#include "token.h"
#include "scanner.h"
#include "testScanner.h"

using namespace std;

void testScanner(char* file, char* baseFile, int valC) {
	int tokenLine = 1; // Initialize token line number to 1
	int lineReady = 0;
	string nextCol = "";
	string tokenType = "";
	string totalInstance = "";
	string strTokenLine = "1"; // Initialize strTokenLine to "1"
	while (tokenType != "NL" && tokenType != "EOFTk" && tokenType != "ERR" && tokenType != "Empty") {
		string token = scanner(file, baseFile, totalInstance, strTokenLine);
		if (token == "FileError") {
			break;
		}else if(token == "Empty"){
			cout << "EOFTk" << endl;
			tokenType = "Empty";
			break;
		}
		if (lineReady == 1){
			tokenLine += 1;
			lineReady = 0;
		}
		//cout << token << endl;
		int phraseLength = token.length();
		tokenType = "";
		string tokenInstance = "";
		int delimiter = 0, prevLocation = 0, currentLocation = 0;
		for (int i = 0; i < phraseLength; i++) {
			int ascii = token[i];
			if (ascii == 126) { // ASCII code for '~'
				delimiter += 1;
				currentLocation = i;
				if(delimiter == 5){
					currentLocation -= 1;
					prevLocation += 1;
				}//else if(delimiter == 3){
				//currentLocation -= 1;
				//}
			}
			for (int x = prevLocation; x < currentLocation; x++) {
				if (delimiter == 1) {
					tokenType += token[x];
					if (x == currentLocation - 1) {
						delimiter += 1;
					}
				} else if (delimiter == 3) {
					if (x == currentLocation - 1) {
						delimiter += 1;
					}
					tokenInstance += token[x+1];
				} else if (delimiter == 5) {
					lineReady = 1;
				}
			}
			prevLocation = currentLocation;
		}
		if (tokenType == "ERR" || tokenType == "NL") {
			break;
		}
		// Remove '~' from Token Instance
		string tokenInstanceOutput = tokenInstance;
		if(tokenInstanceOutput.size() >= 1){
			tokenInstanceOutput.erase(tokenInstanceOutput.size() - 1);
		}
		// Comments are stored as Tokens but are not displayed
		// If you would like for Comments to be displayed for your enjoyment,
		// please remove comment out line 80
		if(tokenType == "EOFTk"){
			cout << tokenType << endl;
		}else if(tokenType == "Comment"){
			
		}else{
			cout << tokenType << " token \t" << tokenInstanceOutput; // << " }\tLine: ";
			if(tokenInstance.length() <= 7){
				cout << " \t\tLine: " << tokenLine << endl;
			}else{	
				cout << " \tLine: " << tokenLine << endl;
			}
		}
		totalInstance += tokenInstance;
	}
}

