#include <bits/stdc++.h>
using namespace std;

const int N = 30;

class House{
public:
    long long x, y, g, w;
};

static House house[N*N+5];

void read(long long&);

bool cmp(long long a, long long b){
    return a > b;
}

long long ans;
long long pw[75];

int main(){

    long long c, n, m, p, t;
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

    for(int i = 1; i <= c; i++){
        long long _x, _y, g, w;
        read(_x), read(_y), read(g), read(w);
        house[i] = {_x, _y, g, w};
        map[_x][_y] = true;
    }

    long long cnt;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(map[i][j]){
                continue;
            }
            static long long val[N*N*2+5];
            cnt = 0;
            for(int k = 1; k <= c; k++){
                static long long dis;
                dis = abs(house[k].x-i) + abs(house[k].y-j);
                if(p >= house[k].w + pw[dis]){
                    static long long mn;
                    mn = min((p - pw[dis])/house[k].w, house[k].g);
                    static long long num;
                    num = min(mn, m);
                    val[++cnt] = num;
                    if(num < house[k].g){
                        num = min(num, house[k].g - num);
                        val[++cnt] = num;
                    }
                }
            }
            if(cnt){
                static long long res;
                res = 0;
                sort(val+1, val+1+cnt, cmp);
                long long mxk = min(t, cnt);
                for(int k = 1; k <= mxk; k++){
                    res += val[k];
                }
                ans = max(ans, res);
            }
        }
    }

    printf("%lld\n", ans);

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