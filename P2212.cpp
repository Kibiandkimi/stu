//
// Created by kibi on 2022/8/27.
//
//vector - 3.73s (TLE*2)
//vector+o2 - 0.813s
//array - 3.19s (TLE*1)
//array+(j=i+1) - 1.76s
//总结吸氧大法好(bushi)
#include <bits/stdc++.h>
using namespace std;
int xy[2005][2], n, c;

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c=='-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}
void foo(int &x, int &y) { read(x),read(y); }

struct node{
    node(int tu, int tv, int tw){
        u = tu, v = tv, w = tw;
    }
    void get(int &tu, int &tv, int &tw)const{
        tu = u, tv = v, tw = w;
    }
    int u, v, w;
};
vector<node> edge;

bool cmp(node a, node b){
    return a.w < b.w;
}

int b[2005];
int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}

int main(){
    foo(n, c);
    for(int i = 1; i <= n; i++){
        //        int x, y;
        foo(xy[i][0], xy[i][1]);
    }
    for(int i = 1; i <= n; i++){
        b[i] = i;
        for(int j = 1; j <= n; j++){
            int dis = pow(xy[i][0]-xy[j][0], 2) + pow(xy[i][1]-xy[j][1], 2);
            if(dis >= c){
                edge.emplace_back(i, j, dis);
            }
        }
    }
    sort(edge.begin(), edge.end(), cmp);
    int se = edge.size(), ans = 0, cnt = n-1;
    for(int i = 0; i < se && cnt; i++){
        int u, v, w;
        edge[i].get(u, v, w);
        if(find(u) != find(v)){
            cnt--;
            ans += w;
            b[find(u)] = find(v);
        }
    }
    if(cnt){
        printf("-1");
    }else{
        printf("%d", ans);
    }
}

namespace t {
#include <bits/stdc++.h>
    //using namespace std;
    int xy[2005][2], n, c, se;

    void read(int &x) {
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w *= -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }
    void foo(int &x, int &y) { read(x), read(y); }

    struct node {
        explicit node(int tu = 0, int tv = 0, int tw = 0) {
            u = tu, v = tv, w = tw;
        }
        void get(int &tu, int &tv, int &tw) const {
            tu = u, tv = v, tw = w;
        }
        int u, v, w;
    };
    //vector<node> edge;
    node edge[4000005];

    bool cmp(node a, node b) {
        return a.w < b.w;
    }

    int b[2005];
    int find(int x) {
        if (x != b[x]) {
            return b[x] = find(b[x]);
        }
        return x;
    }

    int main() {
        foo(n, c);
        for (int i = 1; i <= n; i++) {
            //        int x, y;
            foo(xy[i][0], xy[i][1]);
        }
        for (int i = 1; i <= n; i++) {
            b[i] = i;
            for (int j = 1; j <= n; j++) {
                int dis = pow(xy[i][0] - xy[j][0], 2) + pow(xy[i][1] - xy[j][1], 2);
                if (dis >= c) {
                    edge[se++] = node(i, j, dis);
                }
            }
        }
        sort(edge, edge + se, cmp);
        int ans = 0, cnt = n - 1;
        for (int i = 0; i < se && cnt; i++) {
            int u, v, w;
            edge[i].get(u, v, w);
            if (find(u) != find(v)) {
                cnt--;
                ans += w;
                b[find(u)] = find(v);
            }
        }
        if (cnt) {
            printf("-1");
        } else {
            printf("%d", ans);
        }
    }
}

namespace t2{
#include <bits/stdc++.h>
    using namespace std;
    int xy[2005][2], n, c, se;

    void read(int &x){
        int s = 0, w = 1, c = getchar();
        while(c<'0'||'9'<c){
            if(c=='-'){
                w *= -1;
            }
            c = getchar();
        }
        while('0'<=c&&c<='9'){
            s = s*10 + c-'0';
            c = getchar();
        }
        x = s*w;
    }
    void foo(int &x, int &y) { read(x),read(y); }

    struct node{
        explicit node(int tu = 0, int tv = 0, int tw = 0){
            u = tu, v = tv, w = tw;
        }
        void get(int &tu, int &tv, int &tw)const{
            tu = u, tv = v, tw = w;
        }
        int u, v, w;
    };
    //vector<node> edge;
    node edge[4000005];

    bool cmp(node a, node b){
        return a.w < b.w;
    }

    int b[2005];
    int find(int x){
        if(x != b[x]){
            return b[x] = find(b[x]);
        }
        return x;
    }

    int main(){
        foo(n, c);
        for(int i = 1; i <= n; i++){
            //        int x, y;
            foo(xy[i][0], xy[i][1]);
        }
        for(int i = 1; i <= n; i++){
            b[i] = i;
            for(int j = i+1; j <= n; j++){
                int dis = pow(xy[i][0]-xy[j][0], 2) + pow(xy[i][1]-xy[j][1], 2);
                if(dis >= c){
                    edge[se++] = node(i, j, dis);
                }
            }
        }
        sort(edge, edge+se, cmp);
        int ans = 0, cnt = n-1;
        for(int i = 0; i < se && cnt; i++){
            int u, v, w;
            edge[i].get(u, v, w);
            if(find(u) != find(v)){
                cnt--;
                ans += w;
                b[find(u)] = find(v);
            }
        }
        if(cnt){
            printf("-1");
        }else{
            printf("%d", ans);
        }
    }
}