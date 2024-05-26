//
// Created by kibi on 23-11-15.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = unsigned long long;

    auto read = [](initializer_list<int*> x){
        auto read = [](int &x){
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
        };

        for(auto &i : x){
            read(*i);
        }
    };

    auto read_ll = [](initializer_list<ll*> x){
        auto read_ll = [](ll &x){
            ll s = 0, w = 1, c = getchar();
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
        };

        for(auto &i : x){
            read_ll(*i);
        }
    };

    int n, m, d, q;

    read({&n, &m, &d, &q});

    ll raw[n], aim[m];
    set<ll> raw_st_aim;
    vector<ll> st, raw_aim;
    for(ll &i : raw){
        read_ll({&i});
    }
    for(ll &i : aim){
        read_ll({&i});
        raw_st_aim.insert(i);
    }

    for(auto &i : raw_st_aim){
        raw_aim.emplace_back(i);
    }
    raw_aim.shrink_to_fit();

    for(auto &i : raw_aim){
        bool flag = true;
        for(auto &j : raw_aim){
            ll t = i;
            while(t){
                if(t / d == j){
                    flag = false;
                    break;
                }
                t /= d;
            }
            if(!flag){
                break;
            }
        }
        if(flag){
            st.emplace_back(i);
        }
    }

    bool pre[n], pre_col[st.size()][n];
    int sum[n], sum_col[st.size()][n];
    memset(pre, 0, sizeof pre);
    memset(pre_col, 0, sizeof pre_col);
    memset(sum_col, 0, sizeof sum_col);
    memset(sum, 0, sizeof sum);
    for(int i = 0; i < n; i++){
        int cnt = 0;
        vector<ll> now;
        ll t = raw[i];
        while(t){
            now.emplace_back(t);
            t /= d;
        }
        for(auto &j : st){
            for(auto &k : now){
                if(k == j){
                    pre_col[cnt][i] = true;
                    break;
                }
            }
            if(pre_col[cnt][i]){
                break;
            }
            cnt++;
        }
        if(cnt < st.size()){
            pre[i] = true;
        }
    }
    sum[0] = pre[0];
    for(int i = 0; i < st.size(); i++){
        sum_col[i][0] = pre_col[i][0];
    }
    for(int i = 1; i < n; i++){
        sum[i] = sum[i - 1] + pre[i];
        for(int j = 0; j < st.size(); j++){
            sum_col[j][i] = sum_col[j][i - 1] + pre_col[j][i];
        }
    }

    while(q--){
        int l, r;
        read({&l, &r});
        l--, r--;
        int ans = 0;
        for(int i = 0; i < st.size(); i++){
            ans += (sum_col[i][r] - (l ? sum_col[i][l - 1] : 0) ? 1 : 0);
        }
        printf("%d\n", ans);
    }
}