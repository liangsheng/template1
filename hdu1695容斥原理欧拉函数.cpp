#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define eps 1e-8
#define PI 3.14159265358979
#define inf 0x3fffffff
#define L 100005

long long e[L];
int prime[L][20], num[L];    //prime[i][j]����i�ĵ�j�������ӣ�num[i]����i�������Ӹ���

void Euler ()
{
    int i, j;
    for (i = 1; i < L; i++)    //��ʼ��
        e[i] = i;
    for (i = 2; i < L; i++)
    {
        if (e[i] == i)    //ֻ�������ſɽ���
        {
            e[i] = i - 1;
            for (j = i << 1; j < L; j += i)    //��ŷ����ͬʱ��������
                e[j] = e[j] - e[j] / i, prime[j][num[j]++] = i;
        }
    }
    for (i = 2; i < L; i++)    //�������
        e[i] += e[i-1];
}

int dfs (int x, int b, int n)    //��[1,b]���ж��ٸ���n�ǻ���
{
    if (!b)
        return 0;
    int ans = 0, i;
    for (i = x; i < num[n]; i++)
        ans += b/prime[n][i] - dfs (i+1, b/prime[n][i], n);    //�ݳ�ԭ��
    return ans;
}

int main()
{
    int t, a, b, c, d, k, cc = 1, i;
    long long res;
    memset (num, 0, sizeof(num));
    Euler ();
    scanf ("%d", &t);
    while (t--)
    {
        scanf ("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf ("Case %d: ", cc++);
        if (!k)    //k==0������Ϊ��ĸ������
        {
            puts ("0");
            continue;
        }
        b /= k, d /= k;    //�����ת����ת������gcd=1�Ķ���
        if (d < b)
            d ^= b, b ^= d, d ^= b;
        res = e[b];    //[1,b]��[1,b]��gcdΪ1�Ķ���
        for (i = b + 1; i <= d; i++)    //��[b+1,d]��[1,d]�Ļ��ʶ���
            res += b - dfs (0, b, i);    //�Ѿ��޷������������ˣ��ҷ�������
        printf ("%I64d\n", res);
    }
    return 0;
}
