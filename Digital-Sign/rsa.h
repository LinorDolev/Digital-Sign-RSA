
#ifndef DIGITAL_SIGN_RSA_H
#define DIGITAL_SIGN_RSA_H

#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

struct rsa_key{
    long long index;
    long long n;

    friend ostream& operator<<(ostream& os, rsa_key& key){

        os << "{ index: " << key.index  << ", n: " << key.n << " }";
        return os;
    }
}
typedef RSAKey;


struct {
    RSAKey pr;
    RSAKey pu;
}
typedef KeyPair;


long long fastPower(long long base, long long pow, long long mod);
//long fastPower(long base, long pow, long mod);

long long inverseGCD(long long a, long long mod);

KeyPair generateKeys();

long long gcd(long long a, long long b);


//long encryptDecrypt(RSAKey key, long input);

long long encryptDecrypt(RSAKey key, long long input);


#endif //DIGITAL_SIGN_RSA_H
