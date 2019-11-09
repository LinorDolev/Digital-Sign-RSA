#ifndef DIGITAL_SIGN_HASH_H
#define DIGITAL_SIGN_HASH_H

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

long sumString(const string& input);

string asHex(long num);

long divisionRemainder(long num);

long folding(long num, int nSeq=2);

long digitRearrangement(long num);

#endif //DIGITAL_SIGN_HASH_H
