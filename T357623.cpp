#include <bits/stdc++.h>
using namespace std;

const int N = 30;

class House{
public:
    long long x, y, g, w;
};

static House house[N*N+5];

void read(long long&);
void f(int);

long long x, y, np, nt, res, ans, nc, nm;
long long pw[75];

int main(){

    long long c, n, m, p, t; // c, 公寓数  n, 地图边长  m, 单次朋友个数  p, 体力上限  t, 天数
    // t, 公寓上限  p, 单次距离上限
    read(c), read(n), read(m), read(p), read(t);
    if(t == 0){
        printf("0\n");
        return 0;
    }

    pw[0] = 1;
    for(int i = 1; i <= 2*n; i++){
        pw[i] = pw[i-1]*2;
    }

    static bool map[N+5][N+5];

    int cnt = 0;
    for(int i = 1; i <= c; i++){
        long long _x, _y, g, w;
        read(_x), read(_y), read(g), read(w);
        //        if(g > m){
        //        	house[++cnt] = {_x, _y, m, w};
        //        	house[++cnt] = {_x, _y, min(m, g-m), w};
        //        }else{
        //        	house[++cnt] = {_x, _y, g, w};
        //        }
        house[++cnt] = {_x, _y, g, w};
        map[_x][_y] = true;
    }
    np = p;
    nc = c;
    nm = m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(map[i][j]){
                continue;
            }
            x = i, y = j;
            nt = t;
            res = 0;
            f(1);

        }
    }

    printf("%lld\n", ans);

}

void f(int u){
    // 去
    long long dis = abs(house[u].x-x) + abs(house[u].y-y);
    if(np >= house[u].w+pw[dis]){
        // 去一次
        long long mn = min((np - pw[dis])/house[u].w, house[u].g);
        long long num = min(mn, nm);
        res += num;
        nt--;
        ans = max(ans, res);
        if(nt && u != nc){
            f(u+1);
        }
        res -= num;
        nt++;
        // 去两次
        if(nt>1 && num < house[u].g){
            num = min(2 * num, house[u].g);
            res += num;
            nt-=2;
            ans = max(ans, res);
            if(nt && u != nc){
                f(u+1);
            }
            res -= num;
            nt+=2;
        }
    }
    // 不去
    if(u != nc){
        f(u+1);
    }
}

void read(long long &_x){
    long long s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    _x = s * w;
}