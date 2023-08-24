//
// Created by kibi on 2022/8/18.
//
//我咋没看出状压
#include <bits/stdc++.h>
using namespace std;
int n, m, tot, ans, res;
int a[25];
bool f[2210], vis[2210];

void d(){
    memset(f, 0, sizeof f);
    f[0] = true;
    ans = 0, tot = 0;
    for(int i = 1; i <= n; i++){
        if(vis[i]){
            continue;
        }
        for(int j = tot; j >= 0; j--){
            if(f[j]&&!f[j+a[i]]){
                f[j+a[i]] = true;
                ans++;
            }
        }
        tot += a[i];
    }
    res = max(res, ans);
}

void dfs(int u, int now){
    if(now > m){
        return ;
    }
    if(u == n){
        if(now == m){
            d();
        }
        return ;
    }
    dfs(u+1, now);
    vis[u] = true;
    dfs(u+1, now+1);
    vis[u] = false;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    dfs(1, 0);
    printf("%d", res);
}

// 2023/8/24

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){

    static const int N = 20, MaxV = 20 * 100;

    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = getchar();
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
            x = s * w;
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static int raw_data[N + 5], maxV, minV = 101;
    for(int i = 1; i <= n; i++){
        read(raw_data[i]);
        maxV += raw_data[i];
        minV = min(minV, raw_data[i]);
    }

    long long ans = 0;
    static bool vis[N + 5];

    auto f = [&](auto && f, int dep, int now) -> void{
        if(dep < m){
            for(int i = now; i <= n; i++){
                vis[i] = true;
                f(f, dep + 1, i + 1);
                vis[i] = false;
            }
        }else{
            static bool d[MaxV + 5][N + 5] = {true};
            static long long res;
            res = 0;
            for(int j = 1; j <= n; j++){
                for(int i = 0; i <= maxV; i++){
                    if(!vis[j] && raw_data[j] <= i && d[i - raw_data[j]][j - 1]){
                        d[i][j] = true;
                    }else{
                        d[i][j] = d[i][j - 1];
                    }
                }
            }
            for(int i = minV; i <= maxV; i++){
                d[i][n] ? res++ : res;
            }
            for(int j = 1; j <= n; j++){
                for(int i = minV; i <= maxV; i++){
                    d[i][j] = false;
                }
            }
            ans = max(ans, res);
        }
    };

    f(f, 0, 1);

    printf("%lld\n", ans);
}
 *
 * */