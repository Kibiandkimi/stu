//
// Created by kibi on 23-11-10.
//

// TODO not correct, need to learn KMP and fail tree better

#include <bits/stdc++.h>
using namespace std;

int main(){
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

    auto read_str = [](vector<int> &x){
        auto judge = [](int c){
            return 'a' <= c && c <= 'z';
        };
        int c = getchar();
        while(!judge(c)){
            c = getchar();
        }
        while(judge(c)){
            x.emplace_back(c);
            c = getchar();
        }
        x.shrink_to_fit();
    };

    vector<int> s;
    read_str(s);

    int pi[s.size()], raw_dep[s.size() + 1];
    auto dep = raw_dep + 1;
    pi[0] = 0;
    dep[-1] = 0;
    dep[0] = 1;
    for(int i = 1; i < s.size(); i++){
        int j = pi[i - 1];
        while(j && s[j] != s[i]){
            j = pi[j - 1];
        }
        if(s[i] == s[j]){
            j++;
        }
        dep[i] = dep[j - 1] + 1;
        pi[i] = j;
    }

    int raw_pre[s.size() + 1][20];
    auto pre = raw_pre + 1;
    pre[-1][0] = -1;
    pre[0][0] = -1;
    for(int i = 1; i < s.size(); i++){
        pre[i][0] = pi[i - 1];
    }
    for(int i = 1; i < 20; i++){
        for(int j = -1; j < (int)s.size(); j++) {
            pre[j][i] = pre[pre[j][i - 1]][i - 1];
        }
    }

    int m;
    read({&m});

    while(m--){
        int p, q;
        read({&p, &q});

        p--, q--;

        if(dep[p] > dep[q]){
            swap(p, q);
        }
        for(int i = 19; i >= 0; i--){
            if(dep[pre[q][i]] >= dep[p]){
                q = pre[q][i];
            }
        }
        for(int i = 19; i >= 0; i--){
            if(pre[q][i] != pre[p][i]){
                q = pre[q][i];
                p = pre[p][i];
            }
        }
        printf("%d\n", pre[p][0] + 1);

    }
}