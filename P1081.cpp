//
// Created by kibi on 2021/10/11.
//
#include <bits/stdc++.h>
using namespace std;
struct city{
    int h, d;
    int pre, nxt;
}a[100005];
int pos[100005], ga[100005], gb[100005];
int f[25][100005][2];
long long da[25][100005][2], db[25][100005][2], la, lb;
int n, m, t;
bool cmp(city a1, city a2){
    return a1.h < a2.h;
}
int pd(int x, int ta, int tb){
    if(!ta){
        return a[tb].d;
    }
    if(!tb){
        return a[ta].d;
    }
    if(a[x].h-a[ta].h<=a[tb].h-a[x].h){
        return a[ta].d;
    }else{
        return a[tb].d;
    }
}
void del(int x){
    if(a[x].pre){
        a[a[x].pre].nxt = a[x].nxt;
    }
    if(a[x].nxt){
        a[a[x].nxt].pre = a[x].pre;
    }
}
void calc(int s, long long x){
    la = lb = 0;
    int k = 0;
    for(int i = t; i >= 0; i--){
        if(f[i][s][k] && da[i][s][k]+db[i][s][k]<=x){
            x -= da[i][s][k] + db[i][s][k];
            la += da[i][s][k];
            lb += db[i][s][k];
            if(!i){
                k ^= 1;
            }
            s = f[i][s][k];
        }
    }
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i].h);
        a[i].d = i;
    }
    sort(a+1, a+1+n, cmp);
    for(int i = 1; i <= n; i++){
        pos[a[i].d] = i;
        a[i].pre = i-1;
        a[i].nxt = i+1;
    }
    a[1].pre = a[n].nxt = 0;
    for(int i = 1; i < n; i++){
        int p = pos[i], p1 = a[p].pre, p2 = a[p].nxt;
        if(p1&&(a[p].h-a[p1].h<=a[p2].h-a[p].h||!p2)){
            gb[i] = a[p1].d, ga[i] = pd(p,  a[p1].pre, p2);
        }else{
            gb[i] = a[p2].d, ga[i] = pd(p, p1, a[p2].nxt);
        }
        del(p);
    }
    for(int i = 1; i <= n; i++){
        if(ga[i]){
            f[0][i][0] = ga[i];
            da[0][i][0] = fabs(a[pos[i]].h - a[pos[ga[i]]].h);
            db[0][i][0] = 0;
        }
        if(gb[i]){
            f[0][i][1] = gb[i];
            da[0][i][1] = 0;
            db[0][i][1] = fabs(a[pos[i]].h - a[pos[gb[i]]].h);
        }
    }
    t = (int)(log(1.0*n)/log(2)+1);
    for(int i = 1; i <= t; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 0; k <= 1; k++){
                int l = (i==1)?k^1:k;
                if(f[i-1][j][k]){
                    f[i][j][k] = f[i-1][f[i-1][j][k]][l];
                }
                if(f[i][j][k]){
                    da[i][j][k] = da[i-1][j][k] + da[i-1][f[i-1][j][k]][l];
                    db[i][j][k] = db[i-1][j][k] + db[i-1][f[i-1][j][k]][l];
                }
            }
        }
    }
    long long x;
    int s;
    scanf("%lld", &x);
    int p = 0;
    long long sa = 1, sb = 0;
    for(int i  = 1; i <= n; i++){
        calc(i, x);
        if(!lb){
            la = 1;
        }
        if(la*sb<lb*sa||(la*sb==lb*sa&&a[pos[i]].h>a[pos[p]].h)){
            sa = la, sb = lb, p = i;
        }
    }
    printf("%d\n", p);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        scanf("%d %lld", &s, &x);
        calc(s,x);
        printf("%lld %lld\n", la, lb);
    }
}