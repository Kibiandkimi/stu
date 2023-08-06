//
// Created by kibi on 23-7-17.
//

#include <bits/stdc++.h>
using namespace std;

const int N = 300000, T = 5000;

void read(int &x);

class Thing{
public:
    int s, t, x, c, id;
    bool operator < (const Thing& other) const{
        return c > other.c;
    }
};

int main(){
    int n;
    long long ans = 0;
    static Thing thing[N+5];
    static vector<int> s[T+5], t[T+5];
    static long long f[T*2+5];
    static bool vis[N+5];

    read(n);

    for(int i = 1; i <= n; i++){
        read(thing[i].s), read(thing[i].t), read(thing[i].x), read(thing[i].c);
        thing[i].id = i;
        s[thing[i].s].push_back(i);
        t[thing[i].t].push_back(i);
    }

    static priority_queue<pair<int, int> > q[T+5];
    for(int i = 1; i <= T; i++){
        f[i] = max(f[i], f[i-1]);
        for(auto j : s[i]){
            q[thing[j].x].emplace(thing[j].c, thing[j].id);
        }
        for(int j = 1; j <= T; j++) {
            while (!q[j].empty() && vis[q[j].top().second]) {
                q[j].pop();
            }
            if (q[j].empty()) {
                continue;
            }
            ans = max(ans, f[i+j] = max(f[i+j], f[i] + q[j].top().first));
        }
        for(auto j : t[i]){
            vis[j] = true;
        }
    }
    printf("%lld\n", ans);
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

//TODO fix this
/*
 * #include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 3e5 + 10; // 定义常量表示最大事情个数
const int MAXT = 5000 + 10; // 定义常量表示最大时间范围

struct Thing { // 定义结构体表示每一件事
    int s, t, x, c, id; // 开始时间、结束时间、所需时间、收益、编号
    bool operator < (const Thing& other) const { // 定义比较运算符按照收益从大到小排序
        return c > other.c;
    }
};

vector<int> s[MAXT]; // 定义数组存储每个开始时间对应的事情编号
vector<int> t[MAXT]; // 定义数组存储每个结束时间对应的事情编号
Thing things[MAXN]; // 定义数组存储所有的事情
bool vis[MAXN]; // 定义数组表示每一件事是否已经无法做了
priority_queue<Thing> q[MAXT]; // 定义优先队列数组存储每个所需时间对应的事情
long long f[MAXT * 2]; // 定义数组表示每个时刻的最大钱数

int main() {
    ios::sync_with_stdio(false); // 加速输入输出流
    cin.tie(nullptr); // 解除cin和cout的绑定，防止刷新缓冲区
    int n; // 定义变量表示事情个数
    cin >> n; // 输入事情个数
    for (int i = 1; i <= n; i++) {
        cin >> things[i].s >> things[i].t >> things[i].x >> things[i].c; // 输入每一件事的信息
        things[i].id = i; // 记录每一件事的编号
        s[things[i].s].push_back(i); // 将每一件事的编号插入到对应的开始时间数组中
        t[things[i].t].push_back(i); // 将每一件事的编号插入到对应的结束时间数组中
    }
    long long ans = 0; // 定义变量表示最终答案
    for (int i = 1; i <= MAXT - 1; i++) { // 枚举每个时刻
        f[i] = max(f[i], f[i - 1]); // 初始化为不做任何事的情况
        for (const auto& j : s[i]) { // 遍历当前时刻开始的所有事情
            q[things[j].x].emplace(things[j]); // 将每一件事插入到对应的所需时间的优先队列中
        }
        for (int x = 1; x <= MAXT - 1; x++) { // 枚举所需时间
            while (!q[x].empty() && vis[q[x].top().id]) {
                q[x].pop(); // 如果当前优先队列不为空，并且队首的事情已经无法做了，就将其弹出队列
            }
            if (q[x].empty()) { // 如果当前优先队列为空，就跳过这个所需时间
                continue;
            }
            ans = max(ans, f[i + x] = max(f[i + x], f[i] + q[x].top().c));
            // 如果当前优先队列不为空，就用前一个时刻加上队首的收益更新当前时刻的最大钱数，并更新最终答案
        }
        for (const auto& j : t[i]) { // 遍历当前时刻结束的所有事情
            vis[j] = true; // 将每一件事标记为已经无法做了
        }
    }
    cout << ans << endl; // 输出最终答案
    return 0;
}
*/