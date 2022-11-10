//
// Created by kibi on 2022/10/23.
//
#include <bits/stdc++.h>
using namespace std;

class RawData{
    constexpr static const double g = 9.8;
public:
    int x, y, v, e, id;
    double l;
    static bool cmp(RawData a, RawData b){
        return a.y != b.y ? a.y < b.y : a.l > b.l;
    }
    void pre(){
        l = x + v * sqrt((2*y)/g);
    }
};

class Node{
public:
    double v;
    bool flag;
    int id, pos;
    Node(double v, bool flag, int id, int pos){
        this -> v = v, this -> flag = flag, this -> id = id, this -> pos = pos;
    }
    static bool cmp(Node a, Node b){
        return a.v < b.v;
    }
};

class Tree{
    int val[500005];
public:
    void add(int u, int v){
        for(int i = u; i < 500005; i += i&(-i)){
            val[i] += v;
        }
    }
    int query(int u){
        static int res;
        res = 0;
        for(int i = u; i; i -= i&(-i)){
            res += val[i];
        }
        return res;
    }
};

void read(int &x);
bool cmp(int a, int b);

int main(){
    static int n, m;
    static RawData raw[500005];
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        read(raw[i].x), read(raw[i].y), read(raw[i].v);
        raw[i].id = i;
        raw[i].pre();
    }
    for(int i = 1; i <= n; i++){
        read(raw[i].e);
    }
    sort(raw+1, raw+1+n, RawData::cmp);
    static long long res;
    static int ans[500005], sum[500005];
    for(int i = 1; i <= n; i++){
        static vector<Node> v;
        if(raw[i+1].y != raw[i].y){
            v.emplace_back(raw[i].x, true, raw[i].id, i), v.emplace_back(raw[i].l, false, raw[i].id, i);
            sort(v.begin(), v.end(), Node::cmp);
            static int j1, y1[500005], j2, y2[500005];
            static Tree tr1, tr2;
            j1 = 0, j2 = 0;
            for(auto &now : v){
                if(now.flag){
                    j1++;
                    tr1.add(j1, 1);
                    y1[now.id] = j1;
                }else{
                    j2++;
                    tr2.add(j2, 1);
                    y2[now.id] = j2;
                }
            }
            for(auto &now : v){
                if(!now.flag){
                    sum[now.id] += tr1.query(y1[now.id]-1);
                    tr1.add(y1[now.id], -1);
                }else{
                    sum[now.id] += tr2.query(y2[now.id]-1);
                    tr2.add(y2[now.id], -1);
                }
            }
            v.clear();
        }else{
            v.emplace_back(raw[i].x, true, raw[i].id, i), v.emplace_back(raw[i].l, false, raw[i].id, i);
        }
    }
    for(int i = 1; i <= n; i++){
        static int p;
        p = raw[i].id;
        res += sum[p];
        ans[p] = min(sum[p], raw[i].e);
    }
    sort(ans+1 ,ans+n+1, cmp);
    for(int i = 1; i <= m; i++){
        res -= ans[i];
    }
    printf("%lld", res);
}

bool cmp(int a, int b){
    return a>b;
}

void read(int &x){
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