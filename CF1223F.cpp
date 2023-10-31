//
// Created by kibi on 23-10-31.
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

    int T;
    read(T);

    while(T--) {
        int n;
        read(n);

        static vector<int> str;
        str.resize(n);
        for(auto &i : str){
            read(i);
        }

        int pre[str.size()], f[str.size()];
        for (int i = 0; i < str.size(); i++) {
            pre[i] = i - 1;
        }

        long long cnt = 0;

        int vis[str.size() + 1];
        memset(vis, -1, sizeof vis);

        vis[str[0]] = 0;
        for (int i = 1; i < str.size(); i++) {
            if(vis[str[i]] >= 0) {
                while (str[pre[i]] != str[i]) {
                    pre[i] = pre[pre[i]] - 1;
                    cnt++;
                    if (pre[i] < 0){
                        break;
                    }
                    if (pre[i] < vis[str[i]] && str[pre[i]] != str[i]) {
                        pre[i] = -1;
                        break;
                    }
                }
            }else{
                pre[i] = -1;
                vis[str[i]] = i;
            }
        }

        long long ans = 0;
        for (int i = 0; i < str.size(); i++) {
            f[i] = 0;
            if (pre[i] > 0) {
                f[i] = f[pre[i] - 1] + 1;
                ans += f[i];
            } else if (pre[i] == 0) {
                f[i] = 1;
                ans += f[i];
            }
        }

        printf("%lld\n", ans);
    }
}