

#ifndef DIGITAL_SIGN_ERRORS_H
#define DIGITAL_SIGN_ERRORS_H

#include <iostream>
#include <fstream>
using namespace std;

void checkArguments(int argc, char* argv[]);

void checkFileExistence(ifstream &inFile, const char *fileName);
#endif //DIGITAL_SIGN_ERRORS_H
