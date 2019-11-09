
#ifndef DIGITAL_SIGN_FILES_H
#define DIGITAL_SIGN_FILES_H

#include <string>
#include <fstream>
#include <iostream>

#include "hash.h"
#include "rsa.h"
#include "errors.h"

using namespace std;

string readFile(const char *fileName);
RSAKey readKey(const char *fileName);
void writeKeyPair(const char *fileName, KeyPair keyPair);

void writeKey(const char *fileName, RSAKey key);

void encryptFile(const char *fileName, RSAKey key);

void decryptFile(const char *fileName, RSAKey key);


#endif //DIGITAL_SIGN_FILES_H
