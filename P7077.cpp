//
// Created by kibi on 2022/8/18.
//
#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;
int n, m, Q, cnt1, cnt2, cnt3;
long long r[100005];
int q[100005];
int len3[100005], y[100005];
struct node1{
    int p;
    long long v;
}c1[100005];
struct node2{
    long long v;
}c2[100005];
struct node3{
    //    int id = -1;
    vector<int> opt;
}c3[100005];
struct node4{
    long long mul = 1;
    vector<int> p;
    vector<long long> v;
    //    vector<pair<int, long long> > v;
}c4[100005];
struct Func{
    int id, type;
};
Func func[100005];
vector<int> tp_res;

void tp(){
    static int in[100005];
    vector<int> g[100005];
    queue<int> tp_q;
    int vis[100005] = {0};
    for(int i = 1; i <= cnt3; i++){
        g[i].reserve(len3[y[i]]+2);
    }
    for(int i = 1; i <= cnt3; i++){
        int so = c3[i].opt.size();
        for(int j = 0; j < so; j++) {
            int t = c3[i].opt[j];
            if ((vis[func[t].id]!=i) && func[t].type==3) {
                //                g[func[t].id].push_back(func[i].id);
                g[func[t].id].push_back(i);
                //                in[func[i].id]++;
                in[i]++;
                vis[func[t].id] = i;
            }
        }
    }

    //    for(int i = 1; i <= m; i++){
    //        if(!in[i]&& func[i].type==3){
    //            tp_q.push(func[i].id);
    //        }
    //    }
    for(int i = 1; i <= cnt3; i++){
        if(!in[i]){
            tp_q.push(i);
        }
    }

    while(!tp_q.empty()){
        int u = tp_q.front();
        tp_q.pop();
        tp_res.push_back(u);
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            if(!(--in[g[u][i]])){
                tp_q.push(g[u][i]);
            }
        }
    }
}

void add_main(){
    func[m+1] = {++cnt3, 3};
    //    c3[cnt3].len = Q,
    //    c3[cnt3].id = m+1;
    c3[cnt3].opt.reserve(Q+5);
    for(int i = 1; i <= Q; i++){
        c3[cnt3].opt.push_back(q[i]);
    }
    tp_res.push_back(cnt3);
}

void jx(){
    int stp = tp_res.size();
    add_main();
    static int y[100005] = {0}, vis[100005] = {0};
    static long long mul_now[1000005];
    for(int i = 0; i <= stp; i++){
        int u = tp_res[i];
        int so = c3[u].opt.size();
        vector<int> &opt = c3[u].opt;
        int vis_first = 0, cnt = 0;
        node4 &out = c4[u];
        //        vector<long long> mul_now;
        //        mul_now.reserve(so+4);
        for(int j = so-1; j >= 0; j--){
            int v = opt[j];
            if(func[v].type==2){
                out.mul = ((out.mul * c2[func[v].id].v)%mod);
                mul_now[cnt++] = out.mul;
            }else if(func[v].type==3){
                //                mul_now.push_back(out.mul);
                mul_now[cnt++] = out.mul;
                out.mul = ((out.mul * c4[func[v].id].mul)%mod);
            }else {
                mul_now[cnt++] = out.mul;
                //                mul_now.push_back(out.mul);
            }
        }
        for(int j = 0; j < so; j++){
            int v = opt[j];
            if(func[v].type==1){
                node1 &f = c1[func[v].id];
                if((y[f.p]||f.p==vis_first)&&vis[f.p]==i){
                    out.v[y[f.p]] = (out.v[y[f.p]] + mul_now[(so-j-1)]*f.v)%mod;
                    //                    out.v[y[f.p]].second = (out.v[y[f.p]].second + mul_now[(so-j-1)]*f.v)%mod;
                }else{
                    //                    out.v.emplace_back(f.p, (mul_now[(so-j-1)]*f.v)%mod);
                    out.v.push_back((mul_now[(so-j-1)]*f.v)%mod);
                    out.p.push_back(f.p);
                    y[f.p] = out.v.size()-1;
                    vis[f.p] = i;
                    if(!y[f.p]){
                        vis_first = f.p;
                    }
                }
            }else if(func[v].type==3){
                node4 &f = c4[func[v].id];
                int ss = f.v.size();
                for(int k = 0; k < ss; k++){
                    if((y[f.p[k]]||f.p[k]==vis_first)&&vis[f.p[k]]==i){
                        out.v[y[f.p[k]]] = (out.v[y[f.p[k]]] + mul_now[(so-j-1)]*f.v[k])%mod;
                    }else{
                        //                        out.v.emplace_back(f.p[k], (mul_now[(so-j-1)]*f.v[k])%mod);
                        out.v.push_back((mul_now[(so-j-1)]*f.v[k])%mod);
                        out.p.push_back(f.p[k]);
                        vis[f.p[k]] = i;
                        y[f.p[k]] = out.v.size()-1;
                        if(!y[f.p[k]]){
                            vis_first = f.p[k];
                        }
                    }
                }
//                TODO 尝试释放c4的vector
//                --len4[y[func[v].id]];
//                if(!len4[y[func[v].id]]){
//                    vector<int>().swap(c4[func[v].id].p);
//                    vector<long long>().swap(c4[func[v].id].v);
//                }
            }
        }
        vector<int>().swap(c3[u].opt);
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

int main(){
    read(n);
    for(int i = 1; i <= n; i++){
        read(r[i]);
    }
    read(m);
    int vis[100005] = {0};
    for(int i = 1; i <= m; i++){
        int c;
        read(c);
        if(c == 1){
            func[i] = {++cnt1, 1};
            int p, v;
            read(p), read(v);
            c1[cnt1].p = p, c1[cnt1].v = v;
        }else if(c == 2){
            func[i] = {++cnt2, 2};
            int v;
            read(v);
            c2[cnt2].v = v;
        }else if(c == 3){
            func[i] = {++cnt3, 3};
            int l;
            read(l);
            c3[cnt3].opt.reserve(l+4);
            y[cnt3] = i;
            for(int j = 1; j <= l; j++){
                int t;
                read(t);
                if(func[t].type==3&& vis[t]!=i){
                    vis[t] = i;
                    len3[t]++;
                }
                c3[cnt3].opt.push_back(t);
            }
        }
    }
    read(Q);
    for(int i = 1; i <= Q; i++){
        read(q[i]);
    }

    tp();
    jx();

    for(int i = 1; i <= n; i++){
        r[i] = (r[i]*c4[cnt3].mul)%mod;
    }
    int ss = c4[cnt3].v.size();
    for(int i = 0; i < ss; i++){
        r[c4[cnt3].p[i]] = (r[c4[cnt3].p[i]] + c4[cnt3].v[i])%mod;
    }

    for(int i = 1; i <= n; i++){
        printf("%lld ", r[i]);
    }
}

// 23-10-31

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());
    static const int Mod = 998244353;
    using ll = long long;

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

        static void sub(int &x, int v){
            x = (int)(((ll)x * v) % Mod);
        }

        static void add(int &x, int v){
            x = (x + v) % Mod;
        }
    };

    auto read = Tools::read;
    static auto sub = Tools::sub;
    static auto add = Tools::add;

    freopen("t.in", "r", stdin);

    static int n;
    read(n);

    int raw_data[n];
    for(auto &i : raw_data){
        read(i);
    }

    class Index{
    public:
        bool type; // 0->base 1->func
        int index;
    };

    class BaseFunc{
    public:
        int id, x, v;

        BaseFunc(int id, int x, int v):id(id), x(x), v(v){}
    };

    class Func{
    public:
        int id{}, num_of_func{};
        vector<int> id_of_func;
    };

    static vector<BaseFunc> myBaseFunc;
    static vector<Func> myFunc;



    int m;
    read(m);
    int raw_in[m];
    static int* in = raw_in; // TODO maybe use in to topu, and delete no in func
    Index index[m];
    for(int i = 0; i < m; i++){
        int type;
        read(type);
        if(type == 1){
            int pos, val;
            read(pos), read(val);
            myBaseFunc.emplace_back(i + 1, pos, val);
            index[i] = {false, (int)myBaseFunc.size() - 1};
        }else if(type == 2){
            int val;
            read(val);
            myBaseFunc.emplace_back(i + 1, -1, val);
            index[i] = {false, (int)myBaseFunc.size() - 1};
        }else if(type == 3){
            int num;
            read(num);
            myFunc.emplace_back();
            Func &now = myFunc.back();
            now.id = i + 1;
            now.num_of_func = num;
            now.id_of_func.reserve(num);
            now.id_of_func.resize(num);
            for(auto &j : now.id_of_func){
                read(j);
                in[j - 1]++;
            }
            reverse(now.id_of_func.begin(), now.id_of_func.end());
            index[i] = {true, (int)myFunc.size() - 1};
        }
    }

    myBaseFunc.shrink_to_fit();
    myFunc.shrink_to_fit();

    class Run{
    public:
        class OptFunc{
        public:
            vector<pair<int, int>> add;
            int p;

            OptFunc():p(1){}
        };

        vector<OptFunc> optFunc;
        vector<bool> opt;
        int *data;
        Index *index;
        int flag;

        Run(int num, int *data, Index *index):
                                                optFunc(num),
                                                opt(num, false),
                                                data(data),
                                                index(index),
                                                flag(1){}

        void optimize(int id){
            auto change = new int [n];
            auto vis = new int [n];
            int snd = rnd();
            set<int> st;
            auto *now = &myFunc[index[id - 1].index];
            for(auto &i : now->id_of_func){
                if(index[i - 1].type && !opt[index[i - 1].index]){
                    optimize(i);
                }
                if(index[i - 1].type){
                    auto *nxt = &optFunc[index[i - 1].index];
                    for(auto &j : nxt->add){
                        int val = j.second;
                        sub(val, optFunc[index[id - 1].index].p);
                        if(vis[j.first] != snd){
                            st.insert(j.first);
                            change[j.first] = 0;
                            vis[j.first] = snd;
                        }
                        add(change[j.first], val);
                    }
                    sub(optFunc[index[id - 1].index].p, nxt->p);
                }else{
                    auto *nxt = &myBaseFunc[index[i - 1].index];
                    if(nxt->x < 0){
                        sub(optFunc[index[id - 1].index].p, nxt->v);
                    }else{
                        int val = nxt->v;
                        sub(val, optFunc[index[id - 1].index].p);
                        if(vis[nxt->x - 1] != snd) {
                            st.insert(nxt->x - 1);
                            change[nxt->x - 1] = 0;
                            vis[nxt->x - 1] = snd;
                        }
                        add(change[nxt->x - 1], val);
                    }
                }
            }
            for(auto &i : st){
                optFunc[index[id - 1].index].add.emplace_back(i, change[i]);
            }
            optFunc[index[id - 1].index].add.shrink_to_fit();
            opt[index[id - 1].index] = true;

            free(change);
            free(vis);
        }

        void run(int id){
            if(!index[id - 1].type){
                BaseFunc *now = &myBaseFunc[index[id - 1].index];
                if(now->x < 0){
                    sub(flag, now->v);
                }else{
                    int val = now->v;
                    sub(val, flag);
                    add(data[now->x - 1], val);
                }
            }else{
                if(!opt[index[id - 1].index]){
                    optimize(id);
                }

                auto *now = &optFunc[index[id - 1].index];
                for(auto &i : now->add){
                    int val = i.second;
                    sub(val, flag);
                    add(data[i.first], val);
                }
                sub(flag, now->p);
            }
        }
    };

    int pre[n];
    memset(pre, 0, sizeof pre);

    Run run((int)myFunc.size(), pre, index);

    int q;
    read(q);

    int question[q];

    for(auto &i : question){
        in[i - 1]++;
        read(i);
    }
    for(int i = q - 1; i >= 0; i--){
        run.run(question[i]);
    }

    for(int i = 0; i < n; i++){
        sub(raw_data[i], run.flag);
        add(raw_data[i], pre[i]);
        printf("%d ", raw_data[i]);
    }
    printf("\n");
}
 *
 * */