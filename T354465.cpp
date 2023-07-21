//
// Created by kibi on 23-7-21.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100000, K = 224;

void read(int&);

int main(){

    class People{
    public:
        int w, s, p; // p(2 -> 3 -> 1)
        static bool cmp(People a, People b){
            return a.w == b.w ? a.p != 1 && (a.p == 2 || b.p != 2) : a.w < b.w;
        }
    };

    int n, k;
    static long long f[2][K + 5][K + 5];
    People people[N + 5];

    memset(f, 0x3f, sizeof f);

    const long long Inf = f[0][0][0];

    read(n), read(k);

    if(2 * k > n){
        printf("-1\n");
        return 0;
    }

    for(int i = 1; i <= n; i++){
        read(people[i].w), read(people[i].s), read(people[i].p);
    }

    sort(people+1, people+1+n, People::cmp);

    f[1%2][0][0] = 0;

    for(int i = 1; i <= n; i++){
        //        memcpy(f[(i%2)^1], f[(i%2)], sizeof f[(i%2)]); // memcpy还更慢。。。 当然是因为特殊原因
        for(int j = 0; j <= k; j++){
            for(int _k = 0; _k <= k; _k++){
                f[(i%2)^1][j][_k] = f[(i%2)][j][_k];
            }
        }
        if(people[i].p != 1){
            for(int j = 0; j <= k; j++){
                for(int _k = 0; _k < k; _k++){
                    f[(i%2)^1][j][_k+1] = min(f[(i%2)^1][j][_k+1], f[(i%2)][j][_k] + people[i].s);
                }
            }
        }
        if(people[i].p != 2){
            for(int j = 0; j < k; j++){
                for(int _k = 1; _k <= k; _k++){
                    f[(i%2)^1][j+1][_k-1] = min(f[(i%2)^1][j+1][_k-1], f[i%2][j][_k] + people[i].s);
                }
            }
        }
    }
    if(f[(n%2)^1][k][0] == Inf){
        printf("-1\n");
    }else{
        printf("%lld\n", f[(n%2)^1][k][0]);
    }

}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c  = getchar();
    }
    x = s * w;
}