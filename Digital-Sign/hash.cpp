
#include "hash.h"

long sumString(const string &input)
{
    long sum = 0L;
    long size = input.length();

    for (long i = 0; i < size; ++i)
    {
        sum += input[i];
    }

    return sum * sum * sum;
}


long divisionRemainder(long num)
{
    const long PRIME_NUMBER_10_DIGITS = 9576890767L;
    return num % PRIME_NUMBER_10_DIGITS;
}

long numberLength(long number)
{
    int counter = 0;
    while(number > 0 )
    {
        number /= 10;
        counter++;
    }
    return counter;
}

/** divides the number into n parts and returns their sum
 * Example: num = 123456789 nSeq = 3 -> returns 123 + 456 + 789
 */
long folding(long num, int nSeq)
{

    int size = numberLength(num) / nSeq;
    long sum = 0;
    long divider = (int)pow(10, nSeq);
    long temp = num;

    for (int i = 0; i < size; ++i)
    {
        sum += temp % divider;
        temp /= divider;
    }

    return sum;

}

long reverseNumber(long num, int length)
{
    long reversedNumber = 0;

    while(num > 0){
        reversedNumber += (num % 10) * (long)pow(10, --length);
        num /= 10;
    }
    return reversedNumber;
}


long digitRearrangement(long num)
{
    //const int BEGIN_INDEX = 0, END_INDEX = numberLength(num);
    const int BEGIN_INDEX = 3, END_INDEX = 7;
    const int LENGTH = END_INDEX - BEGIN_INDEX;

    long result = num / (long)pow(10, BEGIN_INDEX);
    result %= (long)pow(10, LENGTH);



    return reverseNumber(result, LENGTH);
}
