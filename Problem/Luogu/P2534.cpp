//
// Created by kibi on 24-7-27.
//

// TODO this is A* but need IDA*
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](){
        uint s = 0, c = getchar();
        while(c < '0' || '9' < c){
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        return s;
    };


    const uint n = read();

    using T = vector<unsigned short>;
    using U = tuple<T, uint>;

    T raw(n), st(n);
    for(auto &i : raw){
        i = read();
    }

    map<uint, uint> mp;

    st = raw;

    sort(st.begin(), st.end());

    for(auto &i : st){
        mp[i] = (&i) - &*st.begin() + 1;
    }

    for(auto &i : raw){
        i = mp[i];
    }

    class Cmp{
    public:
        bool operator () (const U &a_, const U &b_){
            auto [a, step1] = a_;
            auto [b, step2] = b_;
            uint cnt1 = 0, cnt2 = 0, lst = 0;
            for(auto &i : a){
                cnt1 += (i - lst != 1);
            }
            lst = 0;
            for(auto &i : b){
                cnt2 += (i - lst != 1);
            }
            return cnt1 + step1 > cnt2 + step2;
        }
    };

    priority_queue<U, vector<U>, Cmp> q;

    q.emplace(raw, 0);

    map<T, uint> my_st;
    my_st[raw] = 0;

    while(!q.empty()){
        auto [u, step] = q.top();
        q.pop();

        for(auto &i : u){
            reverse(&*u.begin(), &i + 1);
            if(my_st.find(u) == my_st.end() || my_st[u] > step + 1) {
                q.emplace(u, step + 1);
                my_st[u] = step + 1;
            }
            reverse(&*u.begin(), &i + 1);
        }

        auto check = [](T &u){
            for(auto &i : u){
                if(i != (uint)(&i - &*u.begin() + 1)){
                    return false;
                }
            }
            return true;
        };

        if(check(u)){
            printf("%d\n", step);
            return 0;
        }
    }
}
