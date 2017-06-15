#include "Key.h"
#include "BigInt.h"
#include "PrimeGen.h"
#include "globalData.h"
#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include "utils.h"

using namespace std;

void Key::generate(int digNum) {
    this->digNum = digNum;
    srand((unsigned)time(NULL));
    
    BigInt p(GeneratePrime(digNum));
    BigInt q(GeneratePrime(digNum));

    LOGLN("Key: ��Կ����");
    BigInt t = (p - 1) * (q - 1);
    BigInt x, y, temp;
    while (1)
    {
        e.Random(digNum);
        //������T���ʵ�E
        while (!(BigInt::Gcd(e,t) == 1))
            e.Random(digNum);
        temp = BigInt::ExtendedGcd(e, t, x, y);
        temp = (e * x) % t;
        if (temp == 1)
            break;
    }
    LOGLN("    ��Կe: " << e);

    n = p * q;
    LOGLN("    ��Կn: " << n);

    d = x;
    LOGLN("    ˽Կd: " << d);

}

void Key::getPublicKey(BigInt& N, BigInt& E) const 
{
    N = this->n;
    E = this->e;
}
void Key::getPrivateKey(BigInt& N, BigInt& D) const
{
    N = this->n;
    D = this->d;
}
