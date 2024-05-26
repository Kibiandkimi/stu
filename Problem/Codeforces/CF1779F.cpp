//
// Created by kibi on 23-11-6.
//

// TODO not finish, path not correct, f maybe wrong too;

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

    class Tree{
        class Node{
        public:
            int id{}, siz{}, val{};
            Node *fa{};
            vector<Node*> son;
            int f[32]{};
            vector<pair<int, int>> org[32];
        };

        Node *rt;
        vector<Node> node;

        int pre[32]{};

        static void update(int &x, int y){
            x = x == -1 ? y : min(x, y);
        }

        void dfs(Node *u){
            u->siz = 1;
            u->f[u->val] = 0;
            u->org[u->val] = {-1, u->val};
            for(auto &v : u->son){
                dfs(v);
                u->siz += v->siz;
                memcpy(pre, u->f, sizeof u->f);
                memset(u->f, -1, sizeof u->f);
                for(int i = 0; i < 32; i++){
                    if(pre[i] == -1){
                        continue;
                    }
                    for(int j = 0; j < 32; j++){
                        if(v->f[j] == -1){
                            continue;
                        }
                        update(u->f[i ^ j], v->f[j] + pre[i]);
                        if(u->f[i ^ j] == v->f[j] + pre[i]){
                            u->org[i ^ j] = {v->id, j};
                        }
                    }
                }
            }
            if(!(u->siz & 1)){
                update(u->f[0], 2);
                if(u->f[0] == 2){
                    u->org[0] = {-2, 0};
                }
            }
        }

    public:
        Tree(int rt, int n, const int *fa, const int *val):node(n){
            for(int i = 0; i < n; i++){
                node[i].id = i;
                node[i].val = val[i];
                memset(node[i].f, -1, sizeof node[i].f);
                if(i == rt){
                    continue;
                }
                node[i].fa = &node[fa[i]];
                node[fa[i]].son.emplace_back(&node[i]);
            }

            this->rt = &node[rt];

            dfs(this->rt);
        }

        friend class Work;
    };

    int n;
    read({&n});

    int val[n];
    for(auto &i : val){
        read({&i});
    }

    int fa[n];
    for(int i = 1; i < n; i++){
        read({&fa[i]});
        fa[i]--;
    }
    Tree tree(0, n, fa, val);

    class Work{
    public:
        explicit Work(Tree &tree){
            if(tree.node[0].f[0] == -1){
                printf("-1\n");
                return;
            }
            int now = 0, nxt = 0;
            vector<int> ans;
            while(now >= 0){
                ans.emplace_back(now);
                int t1 = tree.node[now].org[nxt].first, t2 = tree.node[now].org[nxt].second;
                now = t1;
                nxt = t2;
            }
            if(now == -2){

            }
            printf("%d\n", (int)ans.size());
            reverse(ans.begin(), ans.end());
            for(auto &i : ans){
                printf("%d ", i + 1);
            }
            printf("\n");
        }
    };

    Work{tree};
}