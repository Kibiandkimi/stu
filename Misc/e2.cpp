//
// Created by kibi on 2021/11/7.
//
#include <cstdio>
using namespace std;

int n,qa,qb,ans;
long long t[600005];
struct rd{
    int y;
    int nxt;
};
rd a[1000005];
rd b[1000005];
long long d1[600005];
long long d2[600005];
int ha[600005];
int hb[600005];
int f[600005];
void addd1(int ax,int ay){
    a[++qa].y=ay;
    a[qa].nxt=ha[ax];
    ha[ax]=qa;
}
void addd2(int ax,int ay){
    b[++qb].y=ay;
    b[qb].nxt=hb[ax];
    hb[ax]=qb;
}
void dfsa(int k,int fa){
    int u,i;
    for(i=ha[k];i!=0;i=a[i].nxt){
        u=a[i].y;
        if(u==fa) continue;
        d1[u]=d1[k]+1+t[k];
        f[u]=k;
        dfsa(u,k);
    }
}
void dfsb(int k,int fa){
    int u,i,flg=0;
    for(i=hb[k];i!=0;i=b[i].nxt){
        u=b[i].y;
        if(u==fa) continue;
        flg=1;
        d2[u]=d2[k]+1;
        if((d1[u]<=d2[u]&&d2[u]<=d1[u]+t[u])||(d1[k]==d2[u]&&f[k]==u)) continue;
        dfsb(u,k);
    }
    if(!flg) ans++;
}
int main(){
    scanf("%d",&n);
    int i,ax,ay;
    for(i=1;i<=n;i++) scanf("%lld",&t[i]);
    for(i=1;i<n;i++){
        scanf("%d%d",&ax,&ay);
        addd1(ax,ay);
        addd1(ay,ax);
    }
    for(i=1;i<n;i++) {
        scanf("%d%d",&ax,&ay);
        addd2(ax,ay);
        addd2(ay,ax);
    }
    dfsa(1,0);
    dfsb(n+1,0);
    printf("%d\n",ans);
    return 0;
}
/*
5
2 0 1000000000 2 1000000000
2 1
1 3
4 2
4 5
6 5
4 6
3 5
5 2

10
2 2 1000000000 6 3 1000000000 8 1000000000 1000000000 1000000000
2 1
2 3
4 1
5 4
6 1
7 1
8 1
9 5
7 10
9 10
9 11
8 11
5 7
9 6
5 11
4 3
3 11
2 10
 */