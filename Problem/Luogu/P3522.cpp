//
// Created by kibi on 23-11-6.
//
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

    class Node{
    public:
        int l, r;
    };

    int n;
    read({&n});

    Node node[n];
    for(auto &i : node){
        read({&i.l, &i.r});
    }

    class Cmp{
    public:
        bool operator () (const pair<int, int> &a, const pair<int, int> &b){
            return a.second > b.second;
        }
    };

    int pos[n];
    memset(pos, -1, sizeof pos);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> q;
    for(int i = n - 1; i >= 0; i--){
        while(!q.empty() && q.top().second < node[i].l){
            pos[q.top().first] = i;
            q.pop();
        }
        q.emplace(i, node[i].r);
    }

    // ri >= pre_min_l

    int ans = 1, l = 0;
    for(int i = 0; i < n; i++){
        while(pos[i] >= l){
            l++;
        }
        ans = max(ans, i - l + 1);
        int mx = -1e9;
        for(int j = l; j <= i; j++){
            if(node[j].r < mx){
                throw exception();
            }
            mx = max(mx, node[j].l);
        }
    }

    printf("%d\n", ans);

}