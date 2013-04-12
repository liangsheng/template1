#include<iostream>   
#include<vector>   
using namespace std;   
  
const int MAX=10001;   
int f[MAX];   
int r[MAX];   
int indegree[MAX];//����ÿ���ڵ�����   
int visit[MAX];   
vector<int> tree[MAX],Qes[MAX];   
int ancestor[MAX];   
  
  
void init(int n)   
{   
    for(int i=1;i<=n;i++)   
    {   
  
        r[i]=1;   
        f[i]=i;   
        indegree[i]=0;   
        visit[i]=0;   
        ancestor[i]=0;   
        tree[i].clear();   
        Qes[i].clear();   
    }   
  
}   
  
int find(int n)   
{   
    if(f[n]==n)   
        return n;   
    else  
        f[n]=find(f[n]);   
    return f[n];   
}//���Һ�������ѹ��·��   
  
int Union(int x,int y)   
{   
    int a=find(x);   
    int b=find(y);   
    if(a==b)   
        return 0;   
    //��ȵĻ�,x��y�ϲ�   
    else if(r[a]<=r[b])   
    {   
        f[a]=b;   
        r[b]+=r[a];   
    }   
    else  
    {   
        f[b]=a;   
        r[a]+=r[b];   
    }   
    return 1;   
  
}//�ϲ��������������ͬһ��֧�򷵻�0���ɹ��ϲ�����1   
  
  
void LCA(int u)   
{   
    ancestor[u]=u;   
    int size = tree[u].size();   
    for(int i=0;i<size;i++)   
    {   
        LCA(tree[u][i]);   
        Union(u,tree[u][i]);   
        ancestor[find(u)]=u;   
    }   
    visit[u]=1;   
    size = Qes[u].size();   
    for(int i=0;i<size;i++)   
    {   
        //����Ѿ�����������ڵ�,�Ϳ��Է��ؽ����.   
        if(visit[Qes[u][i]]==1)   
        {   
            cout<<ancestor[find(Qes[u][i])]<<endl;   
            return;   
        }   
    }   
}   
  
  
int main()   
{   
    int cnt;   
    int n;   
    cin>>cnt;   
    while(cnt--)   
    {   
        cin>>n;;   
        init(n);   
        int s,t;   
        for(int i=1;i<n;i++)   
        {   
            cin>>s>>t;   
            tree[s].push_back(t);   
            indegree[t]++;   
        }   
        //��������������ѯ��   
        cin>>s>>t;   
        //�൱��ѯ������   
        Qes[s].push_back(t);   
        Qes[t].push_back(s);   
        for(int i=1;i<=n;i++)   
        {   
            //Ѱ�Ҹ��ڵ�   
            if(indegree[i]==0)   
            {   
                LCA(i);   
                break;   
            }   
        }   
    }
    system("pause");   
    return 0;   
}  
