//
// Created by kibi on 23-9-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    int t, k;
    read(t), read(k);

    static int c[2005][2005];
    static long long s[2005][2005];

    c[0][0] = c[1][0] = c[1][1] = 1;
    for(int i = 2; i <= 2000; i++){
        c[i][0] = 1;
        for(int j = 1; j <= 2000; j++){
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % k;
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
            if(!c[i][j]){
                s[i][j]++;
            }
        }
        s[i][i + 1] = s[i][i];
    }

    while(t--){
        int n, m;
        read(n), read(m);

        printf("%lld\n", m > n ? s[n][n] : s[n][m]);
    }
}