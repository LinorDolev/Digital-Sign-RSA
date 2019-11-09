#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string.h>

#include "errors.h"
#include "files.h"
#include "hash.h"
#include "rsa.h"


using namespace std;

/**Const Variables*/
const int MAX_KEY_LENGTH = 30;
const int FILE_PATH_LENGTH = 50;
const int NUM_OF_OPTS = 10, F_OPT = 0, M_OPT = 1, S_OPT = 2,
                           R_OPT = 3, K_OPT = 4, G_OPT = 5,
                           H_OPT = 6, E_OPT = 7, V_OPT = 8,
                           D_OPT = 9;

/**Function Prototypes*/

void parseOptions(int argc, char* argv[], char filePath[FILE_PATH_LENGTH],
                  char keyPath[MAX_KEY_LENGTH], char keyFileName[MAX_KEY_LENGTH], long* encryptedHash , bool options[NUM_OF_OPTS]);


void handleOptions(bool options[NUM_OF_OPTS], char filePath[FILE_PATH_LENGTH],
                   char keyPath[MAX_KEY_LENGTH], char keyFileName[MAX_KEY_LENGTH], long encryptedHash);

long handleHashOptions(bool options[NUM_OF_OPTS], long sumOfFileChars, RSAKey key, long signedHash);

long handleSigningHashes(bool options[NUM_OF_OPTS], long sumOfFileChars, RSAKey key);

long hashByOption(long sumOfFileChars, int option);

void validateHash(long hash, RSAKey key, long signedHash);

/**Main*/
int main(int argc, char* argv[])
{
    KeyPair keyPair;
    char keyPath[MAX_KEY_LENGTH], keyFileName[MAX_KEY_LENGTH], filePath[FILE_PATH_LENGTH];
    bool options[NUM_OF_OPTS];
    long encryptedHash = 0;

    parseOptions(argc, argv, filePath, keyPath, keyFileName, &encryptedHash, options);

    handleOptions(options, filePath, keyPath, keyFileName, encryptedHash);

    return 0;
}



void parseOptions(int argc, char* argv[], char filePath[FILE_PATH_LENGTH],
                  char keyPath[MAX_KEY_LENGTH], char keyFileName[MAX_KEY_LENGTH], long* encryptedHash , bool options[NUM_OF_OPTS])
{
    int opt;

    for (int i = 0; i < NUM_OF_OPTS ; ++i)
    {
        options[i] = false;
    }

    while((opt = getopt(argc, argv, ":f:msrk:g:hv:ed")) != -1)
    {
        switch(opt) {
            case 'f':
                options[F_OPT] = true;
                strcpy(filePath, optarg);
                break;

            case 'm':
                options[M_OPT] = true;
                break;

            case 's':
                options[S_OPT] = true;
                break;

            case 'r':
                options[R_OPT] = true;
                break;

            case 'k':
                options[K_OPT] = true;
                strcpy(keyPath, optarg);
                break;

            case 'g':
                options[G_OPT] = true;
                strcpy(keyFileName, optarg);
                break;

            case 'e':
                options[E_OPT] = true;
                printf("Encrypting File...\n");
                break;

            case 'd':
                options[D_OPT] = true;
                printf("Decrypting File...\n");
                break;

            case 'v':
                /*
                 * TODO Gets a hash value, decrypting it,
                 *  checks if it is equal to the hash
                 */
                options[V_OPT] = true;
                *encryptedHash = strtol(optarg, NULL, 10);
                break;

            case 'h':
                options[H_OPT] = true;
                cout << endl
                << "usage: "<< argv[0] << " [-f file-path] [-k key] [-m | -s | -r] [-v signed-hash] [-e | -d] [-g key-name]" << endl << endl
                << " -f      file path" << endl
                << " -k      RSA key file path to sign / encrypt file / validate with" << endl
                << " -m      division remainder method (mod)" << endl
                << " -s      folding method" << endl
                << " -r      digit rearrangement method" << endl
                << " -v [signed-hash]   validate hash" << endl
                << " -e      encrypt file (result will be saved with .enc)" << endl
                << " -d      decrypt file (result will be saved with .dec)" << endl
                << " -g      key name (public key will be saved as key_name.pub)" << endl
                << endl << endl;


                exit(0);

            case '?':
            default:
                cout << "unknown option" << endl;
                break;

        }
    }


}

void handleOptions(bool options[NUM_OF_OPTS], char filePath[FILE_PATH_LENGTH],
                   char keyPath[MAX_KEY_LENGTH], char keyFileName[MAX_KEY_LENGTH], long encryptedHash)
{
    RSAKey key;
    KeyPair keyPair;
    long sumOfFileChars;
    string fileAsString;

    if(options[F_OPT] && options[K_OPT])
    {
        fileAsString = readFile(filePath);
        sumOfFileChars = sumString(fileAsString);
        key = readKey(keyPath);
        handleHashOptions(options, sumOfFileChars, key, encryptedHash);

        if(options[E_OPT])
        {
            encryptFile(filePath, key);
        }
        else if(options[D_OPT])
        {
            decryptFile(filePath, key);
        }
    }

    else if(options[G_OPT])
    {
        keyPair = generateKeys();
        writeKeyPair(keyFileName, keyPair);
    }
    else
    {
        cerr << "usage: ./Digital_Sign [-f file path] " << endl
             << "\t\t    [-k private key file path to sign with] " << endl
             << "\t\t    [-m division remainder method (mod)]" << endl
             << "\t\t    [-s folding method]" << endl
             << "\t\t    [-r digit rearrangement method]" <<endl
             << "\t\t    [-e encrypt file (result will be saved with .enc)]" <<endl
             << "\t\t    [-d decrypt file (result will be saved with .dec)" << endl
             << "\t\t    [-v validate hash]" <<endl
             << "\t\t    [-g generate RSA key pair]" <<endl;
    }

}

long handleSigningHashes(bool options[NUM_OF_OPTS], long sumOfFileChars, RSAKey key)
{
    int i;
    const char* descriptions[] = {"Division Remainder Method (mod)", "Folding Method", "Digit Rearrangement Method"};
    long hash = 0, signedHash;

    for (i = M_OPT; i <= R_OPT ; ++i)
    {
        if(options[i])
        {
            hash = hashByOption(sumOfFileChars, i);
            signedHash = encryptDecrypt(key, hash);
            if(!options[V_OPT])
            {
                cout << descriptions[i - M_OPT] << ": " << signedHash << endl;
            }
        }
    }

    return hash;
}

void validateHash(long hash, RSAKey key, long signedHash)
{
    long decryptedHash = encryptDecrypt(key, signedHash);
    if(hash == decryptedHash)
    {
        printf("Hash was validated successfully\n");
    }
    else
    {
        printf("Hash is incorrect, file was corrupted or changed\n");
    }

}

long handleHashOptions(bool options[NUM_OF_OPTS], long sumOfFileChars, RSAKey key, long signedHash)
{

        long hash = 0;

        if(!options[M_OPT] && !options[S_OPT] && !options[R_OPT] && !options[E_OPT] && !options[D_OPT])
        {
            cerr << "Unable to find Hash function" << endl;
        }
        else
        {
            hash = handleSigningHashes(options, sumOfFileChars, key);

            if(options[V_OPT])
            {
                validateHash(hash, key, signedHash);
            }

        }

    return hash;
}

long hashByOption(long sumOfFileChars, int option)
{
    switch(option)
    {
        case S_OPT:
            return folding(sumOfFileChars);

        case M_OPT:
            return divisionRemainder(sumOfFileChars);

        case R_OPT:
            return digitRearrangement(sumOfFileChars);
    }
    return 0;
}