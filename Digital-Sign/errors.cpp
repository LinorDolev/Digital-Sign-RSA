
#include "errors.h"

void checkArguments(int argc, char **argv)
{
    if(argc < 3)
    {
        cerr << "usage: ./LinorSign filename rsa-key-file" << endl;
        exit(1);
    }

    /*
     * TODO Check that the files are actually exists
     */
}

void checkFileExistence(ifstream& inFile, const char* fileName)
{
    if (!inFile)
    {
        cerr << "Unable to open file " << fileName << endl;
        exit(1);   // call system to stop
    }
}
