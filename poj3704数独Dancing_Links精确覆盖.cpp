#include <iostream>
#include <cstdio>
#include <cstring>
#define M (81 * 4)          //�������� 
#define N (81 * 9)          //�������� 
#define inf (1 << 30)
const int V = N * M;   //���ڵ��� 
const int head = 0;    //����hed�ڵ� 
using namespace std;

struct NODE
{
    int x, y;  //С������Ͻ����� 
    int p1, p2, p3; //��Ӧ���У� �У�С��  
};

struct NODE2
{
    int x, y, v;   
};

int nr, nc, m;
int ans, size;
int U[V], D[V], L[V], R[V] ,C[V], RR[V];  //Cָ�����head�ڵ� 
int S[M], H[M];   //S��ʾ���еĴ�С H���������������˫��״���� 

int f[10], visit[750];
int g[10][10], mc[30][10], mr[10][10], gg[10][10];  //��˼��Ӧ���� 
NODE bel[10][10]; //���ڵ�С��
NODE2 wv[730], temp[750]; //ÿ�д������˼ 
string s;

int init0()
{
    int i, j, k, h, x, y;
    for (i = 1; i <= 7; i += 3)
        for (j = 1; j <= 7; j += 3)
            for (k = i; k < i + 3; k++)
                for (h = j; h < j + 3; h++)
                    bel[k][h].x = i, bel[k][h].y = j;
    for (i = 1; i <= 9; i++)
        for (j = 1; j <= 9; j++)
        {
            bel[i][j].p1 = i, bel[i][j].p2 = j + 9;
            bel[i][j].p3 = bel[i][j].x - 1 + (bel[i][j].y - 1) / 3 + 19; 
        }
    return 1;
}

int Remove(int c)
{
	int i, j;
	L[R[c]] = L[c], R[L[c]] = R[c];
	for (i = D[c]; i != c; i = D[i])
    {
		for( j = R[i]; j != i; j=R[j])
        {
			S[C[j]]--;
			U[D[j]] = U[j];
			D[U[j]] = D[j];
		}
	}
	return 1;
}

int Resume(int c)
{
	int i, j;
	for(i = U[c]; i != c; i = U[i])
    {
		for(j = L[i]; j != i; j = L[j])
        {
			S[C[j]]++;
			U[D[j]] = D[U[j]] = j;
		}
	}
	L[R[c]] = R[L[c]] = c;
	return 1;
}

int Dance(int k)
{
    //cout << "Dance=" << k; system("pause");
	int min, i, j, c;
	if(R[head] == head)
    {
		if(k < ans) ans = k;
		for (i = 1; i <= nr; i++)
		    if (visit[i]) gg[wv[i].x][wv[i].y] = wv[i].v;
		return 1;
	}
	//cout << "end1"; system("pause");
	for(min = inf, c = 0, i = R[head]; i != head; i = R[i])
		if(S[i] < min) min = S[i], c = i;
	//cout << "CC=" << c; system("pause");
	Remove(c);
	for(i = D[c]; i != c; i = D[i])      //ö�ٿ�ѡ��ÿһ�� 
    {
		visit[RR[i]] = 1;
        for(j = R[i]; j != i; j = R[j]) Remove(C[j]);
		if (Dance(k + 1)) return 1;
		for(j = L[i]; j != i; j = L[j]) Resume(C[j]);
		visit[RR[i]] = 0;
	}
    Resume(c);
    return 0;
}

int Link(int r, int c)
{
    S[c]++, C[size] = c;
	U[size] = U[c], D[U[c]] = size, RR[size] = r;
	D[size] = c, U[c] = size;  
	if(H[r] == -1)  L[size] = R[size] = H[r] = size;
	else
    {
		L[size] = L[H[r]], R[L[H[r]]] = size;
		R[size] = H[r], L[H[r]] = size;
	}
    size++;  
    return 1;    
}


int main()
{
    int i, j, k, h, x, y;
    init0(); 
    while (cin >> s)
    {
        if (s == "end") break;
        k = 0;
        memset(mc, -1, sizeof(mc));
        memset(mr, -1, sizeof(mr));
        for (i = 1; i <= 9; i++)
            for (j = 1; j <= 9; j++)
            {
                if (s[k] == '.') g[i][j] = 0;
                else g[i][j] = s[k] - '0';
                gg[i][j] = g[i][j];
                k++;
            }
        nr = m = nc = 0;
        for (i = 1; i <= 9; i++)
            for (j = 1; j <= 9; j++)
            {
                if (g[i][j] != 0) continue;
                m++;
                mr[i][j] = m;
                memset(f, 0, sizeof(f));
                for (k = 1; k <= 9; k++) f[g[i][k]] = 1, f[g[k][j]] = 1;
                x = bel[i][j].x, y = bel[i][j].y;
                for (k = x; k < x + 3; k++)
                    for (h = y; h < y + 3; h++) f[g[k][h]] = 1;
                for (k = 1; k <= 9; k++)
                    if (f[k] == 0) nr++, wv[nr].x = i, wv[nr].y = j, wv[nr].v = k;    
            }
        //for (i = 1; i <= nr; i++)
         //   cout << wv[i].x << " " << wv[i].y << " " << wv[i].v, system("pause");
        for (i = 1; i <= 9; i++)
        {
            memset(f, 0, sizeof(f));
            for (j = 1; j <= 9; j++) f[g[i][j]] = 1;
            for (j = 1; j <= 9; j++) 
                if (f[j] == 0)
                {
                    nc++; 
                    mc[i][j] = nc; 
                    temp[nc].x = i, temp[nc].y =j;   
                }
        }
        for (i = 1; i <= 9; i++)
        {
            memset(f, 0, sizeof(f));
            for (j = 1; j <= 9; j++) f[g[j][i]] = 1;
            for (j = 1; j <= 9; j++)
                if (f[j] == 0)
                {
                    nc++;
                    mc[i + 9][j] = nc; 
                    temp[nc].x = i + 9, temp[nc].y =j;
                }
        }
        for (i = 1; i <= 9; i++)
        {
            memset(f, 0, sizeof(f));
            x = (i - 1) / 3 * 3 + 1;
            if (i % 3 == 1) y = 1;
            else if (i % 3 == 2) y = 4;
            else y = 7;
            for (k = x; k < x + 3; k++)
                for (h = y; h < y + 3; h++) f[g[k][h]] = 1;
            for (j = 1; j <= 9; j++) 
                if (f[j] == 0)
                {
                    nc++;
                    mc[i + 18][j] = nc;
                    temp[nc].x = i + 18, temp[nc].y =j;    
                } 
        }
        for (i = 0; i <= nc + m; i++)
        {
            S[i] = 0, U[i] = D[i] = i;
            L[i + 1] = i, R[i] = i + 1;
        } 
        R[nc + m] = 0, size = nc + m + 1;
        //cout << nr << " " << nc + m; system("pause");
        //cout << "Link:" << endl;
        memset(H, -1, sizeof(H));
        for (i = 1; i <= nr; i++)
        {
            Link(i, mc[bel[wv[i].x][wv[i].y].p1][wv[i].v]);
            Link(i, mc[bel[wv[i].x][wv[i].y].p2][wv[i].v]);
            Link(i, mc[bel[wv[i].x][wv[i].y].p3][wv[i].v]);
            Link(i, nc + mr[wv[i].x][wv[i].y]);
        }  
        memset(visit, 0, sizeof(visit));
        Dance(0); 
        for (i = 1; i <= 9; i++)
        {
            for (j = 1; j <= 9; j++)
                printf("%d", gg[i][j]);
        }    
        printf("\n");
    }
    system("pause");
    return 0;
}
