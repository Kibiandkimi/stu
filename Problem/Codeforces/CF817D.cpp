//
// Created by kibi on 23-10-28.
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

        static void deal(int len, const int *data, int *res, int inf, bool (*judge)(int, int)){
            stack<pair<int, int>> stk;
            stk.emplace(-1, inf);
            for(int i = 0; i < len; i++){
                while(!judge(data[i], stk.top().second)){
                    stk.pop();
                }
                res[i] = stk.top().first;
                stk.emplace(i, data[i]);
            }
        }
    };

    auto read = Tools::read;
    auto deal = Tools::deal;

    int n;
    read(n);

    int raw_data[n];
    for(int &i : raw_data){
        read(i);
    }

    static auto judge_mx_l = [](const int now, const int pre){return now <= pre;};
    static auto judge_mn_l = [](const int now, const int pre){return now >= pre;};
    static auto judge_mx_r = [](const int now, const int pre){return now < pre;};
    static auto judge_mn_r = [](const int now, const int pre){return now > pre;};

    int mx_l[n], mx_r[n], mn_l[n], mn_r[n];
    deal(n, raw_data, mx_l, 1000001, judge_mx_l);
    deal(n, raw_data, mn_l, 0, judge_mn_l);
    reverse(raw_data, raw_data + n);
    deal(n, raw_data, mx_r, 1000001, judge_mx_r);
    deal(n, raw_data, mn_r, 0, judge_mn_r);
    reverse(raw_data, raw_data + n);
    reverse(mn_r, mn_r + n);
    reverse(mx_r, mx_r + n);

    using ll = long long;
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += ((ll)(i - mx_l[i]) * (n - mx_r[i] - i - 1) - (ll)(i - mn_l[i]) * (n - mn_r[i] - i - 1)) * raw_data[i];
    }
    printf("%lld\n", ans);
}