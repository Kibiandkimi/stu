//
// Created by kibi on 23-8-8.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 300000, M = 300000;

int main(){

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

    class Question{
    public:
        int id, l, r, ans;

        static bool cmp(Question a, Question b){
            return a.r < b.r;
        }
    };

    class Data{
    public:
        int id, v;

        static bool cmp(Data a, Data b){
            return a.v < b.v;
        }
    };

    class TreeArray{
        int data[4 * N + 5]{}, n;

    public:
        explicit TreeArray(int n):n(n){}

        void add(int x){
            while(x <= n){
                data[x]++;
                x += (x & -x);
            }
        }

        int query(int x){
            int sum = 0;
            while(x){
                sum += data[x];
                x -= (x&-x);
            }
            return sum;
        }
    };

    class Pair{
        int l, r;
    public:

        static bool cmp(Pair a, Pair b){
            return a.r < b.r;
        }

        void init(int x, int y){
            l = min(x, y); // min
            r = x+y-l; // max
        }

        int get_l() const{
            return l;
        }

        int get_r() const{
            return r;
        }
    };

    int n, m;
    Tools::read(n), Tools::read(m);

    static Data raw_data[N + 5];
    for(int i = 1; i <= n; i++){
        raw_data[i].id = i;
        Tools::read(raw_data[i].v);
    }

    sort(raw_data + 1, raw_data + 1 + n, Data::cmp);

    static Pair pair[2 * N + 5];

    int cnt_of_pair = 0;

    for(int i = 2; i < n; i++){
        if(raw_data[i].v - raw_data[i-1].v >= raw_data[i+1].v - raw_data[i].v){
            pair[++cnt_of_pair].init(raw_data[i].id, raw_data[i+1].id);
        }
        if(raw_data[i].v - raw_data[i-1].v <= raw_data[i+1].v - raw_data[i].v){
            pair[++cnt_of_pair].init(raw_data[i].id, raw_data[i-1].id);
        }
    }

    if(n >= 2){
        pair[++cnt_of_pair].init(raw_data[1].id, raw_data[2].id);
        pair[++cnt_of_pair].init(raw_data[n].id, raw_data[n-1].id);
    }

    sort(pair + 1, pair + 1 + cnt_of_pair, Pair::cmp);

    static Question question[M + 5];

    for(int i = 1; i <= m; i++){
        int l, r;
        Tools::read(l), Tools::read(r);
        question[i] = {i, l, r, 0};
    }

    sort(question + 1, question + 1 + m, Question::cmp);

    static TreeArray tree_array(n);

    long long ans = 0;

    for(int i = 1; i <= n; i++){
        static int pos_of_pair = 1, pos_of_question = 1;
        while(pair[pos_of_pair].get_r() <= i && pos_of_pair <= cnt_of_pair){
            tree_array.add(pair[pos_of_pair].get_l());
            pos_of_pair++;
        }
        while(question[pos_of_question].r <= i && pos_of_question <= m){
            question[pos_of_question].ans =
                    tree_array.query(question[pos_of_question].r) -
                    tree_array.query(question[pos_of_question].l - 1);
            ans = ans + (long long)question[pos_of_question].ans *
                                question[pos_of_question].id;
            pos_of_question++;
        }
    }

    printf("%lld\n", ans);

}