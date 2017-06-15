#include "PrimeGen.h"
#include "BigInt.h"
#include "utils.h"

/**
 * ����һ����������,��֤����Ϊ����,�Ҳ��ܱ�С��5000����������
 *
 * @param [out] n
 * @param [in] digNum λ��
 */
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

/**
 * Rabin-Miller ���Բ���
 *
 * @param n
 * @param digNum λ��
 * @return true: ������, false: ��������
 */
bool RabinMiller(const BigInt& n, int digNum)
{
    BigInt r, a, y;
    unsigned int s, j;
    r = n - 1;
    s = 0;

    //�ҵ���N-1=2^S*R��S��R,RΪ����
    while (!r.IsOdd())
    {
        s++;
        r >> 1;
    }

    //����һ��С��N-1�ļ�������
    a.Randomsmall(digNum);

    y = BigInt::PowerMode(a, r, n);

    //���J=2��J<S��
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

//����һ������
BigInt GeneratePrime(int digNum)
{
    BigInt n;
    int i = 0;
    LOG("GeneratePrime �������� ");
    while (i < 5)
    {
        //����һ����������
        GenPrime(n, digNum);
        i = 0;
        //��������ROBINMILLER����,����ȫ��ͨ���������ϸ�
        //���������ϸ��ʴ�99.9%
        for ( ; i < 5; i++)
        {
            if (!RabinMiller(n, digNum))
            {
                LOG(".");
                break;
            }
        }
    }
    LOGLN("\n    " << n);
    return n;
}
