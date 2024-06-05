#include "PrimeGen.h"
#include "BigInt.h"
#include "utils.h"

void GenPrime(BigInt& n, int digNum)
{
    int i = 0;
    BigInt divisor;
    const int length = sizeof(prime) / sizeof(int);
    while (i != length)
    {
        n.Random(digNum);
        while (!n.IsOdd())
            n.Random(digNum);
        i = 0;
        for ( ; i < length; i++)
        {
            divisor = prime[i];
            if ((n % divisor) == 0)
                break;
        }
    }
}

bool RabinMiller(const BigInt& n, int digNum)
{
    BigInt r, a, y;
    unsigned int s, j;
    r = n - 1;
    s = 0;

    while (!r.IsOdd())
    {
        s++;
        r >> 1;
    }

    a.Randomsmall(digNum);

    y = BigInt::PowerMode(a, r, n);

    if((!(y == 1)) && (!(y == (n - 1))))
    {
        j = 1;
        while ((j <= s - 1) && (!(y == (n - 1))))
        {
            y = (y * y) % n;
            if (y == 1)
                return false;
            j++;
        }
        if (!(y == (n - 1)))
            return false;
    }
    return true;
}

BigInt GeneratePrime(int digNum)
{
    BigInt n;
    int i = 0;
    LOG("Prime number:");
    while (i < 5)
    {
        GenPrime(n, digNum);
        i = 0;
        for ( ; i < 5; i++)
        {
            if (!RabinMiller(n, digNum))
            {
                break;
            }
        }
    }
    LOGLN(" " << n);
    return n;
}
