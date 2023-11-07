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

    class CP{
    public:
        int p1, p2;
    };

    class Node{
    public:
        int id{};
        vector<Node*> v;

        void add_edge(Node *v){
            this->v.emplace_back(v);
        }
    };

    Node node[2 * n];
    CP cp[n];
    for(int i = 0; i < n; i++){
        int l, r;
        read({&l, &r});
        l--, r--;
        cp[i].p1 = l;
        cp[i].p2 = r;
        node[l].add_edge(&node[r]);
        node[r].add_edge(&node[l]);
        node[l].id = l, node[r].id = r;
    }

    for(int i = 0; i < 2 * n; i += 2){
        node[i].add_edge(&node[i + 1]);
        node[i + 1].add_edge(&node[i]);
    }

    bool col[2 * n];
    bool vis[2 * n];
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < 2 * n; i++){
        if(!vis[i]){
            queue<int> q;
            q.push(i);
            col[i] = false;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(auto &v : node[u].v){
                    if(!vis[v->id]){
                        vis[v->id] = true;
                        col[v->id] = !col[u];
                        q.push(v->id);
                    }
                }
            }
        }
    }

    for(auto &i : cp){
        printf("%d %d\n", 1 + col[i.p1], 1 + col[i.p2]);
    }

}