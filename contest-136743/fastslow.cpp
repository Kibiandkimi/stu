//
// Created by kibi on 23-10-3.
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

    freopen("fastslow.in", "r", stdin);
    freopen("fastslow.out", "w", stdout);

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    int raw_data[n];
    for(int i = 0; i < n; i++){
        read(raw_data[i]);
    }

    int pre[n], suc[n];
    while(m--){
        int x, y;
        read(x), read(y);
        pre[0] = (raw_data[0] == x);
        suc[n - 1] = (raw_data[n - 1] == y);
        for(int i = 1; i < n; i++){
            pre[i] = pre[i - 1] + (raw_data[i] == x);
            suc[n - i - 1] = suc[n - i] + (raw_data[n - i - 1] == y);
        }
        long long ans = 0;
        for(int i = 1; i < n; i++){
            ans = max(ans, (long long)pre[i - 1] * suc[i]);
        }

        printf("%lld\n", ans);
    }

    fclose(stdin);
    fclose(stdout);

}