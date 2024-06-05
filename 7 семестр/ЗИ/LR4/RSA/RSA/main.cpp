#include <iostream>
#include <fstream>
#include <sstream>
#include "md5.h"
#include "rsa.h"

using namespace::std;

int main(int argc, const char * argv[]) {
    std::ifstream inFile;
    inFile.open("src.txt");

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string str = strStream.str();

    string hash = md5(str);

    RSA *rsa = new RSA(512);
    BigInt N, E;
    rsa->getPublicKey(N, E);

    StringTrans st(hash, N.GetBitLength() - 17);
    cout << "MD5 hash before encrypting: " << endl;
    cout << st.toString() << endl;

    RSA::encrypt(st, N, E);
    cout << "MD5 hash after encrypting: " << endl;
    cout << st.toHexString() << endl;

    rsa->decrypt(st);
    cout << "MD5 hash after decrypting: " << endl;
    cout << st.toString() << endl;

    return 0;
}
