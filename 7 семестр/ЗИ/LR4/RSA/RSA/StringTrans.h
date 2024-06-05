#ifndef STRINGTRANS_H_
#define STRINGTRANS_H_

#include "BigInt.h"
#include <vector>
using namespace std;

class StringTrans : public vector<BigInt> {
private:
    void split(const string&);
    int BitLen;

public:
    StringTrans(const string& a, int b);

    string toString();
    string toHexString();
    
    void push_back(const BigInt&);
    StringTrans& operator+= (const BigInt&);
    StringTrans& operator+= (const StringTrans&);
};

#endif
