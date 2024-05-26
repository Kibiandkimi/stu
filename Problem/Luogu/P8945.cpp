//
// Created by kibi on 23-10-31.
//

// TODO first to understand nxt to finish

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

    int n, k;
    read(n), read(k);

    int raw_data[n];
    for(auto &i : raw_data){
        read(i);
    }

    vector<int> pos;
    for(int i = 0; i < n; i++){
        if(raw_data[i] == 0){
            pos.emplace_back(i);
        }
    }

    int l[n], now = 0;
    for(int i = 0; i < n; i++){
        l[i] = now;
        if(raw_data[i] == 0){
            now++;
        }
    }

    int sum1[n], sum2[n];
    sum1[0] = (raw_data[0] == 0) ? 1 : raw_data[0];
    sum2[0] = (raw_data[0] == 0) ? -1 : raw_data[0];
    for(int i = 1; i < n; i++){
        sum1[i] = ((raw_data[i] == 0) ? 1 : raw_data[i]) + sum1[i - 1];
        sum2[i] = ((raw_data[i] == 0) ? -1 : raw_data[i]) + sum2[i - 1];
    }

    int mx1[n], mx2[n];
    mx1[n - 1] = sum1[n - 1], mx2[n - 1] = sum2[n - 1];
    for(int i = n - 2; i >= 0; i--){
        mx1[i] = max(mx1[i + 1], sum1[i]);
        mx2[i] = max(mx2[i + 1], sum2[i]);
    }

    int ans = 0;
    deque<pair<int, int>> q;
    for(int i = 0, lp = 0; i <= n; i++){
        while(!q.empty() && q.front().second < i){
            q.pop_front();
        }
        int id = ((!i) ? 0 : l[i - 1]) + k + 1;
        if(id > now){
            ans = max(ans,  (i == n ? -n : mx1[i]) - (!i ? 0 : sum1[i - 1]));
        }else{
            int np = pos[id - 1];
            for(; lp <= np - 1; lp++){
                while(!q.empty() && q.front().first < sum1[lp]){
                    q.pop_back();
                }
                q.emplace_back(sum1[lp], lp);
            }
            ans = max({ans, q.front().first, mx2[np] - sum1[i] + 2 * k});
        }
    }
    printf("%d\n", ans);
}