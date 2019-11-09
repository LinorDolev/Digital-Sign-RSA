

#include <cstring>
#include <iostream>
#include <stdio.h>

#include "rsa.h"
#include "files.h"

const int FILE_PATH_LENGTH = 100;

string readFile(const char *fileName)
{
    ifstream inFile;
    inFile.open(fileName, ios_base::binary);
    checkFileExistence(inFile, fileName);

    string fileAsString, temp;
    while(inFile >> temp)
    {
        fileAsString += temp;
    }

    inFile.close();

    return fileAsString;
}

void decryptFile(const char *fileName, RSAKey key)
{
    char encFileName[FILE_PATH_LENGTH];

    FILE *readfile, *writeFile;

    strcpy(encFileName, fileName);
    strcat(encFileName, ".dec");

    readfile = fopen(fileName, "r");
    writeFile = fopen(encFileName, "w");

    while(!feof(readfile))
    {
        char temp = 0;
        long encrypted = 0, decrypted = 0;
        fscanf(readfile, "%li ", &encrypted);


        decrypted = encryptDecrypt(key, encrypted);
        temp = decrypted;
        fprintf(writeFile, "%c", temp);

    }


    fclose(readfile);
    fclose(writeFile);
}

void encryptFile(const char *fileName, RSAKey key)
{
    char encFileName[FILE_PATH_LENGTH];

    FILE *readfile, *writeFile;
    strcpy(encFileName, fileName);
    strcat(encFileName, ".enc");

    readfile = fopen(fileName, "r");
    writeFile = fopen(encFileName, "w");

    while(!feof(readfile))
    {
        char temp;
        long asLong, encrypted;
        fscanf(readfile, "%c", &temp);

        if(!feof(readfile))
        {
            asLong = temp;
            encrypted = encryptDecrypt(key, asLong);
            fprintf(writeFile, "%li ", encrypted);
        }

    }

    fclose(readfile);
    fclose(writeFile);
}

RSAKey readKey(const char *fileName)
{
    ifstream inFile;
    inFile.open(fileName);
    checkFileExistence(inFile, fileName);
    long long n, index;

    inFile >> index;
    inFile >> n;
    inFile.close();

    return {index, n};
}

void writeKeyPair(const char *fileName, KeyPair keyPair)
{
    const int KEY_FILE_NAME_LEN = 40;
    char publicKeyFileName[KEY_FILE_NAME_LEN];
    strcpy(publicKeyFileName, fileName);
    strcat(publicKeyFileName, ".pub");

    writeKey(fileName, keyPair.pr);
    writeKey(publicKeyFileName, keyPair.pu);
}

void writeKey(const char *fileName, const RSAKey key)
{

    long index = key.index;
    long n = key.n;

    ofstream outFile;
    outFile.open(fileName);

    outFile << index << " " <<  n;

    outFile.close();
}
