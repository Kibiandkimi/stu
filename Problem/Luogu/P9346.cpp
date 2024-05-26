//
// Created by kibi on 23-11-6.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static int Mod = 985661441;
    using ll = long long;

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

    static auto add = [](int &x, int y){
        x = (x + y) % Mod;
    };

    class Tree{
        class Node{
        public:
            int id{}, siz{};
            Node *fa{};
            vector<Node*> son;
            vector<int> f[3];
        };

        Node *rt;
        vector<Node> node;

        vector<int> pre[3];

        void dfs(Node *u){
            u->siz = 1;
            u->f[0][0] = 1;
            for(auto &v : u->son){
                dfs(v);
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < u->f[i].size(); j++){
                        pre[i][j] = u->f[i][j];
                        u->f[i][j] = 0;
                    }
                }
                for(int i = 0; i < u->siz; i++){
                    for(int j = 0; j < v->siz; j++){
                        if(i + j + 1 >= u->f[0].size()){
                            throw exception();
                        }
                        add(u->f[0][i + j + 1], (int)((ll)pre[0][i] * ((ll)v->f[0][j] + v->f[1][j] + v->f[2][j]) % Mod));
                        add(u->f[1][i + j], (int)((ll)pre[0][i] * ((ll)v->f[0][j] + v->f[1][j]) % Mod));
                        add(u->f[1][i + j + 1], (int)((ll)pre[1][i] * ((ll)v->f[0][j] + v->f[1][j] + v->f[2][j]) % Mod));
                        add(u->f[2][i + j], (int)((ll)pre[1][i] * ((ll)v->f[0][j] + v->f[1][j]) % Mod));
                        add(u->f[2][i + j + 1], (int)((ll)pre[2][i] * ((ll)v->f[0][j] + v->f[1][j] + v->f[2][j]) % Mod));
                    }
                }
                u->siz += v->siz;
            }
        }

    public:
        Tree(int n, int rt, const int *fa):node(n), pre{vector<int>(n), vector<int>(n), vector<int>(n)} {
            for(int i = 0; i < n; i++){
                node[i].id = i;
                node[i].f[0] = node[i].f[1] = node[i].f[2] = vector<int>(n, 0);
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

    static int n;
    read({&n});

    int fa[n];
    for(int i = 1; i < n; i++){
        read({&fa[i]});
        fa[i]--;
    }

    static Tree tree(n, 0, fa);

    int raw_inv[n + 1], raw_fac[n + 1];
    raw_inv[0] = 0;
    raw_inv[1] = raw_fac[0] = raw_fac[1] = 1;
    for(int i = 2; i <= n; i++){
        raw_inv[i] = (int)((ll)(Mod - Mod / i) * raw_inv[Mod % i] % Mod);
        raw_fac[i] = (int)((ll) raw_fac[i - 1] * i % Mod);
    }

    static int *inv = raw_inv, *fac = raw_fac;

    class Work{
    public:
        Work(){
            int ans = 0, sum = 1, inv_sum = 1;
            for(int i = 0; i < n; i++){
                int t = (int)(((ll)tree.rt->f[0][i] + tree.rt->f[1][i] + tree.rt->f[2][i]) * fac[i] % Mod);
                add(ans, (int)((ll)(sum - t) * inv_sum % Mod));
                sum = (int)((ll) sum * (n - 1 - i) % Mod);
                inv_sum = (int)((ll) inv_sum * inv[n - 1 - i] % Mod);
            }
            printf("%d\n", (ans % Mod + Mod) % Mod);
        }
    };

    Work{};
}