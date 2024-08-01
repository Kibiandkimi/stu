//
// Created by kibi on 24-7-16.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;
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

    class Graph{

        class Edge{
        public:
            int v, w;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n, nullptr){}

        void add_edge(int u, int v, int w, bool flag = false){
            head[u] = new Edge{v, w, head[u]};
            return flag ? add_edge(v, u, w) : void(0);
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    class Tree{
    public:
        class Node;
        using tp = tuple<Node*, ll>;
        class Node{
        public:
            int id;
            tp fa;
            vector<tp> son;
        };

        vector<Node*> node;
        int rt;
        Tree(int rt, int n, Graph &graph):rt(rt), node(n){
            queue<Node*> q;
            q.emplace(node[rt] = new Node{rt, {nullptr, 0}});
            while(!q.empty()){
                auto u = q.front();
                q.pop();
                for(auto i = graph.begin(u->id); i; i = i->nxt){
                    if(get<0>(u->fa) && i->v == get<0>(u->fa)->id){
                        continue;
                    }
                    u->son.emplace_back(node[i->v] = new Node{i->v, {u, i->w}}, i->w);
                    q.emplace(get<0>(u->son.back()));
                }
            }
        }
    };

    class GetFa{
        using Node = Tree::Node;
        using tp = tuple<Node*, ll>;
        vector<tp> fa[20];

    public:
        static int id(tp u){
            return ::get<0>(u) ? ::get<0>(u)->id : 0;
        }

        GetFa(int n, Tree &tree){
            for(auto &i : fa){
                i.reserve(n);
            }
            for(int i = 0; i < n; i++){
                fa[0].emplace_back(tree.node[i]->fa);
            }
            for(int i = 1; i < 20; i++){
                for(int j = 0; j < n; j++){
                    fa[i].emplace_back(::get<0>(fa[i - 1][id(fa[i - 1][j])]), ::get<1>(fa[i - 1][id(fa[i - 1][j])]) + ::get<1>(fa[i - 1][j]));
                }
            }
        }

        tuple<int, ll> get(int u, ll k){
            for(int i = 19; i >= 0 && k > 0; i--){
                if(::get<0>(fa[i][u]) != nullptr && id(fa[i][u]) != 0 && ::get<1>(fa[i][u]) <= k){
                    k -= ::get<1>(fa[i][u]);
                    u = id(fa[i][u]);
                }
            }
            return {u, k};
        }
    };

    static int n;
    read(n);

    Graph graph(n);

    for(int i = 1; i < n; i++){
        int u, v, w;
        read(u), read(v), read(w);
        u--, v--;
        graph.add_edge(u, v, w, true);
    }

    static Tree tree(0, n, graph);

    static int m;
    read(m);

    if(tree.node[0]->son.size() > m){
        printf("-1\n");
        return 0;
    }

    static vector<int> military(m);
    for(auto &i : military){
        read(i);
        i--;
    }

    static auto check = [](ll k){
        using tp = tuple<int, ll>;
        static GetFa getFa(n, tree);
        static vector<tp> v, used;
        static vector<int> flag;
        static vector<int> require;
        v.clear(), used.clear();
        flag.clear(), flag.resize(n, -1);
        require.clear();
        for(int i = 0; i < m; i++){
            auto tem = getFa.get(military[i], k);
            if(GetFa::id(tree.node[get<0>(tem)]->fa) == 0){
                if(get<1>(tem) > get<1>(tree.node[get<0>(tem)]->fa)){
                    v.emplace_back(tem);
                    get<1>(v.back()) -= get<1>(tree.node[get<0>(v.back())]->fa);
                }else{
                    flag[get<0>(tem)] = (int)used.size();
                    used.emplace_back(tem);
                }
            }else if(flag[get<0>(tem)] < 0){
                flag[get<0>(tem)] = (int)used.size();
                used.emplace_back(tem);
            }
        }

        queue<int> q;
        for(int i = 1; i < n; i++){
            if(tree.node[i]->son.empty() && flag[i] < 0){
                q.emplace(tree.node[i]->id);
            }else if(tree.node[i]->son.empty() && flag[i] >= 0){
                get<1>(used[flag[i]]) = -1;
            }
        }
        while(!q.empty()){
            int u = q.front();
            q.pop();

            if(GetFa::id(tree.node[u]->fa) == 0){
                require.emplace_back(u);
            }else if(flag[GetFa::id(tree.node[u]->fa)] < 0){
                q.emplace(GetFa::id(tree.node[u]->fa));
            }else{
                get<1>(used[flag[GetFa::id(tree.node[u]->fa)]]) = -1;
            }
        }

        //        for(auto &i : used){
        //            if(get<1>(i) >= 0 && GetFa::id(tree.node[get<0>(i)]->fa) == 0){
        //                get<1>(i) -= get<1>(tree.node[get<0>(i)]->fa);
        //                v.emplace_back(i);
        //            }
        //        }

        sort(v.begin(), v.end(), [](const tp &a, const tp &b){return get<1>(a)>get<1>(b);});
        sort(require.begin(), require.end(), greater<>());

        for(int i = 0; i < require.size(); i++){
            if(get<1>(v[i]) < get<1>(tree.node[require[i]]->fa) && get<0>(v[i]) != require[i]){
                return false;
            }
        }

        return true;
    };

    auto solve = [](){
        ll l = 0, r = 50000000000000ll;
        while(l < r){
            ll k = (l + r) >> 1;
            if(check(k)){
                r = k;
            }else{
                l = k + 1;
            }
        }
        return l;
    };

    ll ans = solve();

    printf("%lld\n", ans);
}