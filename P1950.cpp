//
// Created by kibi on 23-11-3.
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

        static void read_(bool &x){
            static auto judge = [](int c){return c == '*' || c == '.';};
            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            x = (c == '.');
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    class Node{
    public:
        bool flag;
        int l, h;
    };

    Node data[n][m];
    for(auto &i : data){
        for(auto &j : i){
            Tools::read_(j.flag);
        }
    }

    for(auto &i : data){
        i[0].l = i[0].flag;
        for(int j = 1; j < m; j++){
            i[j].l = (i[j].flag ? i[j - 1].l + 1 : 0);
        }
    }

    using ll = long long;

    ll ans = 0;
    for(int j = 0; j < m; j++){
        data[0][j].h = data[0][j].flag;
        ll sum = data[0][j].h * data[0][j].l;
        stack<pair<int, int>> stk;
        if(sum){
            stk.emplace(1, data[0][j].l);
        }
        ans += sum;
        for(int i = 1; i < n; i++){
            data[i][j].h = (data[i][j].flag ? data[i - 1][j].h + 1 : 0);
            if(!data[i][j].h){
                sum = 0;
                while(!stk.empty()){
                    stk.pop();
                }
            }else{
                int num = 1;
                while(!stk.empty() && stk.top().second > data[i][j].l){
                    num += stk.top().first;
                    sum -= (ll)stk.top().first * stk.top().second;
                    stk.pop();
                }
                stk.emplace(num, data[i][j].l);
                sum += (ll)num * data[i][j].l;
            }
            ans += sum;
        }
    }

    printf("%lld\n", ans);
}