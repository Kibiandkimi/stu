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
    static int ans[500005];
    for(int i = 1; i <= n; i++){
        static vector<Node> v;
        if(raw[i+1].y != raw[i].y){
            v.emplace_back(raw[i].x, true, raw[i].id, i), v.emplace_back(raw[i].l, false, raw[i].id, i);
            sort(v.begin(), v.end(), Node::cmp);
            static int sum[1000005], val[1000005], j, pos[1000005], fuck;
            j = 0;
            fuck = 0;
            for(auto &now : v){
                if(now.flag) {
                    if(pos[now.id]){
                        fuck--;
                    }else {
                        ++j;
                        sum[j] = sum[j - 1] + 1;
                        val[j] = val[j - 1] + 1;
                        pos[now.id] = j;
                    }
                }else{
                    static int tem;
                    if(!pos[now.id]){
                        fuck++;
                        pos[now.id] = j;
                    }else {
                        tem = (sum[j] - sum[pos[now.id]]) - (val[j] - val[pos[now.id]]) + fuck;
                        res += tem > 0 ? tem : -tem;
                        ans[now.id] = min(raw[now.pos].e, tem > 0 ? tem : -tem);
                        ++j;
                        val[j] = val[j - 1] - 1;
                        sum[j] = sum[j - 1];
                    }
                }
            }
            v.clear();
        }else{
            v.emplace_back(raw[i].x, true, raw[i].id, i), v.emplace_back(raw[i].l, false, raw[i].id, i);
        }
    }
    sort(ans+1 ,ans+n+1, cmp);
    for(int i = 1; i <= m; i++){
        res -= ans[i];
    }
    printf("%lld", res*2);
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