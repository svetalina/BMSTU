#include "StringTrans.h"
#include <string>
#include <vector>
#include "BigInt.h"

using namespace std;

StringTrans::StringTrans(const string& a, int b) {
    this->BitLen = b;
    this->split(a);
}

void StringTrans::split(const string& msg) {
    int n = 0,i = 0,j = 0;
    int StrLen = BitLen / 8;
    (*this).clear();
    const char* msg_c = msg.c_str();
    do
    {
        char seg_c[255];
        for (i = n * StrLen,j = 0;i < msg.length() && i < (n + 1) * StrLen;i++,j++)
            seg_c[j] = msg_c[i];
        seg_c[j] = '\0';
        string segment(seg_c);
        vector<BigInt>::push_back(BigInt(segment, 10));
        n++;
    }
    while (n * StrLen < msg.length());
}

string StringTrans::toHexString() {
    size_t len = this->size();
    string res, tmp;
    for (int i = 0; i < len; i++) {
        tmp = (*this)[i].ToHexString();
        res += tmp;
    }
    return res;
}

string StringTrans::toString() {
    size_t len = this->size();
    string res, tmp;
    for (int i = 0; i < len; i++) {
        tmp = (*this)[i].ToString();
        res += tmp;
    }
    return res;
}

void StringTrans::push_back(const BigInt& bigInt) {
    vector<BigInt>::push_back(bigInt);
}

StringTrans& StringTrans::operator+= (const BigInt& bigInt) {
    vector<BigInt>::push_back(bigInt);
    return *this;
}

StringTrans& StringTrans::operator+= (const StringTrans& st) {
    for (const auto & itr : st)
        vector<BigInt>::push_back(itr);
    return *this;
}
