//
// Created by kibi on 23-11-1.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;
    static const int Mod = 998244353;

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

        static void read_(vector<bool> &x){
            static auto judge = [](int c){return c == '0' || c == '1';};
            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            int cnt = 0;
            while(judge(c)){
                x[cnt++] = c == '1';
                c = getchar();
            }
            x.shrink_to_fit();
        }

        static void add(int &x, int y){
            x = (x + y) % Mod;
        }

        static void sub(int &x, int y){
            x = (int)((ll)x * y % Mod);
        }
    };

    auto read = Tools::read;
    auto add = Tools::add;
    auto sub = Tools::sub;

    int T, id;
    read(T), read(id);

    while(T--){
        int n, m, s1, s2;
        read(n), read(m), read(s1), read(s2);

        vector<vector<bool>> mp(n, vector<bool>(m, false));
        for(auto &i : mp){
            Tools::read_(i);
        }

        int f[n][m];
        for(int i = 0; i < n; i++){
            f[i][m - 1] = 0;
            for(int j = m - 2; j >= 0; j--){
                if(mp[i][j]){
                    f[i][j] = -1;
                }else if(!mp[i][j + 1]){
                    f[i][j] = f[i][j + 1] + 1;
                }else{
                    f[i][j] = 0;
                }
            }
        }

        int l, lf;
        int ans_c = 0, ans_f = 0;
        for(int j = 0; j < m - 1; j++){
            l = lf = 0;
            for(int i = 0; i < n; i++){
                if(f[i][j] == -1){
                    l = lf = 0;
                    continue;
                }
                add(ans_c, (int)((ll)f[i][j] * l % Mod));
                add(ans_f, lf);
                add(lf, (int)((ll)f[i][j] * l));
                if(i) {
                    add(l, max(0, f[i - 1][j]));
                }
            }
        }

        sub(ans_c, s1);
        sub(ans_f, s2);

        printf("%d %d\n", ans_c, ans_f);
    }
}