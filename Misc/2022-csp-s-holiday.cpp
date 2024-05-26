#include <bits/stdc++.h>


namespace Raw {
    using namespace std;

    const int SizeN = 2505, SizeM = 10005;

    int head[SizeN], nxt[SizeM * 2], to[SizeM * 2], cnt;
    long long val[SizeN];
    vector<int> g[SizeN];

    int vis[2505];
    //bool t[2505][10];
    bool getH[2505];
    //int d[2505][2505][2];

    struct node {
        long long v;
        int tem[4];
        bool operator<(const node &b) const {
            return v < b.v;
        }
    };

    priority_queue<node> q[2505][4];
    long long ans;
    void read(int &x);
    void read(long long &x);
    void addEdge(int u, int v);
    long long f(int u, int step);
    bool cmp(int a, int b);


    int main() {

        int n, m, k;
        read(n), read(m), read(k);
        for (int i = 2; i <= n; i++) {
            read(val[i]);
        }
        for (int i = 1; i <= m; i++) {
            static int u, v;
            read(u), read(v);
            addEdge(u, v);
        }
        for (int i = 1; i <= n; i++) {
            static queue<int> q1, q2;
            static int flag[2505];
            q1.push(i);
            q2.push(0);
            while (!q1.empty()) {
                static int u, step;
                u = q1.front(), step = q2.front();
                q1.pop(), q2.pop();
                if (step > k) {
                    continue;
                }
                for (int now = head[u]; now; now = nxt[now]) {
                    if (flag[to[now]] != i) {
                        q1.push(to[now]), q2.push(step + 1);
                        flag[to[now]] = i;
                        g[i].emplace_back(to[now]);
                        if (to[now] == 1) {
                            getH[i] = true;
                        }
                    }
                }
            }
            sort(g[i].begin(), g[i].end(), cmp);
        }
        f(1, 0);
        printf("%lld", ans);
        return 0;
    }

    bool cmp(int a, int b) {
        return val[a] > val[b];
    }

    int tem[4];
    long long now;
    long long f(int u, int step) {
        if (step == 4 && getH[u]) {
            node t{};
            t.v = val[u];
            t.tem[0] = tem[0];
            t.tem[1] = tem[1];
            t.tem[2] = tem[2];
            t.tem[3] = tem[3];
            q[u][step - 1].push(t);
            return val[u];
        } else if (step == 4) {
            return -1;
        }

        if (now + q[u][step - 1].top().v <= ans) {
            return -1;
        }

        stack<node> sta;
        long long res = -1;
        while (!q[u][step - 1].empty()) {
            bool tf;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (tem[i] == q[u][step - 1].top().tem[i] && tem[i] != 0) {
                        tf = false;
                        break;
                    }
                }
                if (!tf) {
                    break;
                }
            }

            if (!tf) {
                sta.push(q[u][step - 1].top());
                q[u][step - 1].pop();
            } else {
                long long t = q[u][step - 1].top().v;
                while (!sta.empty()) {
                    q[u][step - 1].push(sta.top());
                    sta.pop();
                }
                ans = max(ans, t + now);
                return t;
            }
        }
        while (!sta.empty()) {
            q[u][step - 1].push(sta.top());
            sta.pop();
        }
        now += val[u];
        tem[step - 1] = u;
        for (auto &i : g[u]) {
            if (vis[i]) {
                continue;
            }
            vis[i] = true;

            res = max(res, f(i, step + 1));
            ans = max(res + val[u], ans);
            vis[i] = false;
        }
        tem[step - 1] = 0;
        now -= val[u];

        node t{};
        t.v = val[u] + res;
        t.tem[0] = tem[0];
        t.tem[1] = tem[1];
        t.tem[2] = tem[2];
        t.tem[3] = tem[3];
        q[u][step - 1].push(t);

        return res + val[u];
    }

    void addEdge(int u, int v) {
        ++cnt;
        nxt[cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt;
        ++cnt;
        nxt[cnt] = head[v];
        to[cnt] = u;
        head[v] = cnt;
    }

    void read(int &x) {
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }

    void read(long long &x) {
        long long s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }

}

using namespace std;

void read(int&);
void read(long long&);

int main(){
    const int MaxN = 2505;
    int n, m, k;
    static bool toHome[MaxN];
    static long long val[MaxN];
    read(n), read(m), read(k);

    class Graph{
        int head[MaxN], nxt[MaxN * MaxN], to[MaxN * MaxN], cnt;
        void _addEdge(int u, int v){
            ++cnt;
            nxt[cnt] = head[u];
            to[cnt] = v;
            head[u] = cnt;
        }
    public:
        class Point{
        public:
            Graph *g;
            int p;
            Point & operator ++() {
                p = g->nxt[p];
                return *this;
            }
            Point(int x, Graph *g){
                this -> g = g;
                p = g->head[x];
            }
        };
        void addEdge(int u, int v, bool flag = true){
            _addEdge(u, v);
            flag ? _addEdge(v, u) : void();
        }
        int get(Point x){
            return to[x.p];
        }
    };

    static Graph gRaw, g;

    for(int i = 2; i <= n; i++){
        read(val[i]);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        read(u), read(v);
        gRaw.addEdge(u, v);
    }

    for (int i = 1; i <= n; i++) {
        static queue<int> q1, q2;
        static int flag[2505];
        flag[i] = i;
        q1.push(i);
        q2.push(0);
        while (!q1.empty()) {
            static int u, step;
            u = q1.front(), step = q2.front();
            q1.pop(), q2.pop();
            if (step > k) {
                continue;
            }
            for (Graph::Point now(u, &gRaw); now.p; ++now) {
                static int v;
                v = gRaw.get(now);
                if (flag[v] != i) {
                    q1.push(v), q2.push(step + 1);
                    flag[v] = i;
                    g.addEdge(i, v, false);
                    if (v == 1) {
                        toHome[i] = true;
                    }
                }
            }
        }
    }

    static int maxValP[MaxN][3];

    for(int i = 2; i <= n; i++){
        int *a = maxValP[i];

        for (Graph::Point now(i, &g); now.p; ++now){
            static int p;
            static long long v;
            p = g.get(now);
            if(p == 1){
                continue;
            }
            if(!toHome[p]){
                continue;
            }
            v = val[p];
            if(v >= val[a[0]]){
                a[2] = a[1];
                a[1] = a[0];
                a[0] = p;
            }else if(v >= val[a[1]]){
                a[2] = a[1];
                a[1] = p;
            }else if(v >= val[a[2]]){
                a[2] = p;
            }
        }
    }

    long long ans = -1e18;

    for(int i = 2; i <= n; i++){
        for(Graph::Point pos(i, &g); pos.p; ++pos){
            static int j;
            j = g.get(pos);

            //            if(j <= i){
            //                continue;
            //            }

            if(!(j != i && j != 1)){
                continue;
            }

            int *a = maxValP[i], *b = maxValP[j];
            static int pa, pb;
            static long long now;
            now = val[i] + val[j];
            pa = 0, pb = 0;
            if(a[pa] == j){
                pa++;
            }
            if(b[pb] == i){
                pb++;
            }
            if(a[pa] == 0 || b[pb] == 0){
                continue ;
            }
            if(a[pa] != b[pb]){
                ans = max(ans, val[a[pa]] + val[b[pb]] + now);
            }else{
                pa++;
                if(a[pa] == j){
                    pa++;
                }
                if(a[pa] == 0){
                    continue ;
                }
                ans = max(ans, val[a[pa]] + val[b[pb]] + now);
                pa--;
                if(a[pa] == j){
                    pa--;
                }

                pb++;
                if(b[pb] == i){
                    pb++;
                }
                if(b[pb] == 0){
                    continue ;
                }
                ans = max(ans, val[a[pa]] + val[b[pb]] + now);
            }
        }
    }
    printf("%lld", ans);
}

void read(int &x) {
    int s = 0, w = 1, c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-') {
            w = -1;
        }
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}

void read(long long &x) {
    long long s = 0, w = 1, c = getchar();
    while (c < '0' || '9' < c) {
        if (c == '-') {
            w = -1;
        }
        c = getchar();
    }
    while ('0' <= c && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}