/*
lower_bound(val): ���������е�һ��ֵ�����ڻ���ڡ�val��Ԫ�ص�iteratorλ�á�
upper_bound(val): ���������е�һ��ֵ�����ڡ�val��Ԫ�ص�iteratorλ�á�
Lower_bound�����÷������������������Ҫ���ҹؼ��ֵ��½�(��һ��������) ����
Upper_bound�����÷������������������Ҫ���ҹؼ��ֵ��Ͻ�(��һ��������) ����
���磺map���Ѿ�������1��2��3��4�Ļ������lower_bound(2)�Ļ������ص�2��
��upper_bound��2���Ļ������صľ���3
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#define N 10005
using namespace std;

int n, m;

int main()
{
    int i, j, x, y, t1, t2;
    vector<int> start, end;
    while (scanf("%d%d", &n, &m) != EOF && n != 0 && m != 0)
    {
        start.clear(), end.clear();
        for (i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d", &t1, &t2, &x, &y);
            y = x + y;
            start.push_back(x);
            end.push_back(y);
        }
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());
        for (i = 1; i <= m; i++)
        {
            scanf("%d%d", &x, &y);
            y = x + y;
            t1 = start.end() - lower_bound(start.begin(), start.end(), y);
            t2 = upper_bound(end.begin(), end.end(), x) - end.begin();
            printf("%d\n", n - t1 - t2);
        }
    }
    system("pause");
    return 0;
}
