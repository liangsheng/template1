/*
������һ��Stirling�����������ģ������ֵ�ǰ���n��Ԫ�صļ��Ϸ���k�������еķ�����Ŀ��
�������ƹ�ʽΪ��
����S(n,0) = 0, S(1,1) = 1.
����S(n+1,k) = S(n,k-1) + nS(n,k)��
�����ڶ���Stirling���ǰѰ���n��Ԫ�صļ��ϻ���Ϊ����k���ǿ��Ӽ��ķ�������Ŀ��
�������ƹ�ʽΪ��
����S(n,k)=0; (n<k||k=0)
����S(n,n) = S(n,1) = 1,
����S(n,k) = S(n-1,k-1) + kS(n-1,k).
������n�����������������k���ޱ�ŵĺ�����( n>=k>=1���Һ��Ӳ�����Ϊ��)�ķ���������stirling��.(���� n ��Ԫ�صļ��ϻ���Ϊ k �����ϵ������)
�������ƹ�ʽ:
����S(n,0) = 0
����S(n,1) = 1 (k = 1)
����S(n,n) = 1
����S(n,k) = 0 (k > n)
����S(n,k) = S(n-1,k-1)+k*S(n-1,k) (n >= k >= 2)
��������������n����ͬ���򣬷ֱ���b1,b2,...,bn��ʾ������ȡ��һ����bn��bn�ķŷ����������֣�
����1.bn��ռһ�����ӣ���ôʣ�µ���ֻ�ܷ���k-1�������������ΪS��n-1,k-1);
����2.bn������ռһ�����ӣ���ô���Խ�b1,b2,...,bn-1��n-1�������k�������Ȼ��bn��������һ�������У�������Ϊk*S(n-1,k).
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define inf (1 << 30)
#define N 21
const double eps = 1e-12;
const double pi = acos(-1.0);
using namespace std;

__int64 ans[N][N], f[N];

int main()
{
    int i , j, n, a, b;
    __int64 sum;
    memset(ans, 0, sizeof(ans));
    memset(f, 0, sizeof(f));
    ans[1][1] = 1;
    for (i = 2; i <= 20; i++)
    {
        for (j = 1; j <= i; j++)
            ans[i][j] = ans[i - 1][j - 1] + (i - 1) * ans[i - 1][j];
    }
    f[0] = 1;
    for (i = 1; i <= 20; i++) f[i] = f[i - 1] * i;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d%d", &a, &b);
        sum = 0;
        for (i = 1; i <= b; i++)
            sum += ans[a][i] - ans[a - 1][i - 1];
        printf("%.4lf\n", double(sum) / double(f[a]));
    }
    system("pause");
    return 0;
}
