#include <iostream>
#include <cstdio>
#include <cstring>
#define NN 30
#define INF 0x3fffffff
using namespace std;

int idx, S;// SΪ��Ҫ���ƶȵ���һ��
int k, mst;// k��ʾk�����ƣ�mstΪ���Ľ��
int pre[NN];
int mark[NN];
int dis[NN]; 
int vis[NN];
char str[NN][NN];
int map[NN][NN];
int best[NN]; // ��������Ȩֵ�ߵ��յ�
int edg[NN][NN];// edg[i][j] = 1 ��ʾ��[i,j]������������
int father[NN];// �������еĸ��ڵ�

int find(char s[])
{
    int i;
    for (i = 0; i < idx; i++)
    {
        if (strcmp(str[i], s) == 0) return i;
    }
     return -1;
 }

int dfs(int cur) // ���������и��� 
{
    int i;
    for (i = 0; i < idx; i++)
    {
        if (edg[i][cur] && mark[i])
        {
            father[i] = cur;
            mark[i] = 0;
            dfs(i);
        }
    }
    return 1;
}

int prim(int s) // ����С������ 
{
    int i, key, Min;
    int sum = 0;
    memset(pre, 0, sizeof(pre));
    for (i = 0; i < idx; i++)
    {
         dis[i] = map[s][i];
         pre[i] = s;
     }
     memset(mark, 0, sizeof(mark));
     mark[s] = 1;
     vis[s] = 1;
     while(1)
     {
         Min = INF;
         key = -1;
          for (i = 0; i < idx; i++)
          {
              if (!vis[i] && !mark[i] && dis[i] < Min)
              {
                 key = i;
                 Min = dis[i];
              }
          }
          if (key == -1) break;
          mark[key] = 1; 
          vis[key] = 1;
          edg[pre[key]][key] = edg[key][pre[key]] = 1;
          sum += dis[key];
          for (i = 0; i < idx; i++)
          {
              if (!vis[i] && !mark[i] && dis[i] > map[key][i])
              {
                 dis[i] = map[key][i];
                 pre[i] = key;
              }
          }
       }
       Min = INF;
       int root = -1; // ����
       for (i = 0; i < idx; i++)
       {
           if (mark[i] && map[i][S] < Min)
           {
              Min = map[i][S];
              root = i;
           }
       }
       // �����и��� 
       mark[root] = 0;
       dfs(root);
       father[root] = S;
       return sum + Min;
}
  
int Best(int x) // ���x��S·���ϵ����Ȩֵ��
{
      int tmp;
      if (father[x] == S) return -1;
      if (best[x] != -1) return best[x];
      tmp = Best(father[x]);
      if (tmp != -1 && map[tmp][father[tmp]] > map[father[x]][x])
          best[x] = tmp;
     else 
         best[x] = x;
      return best[x];
}
  
int Solve()
{
    int i, j;
    memset(vis, 0, sizeof(vis));
    vis[S] = 1;
    int m = 0;// ��֧���� 
    mst = 0;// ��С�������� 
    memset(father, -1, sizeof(father));
    memset(edg, 0, sizeof(edg));
    for (i = 0; i < idx; i++) // �����m����������
    {
         if (!vis[i])
         {
            m++;
            mst += prim(i);
         }
     }
    /*    for (i = 0; i < idx; i++){
         printf("%d----%d %d\n", father[i], i, map[i][father[i]]);
        }�������ڵ��Դ���
    */
    //cout << mst;system("pause");
     int minadd, ax, bx,tmp;
     int change; // ��·��Ȩֵ���ıߣ����ڽ���
     for (i = m + 1; i <= k && i < idx; i++)
     {
         // ����m���������õ�m+1����������������k����������
         memset(best, -1, sizeof(best));
         for (j = 0; j < idx; j++)
         {
             if (best[j] == -1 && father[j] != S){
                Best(j);
             }
         }
         minadd = INF; // �����ߵ���С��ֵ 
         for (j = 0; j < idx; j++) // ���������ٱ�
         {
             if (map[S][j] != INF && father[j] != S){
                ax = best[j];
                bx = father[ax];
                tmp = map[S][j] - map[ax][bx];
                if (tmp < minadd){
                   minadd = tmp;
                   change = j;
                }
             }
         }
         if (minadd >= 0) break;//���ڶ���������k�����ƣ����k���ƣ��Ͳ���break��
         mst += minadd;
         ax = best[change];
         bx = father[ax];
         map[ax][bx] = map[bx][ax] = INF;
         father[ax] = bx = S;// �ı�������������axֱ��ָ��Դ��S
         map[ax][bx] = map[bx][ax] = map[change][S];
         map[S][change] = map[change][S] = INF;
     }
     return 1;
}

int main()
{
    int i, j, n, x, y, d;
    char s1[NN], s2[NN];
    scanf("%d", &n);
    for (i = 0; i <= NN - 2; i++)
    {
         for (j = 0; j <= NN - 2; j++)
             map[i][j] = INF;
     }
     idx = 1;
     strcpy(str[0], "Park");
     while(n--)
     {
        scanf("%s%s%d", s1, s2, &d);
        x = find(s1);
        if (x == -1)
        {
           strcpy(str[idx++], s1);
           x = idx - 1;
        }
        y = find(s2);
        if (y == -1)
        {
           strcpy(str[idx++], s2);
           y = idx - 1;
        }
        if (d < map[x][y])
        {
           map[x][y] = d;
           map[y][x] = d;
        }
     }
     scanf("%d", &k);
     S = 0;
     Solve();
     printf("Total miles driven: %d\n", mst);
     system("pause");
     return 0;
 }
 
