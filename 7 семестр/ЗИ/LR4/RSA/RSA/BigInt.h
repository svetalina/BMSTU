#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include "globalData.h"

using namespace std;

class BigInt {
public:
    BigInt();
    BigInt(const int&);
    BigInt(const BigInt&);
    BigInt(string, int);

    void GenFromHexString(string str);

    void GenFromBinString(string buf);

    void GenFromByteString(const string& buf);

    string ToString() const;

    string ToHexString() const;

    BigInt& operator= (const BigInt&);

    BigInt& operator= (int& a) { Clear(); data[0]=a; return *this;}

    BigInt& operator>> (const int&);

    BigInt& operator<< (const int&);

    int GetBitLength() const;

    int GetLength() const;

    bool TestSign() const {return sign;}

    void Clear();

    void Random(int digNum);

    void Randomsmall(int digNum);

    bool IsOdd() const {return (data[0]&1);}

    BigInt operator+ (const BigInt&) const;        
    BigInt operator- (const BigInt&) const;
    BigInt operator- (const int&) const;
    BigInt operator* (const BigInt&) const;
    BigInt operator* (const unsigned int&) const;
    BigInt operator% (const BigInt&) const;
    int operator% (const int&) const;

    BigInt operator/ (const BigInt&) const;
    BigInt operator& (const BigInt&) const;
    BigInt operator^ (const BigInt&) const;
    BigInt operator| (const BigInt&) const;  

    bool operator< (const BigInt&) const;
    bool operator> (const BigInt&) const;
    bool operator<= (const int&) const;
    bool operator== (const BigInt&) const;
    bool operator== (const int&) const;

    friend ostream& operator<< (ostream&, const BigInt&);

    static BigInt PowerMode (const BigInt& n, const BigInt& p, const BigInt& m);

    static BigInt Gcd(const BigInt& m,const BigInt& n);

    static BigInt Euc(BigInt& E,BigInt& A);

    static BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y);
private:
    static const size_t _capacity = 128 + 1;
    unsigned int data[_capacity];
    bool sign;
    void _output(ostream& out) const;

    int _hexCharToInt(char c);
};

enum _STRING_TYPE {
    BIN_STRING = 2,
    HEX_STRING = 16,
    BYTE_STRING = 10
};

#endif
