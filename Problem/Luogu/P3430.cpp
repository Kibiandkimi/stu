//
// Created by kibi on 23-11-7.
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

    int n;
    read({&n});

    class Node{
    public:
        int ls{-1}, rs{-1};
        bool lv{}, rv{};

        void add_edge(int v, bool flag){
            if(ls == -1){
                ls = v, lv = flag;
            }else{
                rs = v, rv = flag;
            }
        }
    };

    Node node[n];

    map<int, pair<int, bool>> mp;
    for (int i = 0; i < n; ++i){
        int l;
        read({&l});
        if(mp.find(l) != mp.end()){
            node[i].add_edge(mp[l].first, true);
            node[mp[l].first].add_edge(i, true);
            //            node[i].ls = mp[l].first;
            //            node[mp[l].first].ls = i;
            //            node[i].lv = true;
            //            node[mp[l].first].lv = true;
        }else{
            mp[l] = {i, false};
        }
    }
    for (int i = 0; i < n; ++i){
        int r;
        read({&r});
        if(mp.find(r) != mp.end()){
            node[i].add_edge(mp[r].first, mp[r].second);
            node[mp[r].first].add_edge(i, mp[r].second);
            //            node[i].rs = mp[r].first;
            //            node[mp[r].first].rs = i;
            //            node[i].rv = mp[r].second;
            //            node[mp[r].first].rv = mp[r].second;
        }else{
            mp[r] = {i, true};
        }
    }

    int res = 0;
    bool col[n];
    bool vis[n];
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; ++i){
        if(!vis[i]){
            int c0 = 1, c1 = 0;
            vis[i] = true;
            queue<int> q;
            q.push(i);
            col[i] = false;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                if(node[u].ls != -1 && !vis[node[u].ls]){
                    vis[node[u].ls] = true;
                    q.push(node[u].ls);
                    col[node[u].ls] = col[u] ^ node[u].lv;
                    col[node[u].ls] ? c1++ : c0++;
                }
                if(node[u].rs != -1 && !vis[node[u].rs]){
                    vis[node[u].rs] = true;
                    q.push(node[u].rs);
                    col[node[u].rs] = col[u] ^ node[u].rv;
                    col[node[u].rs] ? c1++ : c0++;
                }
            }
            res += min(c0, c1);
        }
    }

    printf("%d\n", res);
}