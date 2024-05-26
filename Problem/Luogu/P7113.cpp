//
// Created by kibi on 23-9-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 100000;

    class Num{
        int data[25]{};

    public:
        Num(){
            memset(data, 0, sizeof data);
        };

        explicit Num(int a){
            static int cnt = 0;
            while(a){
                data[cnt++] = a % 10;
                a >>= 1;
            }
        };

        Num operator + (const Num &b) const{
            Num res;
            for(int i = 0; i < 24; i++){
                res.data[i] = data[i] + b.data[i];
                res.data[i + 1] += res.data[i] / 10;
                res.data[i] %= 10;
            }
        }

        void operator ++(){
            data[0]++;
            int cnt = 0;
            while(data[cnt] > 9){
                data[cnt + 1] = data[cnt] / 10;
                data[cnt] %= 10;
                cnt++;
            }
        }

        bool operator < (const Num &b) const {
            for(int i = 23; i >= 0; i--){
                if(data[i] < b.data[i]){
                    return true;
                }else if(data[i] > b.data[i]){
                    return false;
                }
            }
            return false;
        }

        bool operator == (const Num &b) const{
            for(int i = 23; i >= 0; --i){
                if(data[i] != b.data[i]){
                    return false;
                }
            }
            return true;
        }

        bool operator <= (const Num &b) const{
            return (*this < b) || (*this == b);
        }

        Num operator * (const Num &b) const{
            Num res;
            for(Num i(1); i <= b; i = i + (Num)1){
                res = res + (*this);
            }
            return res;
        }

        Num operator - (const Num &b) const{
            Num res;
            for(int i = 0; i < 24; i++){
                res.data[i] = data[i] - b.data[i];
                if(res.data[i] < 0){
                    res.data[i] += 10;
                    res.data[i + 1]--;
                }
            }
            return res;
        }

        bool t1() const {
            if(data[0] % 2){
                return true;
            }
            return false;
        }

        void t2(){
            for(int i = 23; i > 0; i--){
                data[i - 1] += 10 * (data[i] % 2);
                data[i] >>= 1;
            }
            data[0] >>= 1;
        }

        Num gcd(Num a, Num b) {
            int atimes = 0, btimes = 0;
            while (!a.t1()) {
                a.t2();
                atimes++;
            }
            while (!b.t1()) {
                a.t2();
                btimes++;
            }
            for (;;) {
                while (!a.t1()) {
                    a.t2();
                }
                while (!b.t1()) {
                    b.t2();
                }
                if (a == b) break;
                if (a < b) swap(a, b);
                a = a - b;
            }
            auto pow = [](int a, int p){
                int res = 1;
                while(p){
                    if(p & 1){
                        res = (res * a);
                    }
                    a = a * a;
                    p >>= 1;
                }
                return res;
            };
            return a * (Num)pow(2, min(atimes, btimes));
        }
    };

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
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };
        Edge *head[N + 5];
        Edge edge[N * 5 + 5];
        int cnt;

        friend class Work;

    public:
        void add_edge(int u, int v, bool flag = false){
            edge[++cnt] = {v, head[u]};
            head[u] = &edge[cnt];

            if(!flag){
                return ;
            }

            add_edge(v, u);
        }
    };

    auto read = Tools::read;

    static int n, m;
    read(n), read(m);

    static Graph graph;
    static int d[N + 5];
    for(int i = 1; i <= n; i++){
        read(d[i]);
        for(int j = 0; j < d[i]; j++){
            int to;
            read(to);
            graph.add_edge(i, to);
        }
    }

    class Work{
    public:
        Work(){
            static int in[N + 5];
            for(int i = 1; i <= n; i++){
                for(auto j = graph.head[i]; j; j = j->nxt){
                    in[j->v]++;
                }
            }

            static Num a[N + 5], b[N + 5]; // a/b
            static queue<int> q;
            for(int i = 1; i <= n; i++){
                b[i] = (Num)1;
                if(!in[i]){
                    q.push(i);
                    a[i] = (Num)1;
                }
            }

            while(!q.empty()){
                int u = q.front();
                q.pop();

                b[u] = b[u] * (Num)d[u];

                for(auto i = graph.head[u]; i; i = i->nxt){
                    // gcd(b, d) = g
                    // b = b/g, d = d/g
                    // a/b + c/d = (ad+bc)/bd
                    // a:a[u], b:b[u], c:a[i->to], d:b[i->to]
                    a[i->v] = a[u] * b[i->v] + b[u] * a[i->v];
                    b[i->v] = b[u] * b[i->v];
                    // Todo how div
                }

            }
        }
    };

    Work();

}

// 60pts

/*
 *

 #include <bits/stdc++.h>
using namespace std;

int main(){

   using ull = unsigned long long;
   const int N = 100000;

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

       static ull gcd(ull a, ull b){
           if(!b){
               return a;
           }
           return gcd(b, a % b);
       }
   };

   class Graph{
       class Edge{
       public:
           int v;
           Edge *nxt;
       };
       Edge *head[N + 5];
       Edge edge[N * 5 + 5];
       int cnt;

       friend class Work;

   public:
       void add_edge(int u, int v, bool flag = false){
           edge[++cnt] = {v, head[u]};
           head[u] = &edge[cnt];

           if(!flag){
               return ;
           }

           add_edge(v, u);
       }
   };

   auto read = Tools::read;

   static int n, m;
   read(n), read(m);

   static int d[N + 5], in[N + 5];
   static Graph graph;
   for(int i = 1; i <= n; i++){
       read(d[i]);
       for(int j = 1; j <= d[i]; j++){
           int to;
           read(to);
           in[to]++;
           graph.add_edge(i, to);
       }
   }

   class Work{
   public:
       Work(){
           static queue<int> q;
           static ull a[N + 5], b[N + 5];
           for(int i = 1; i <= n; i++){
               b[i] = 1;
               if(!in[i]){
                   q.push(i);
                   a[i] = 1;
               }
           }

           while(!q.empty()){
               int u = q.front();
               q.pop();

               if(!d[u]){
                   continue;
               }

               b[u] = b[u] * d[u];

               for(auto i = graph.head[u]; i; i = i->nxt){
                   a[i->v] = a[u] * b[i->v] + b[u] * a[i->v];
                   b[i->v] = b[u] * b[i->v];
                   ull gcd = Tools::gcd(a[i->v], b[i->v]);
                   a[i->v] /= gcd;
                   b[i->v] /= gcd;

                   in[i->v]--;
                   if(!in[i->v]){
                       q.push(i->v);
                   }
               }
           }

           for(int i = 1; i <= n; i++){
               if(!d[i]){
                   printf("%llu %llu\n", a[i], b[i]);
               }
           }
       }
   };

   Work();

}

 *
 * */