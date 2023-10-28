//
// Created by kibi on 23-9-30.
//

// 23-10-28 update
// 10-9 finish AC

#include <bits/stdc++.h>
using namespace std;

int main(){
    const int N = 600;

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

    static int times[N + 5];
    for(int i = 1; i <= m; i++){
        read(times[i]);
    }

    static int arr[N + 5][N + 5];
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            read(arr[i][j]);
        }
    }

    static int use, ans[N + 5], res[N + 5], sum;
    static bool choose[N + 5], vis[N + 5];
    for(int i = 1; i <= n; i++){
        use = 0;
        choose[i] = true;
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= n; k++){
                int now = arr[j][k];
                if(vis[now]){
                    continue;
                }
                if(!choose[now]){
                    vis[now] = true;
                    break;
                }else if(choose[now]){
                    res[++use] = now;
                    vis[now] = true;
                    if(use > times[j]){
                        choose[i] = false;
                        break;
                    }
                }
            }
            if(!choose[i]){
                break;
            }
        }
        sum += choose[i];
        if(sum == n - m){
            for(int j = use + 1, mxj = n - m, k = 1; j <= mxj; j++){
                while(!choose[k] || vis[k]){
                    k++;
                }
                res[++use] = k;
                vis[k] = true;
            }
            memcpy(ans + 1, res + 1, n * sizeof (int));
            break;
        }
        memset(vis, 0, (n + 2) * sizeof (bool));
    }

    for(int i = 1; i < n - m; i++){
        printf("%d ", ans[i]);
    }
    printf("%d", ans[n - m]);
}