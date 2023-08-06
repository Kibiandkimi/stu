//
// Created by kibi on 23-7-17.
//

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

void read(int &x);

class Segment{
public:
    int l, r;
};

int mx[N+5], mn[N+5], to[N*10+5];
int tpa, tpb, now;
Segment A[N*8+5], B[N*8+5];

void del_a(int l, int r);
void del_b(int l, int r);
void add_a(int l, int r);
void add_b(int l, int r);

int main(){

    int n, m, v, tot = 0;
    long long res = 0;
    int pw[10];
    static int a[10][N+5], c[N*10+5], _mn[256][N+5], _mx[256][N+5], sa[N+5], sb[N+5];
    static unordered_map<int, int> mp;

    pw[0] = 1;
    for(int i = 1; i <= 8; i++){
        pw[i] = pw[i-1] * i;
    }

    read(n), read(m), read(v);

    for(int i = 0; i < n; i++){
        for(int j = 1; j <= m; j++){
            read(a[i][j]);
            c[i*m+j] = a[i][j];
        }
    }

    sort(c+1, c+1+n*m);

    for(int i = 1; i <= n*m; i++){
        if(!mp.count(c[i])){
            mp[c[i]] = ++tot;
        }
        if(mp.count(c[i] ^ v)){
            int t1 = mp[c[i] ^ v], t2 = mp[c[i]];
            to[t1] = t2, to[t2] = t1;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 1; j <= m; j++){
            a[i][j] = mp[a[i][j]];
        }
    }

    for(int i = 1; i <= m; i++){
        _mn[0][i] = 1e9;
    }
    for(int i = 1; i < (1 << n); ++i){
        for(int j = 0; j < n; j++){
            if(i >> j & 1){
                for(int k = 1; k <= m; k++){
                    _mx[i][k] = max(_mx[i ^ (1<<j)][k], a[j][k]);
                    _mn[i][k] = min(_mn[i ^ (1<<j)][k], a[j][k]);
                }
                break;
            }
        }
        for(int j = 1; j <= m; j++){
            mx[j] = _mx[i][j];
            mn[j] = _mn[i][j];
        }
        tpa = tpb = 0;
        long long ans = 0;
        now = 0;
        for(int j = 1; j <= m; j++){
            while(tpa && mx[sa[tpa]] <= mx[j]){
                del_a(sa[tpa - 1] + 1, sa[tpa]);
                tpa--;
            }
            while(tpb && mn[sb[tpb]] >= mn[j]){
                del_b(sb[tpb - 1] + 1, sb[tpb]);
                tpb--;
            }
            sa[++tpa] = j;
            add_a(sa[tpa-1]+1, j);
            sb[++tpb] = j;
            add_b(sb[tpb-1]+1, j);
            ans += now;
        }
        for(int j = 1; j <= tpa; j++){
            A[mx[sa[j]]].l = 0;
        }
        for(int j = 1; j <= tpb; j++){
            B[mn[sb[j]]].l = 0;
        }
        int cnt = __builtin_popcount(i);
        res += ans * (n - cnt + 1) * pw[cnt] * pw[n-cnt];
    }

    printf("%lld\n", res);
}

void del_a(int l, int r){
    int val = to[mx[r]];
    if(B[val].l){
        Segment t = B[val];
        int _l = t.l, _r = t.r;
        now -= max(0, min(r, _r) - max(l, _l) + 1);
    }
    A[mx[r]].l = 0;
}

void add_a(int l, int r){
    int val = to[mx[r]];
    if(B[val].l){
        Segment t = B[val];
        int _l = t.l, _r = t.r;
        now += max(0, min(r, _r) - max(l, _l) + 1);
    }
    A[mx[r]] = {l, r};
}

void del_b(int l, int r){
    int val = to[mn[r]];
    if(A[val].l){
        Segment t = A[val];
        int _l = t.l, _r = t.r;
        now -= max(0, min(r, _r) - max(l, _l) + 1);
    }
    B[mn[r]].l = 0;
}

void add_b(int l, int r){
    int val = to[mn[r]];
    if(A[val].l){
        Segment t = A[val];
        int _l = t.l, _r = t.r;
        now += max(0, min(r, _r) - max(l, _l) + 1);
    }
    B[mn[r]] = {l, r};
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

/*

#include <bits/stdc++.h>
using namespace std;
void read(int &x) {
    char ch = getchar();
    x = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
}
const int N = 1e5 + 5;
int n, m, X, a[9][N], mx[256][N], mn[256][N], pw[10], tot, c[N * 8];
struct seg {
    int l, r;
} A[N * 8], B[N * 8];
unordered_map<int, int> mp;
int sa[N], tpa, sb[N], tpb, MX[N], MN[N];
long long res = 0;
int now, to[N * 8];
void dela(int l, int r) {
    int val = to[MX[r]];
    if (B[val].l) {
        seg t = B[val];
        int L = t.l, R = t.r;
        now -= max(0, min(r, R) - max(l, L) + 1);
    }
    A[MX[r]].l = 0;
}
void adda(int l, int r) {
    int val = to[MX[r]];
    if (B[val].l) {
        seg t = B[val];
        int L = t.l, R = t.r;
        now += max(0, min(r, R) - max(l, L) + 1);
    }
    A[MX[r]] = (seg){l, r};
}
void delb(int l, int r) {
    int val = to[MN[r]];
    if (A[val].l) {
        seg t = A[val];
        int L = t.l, R = t.r;
        now -= max(0, min(r, R) - max(l, L) + 1);
    }
    B[MN[r]].l = 0;
}
void addb(int l, int r) {
    int val = to[MN[r]];
    if (A[val].l) {
        seg t = A[val];
        int L = t.l, R = t.r;
        // if (r == m) printf ("666 %d %d %d %d\n", l, r, L, R);
        now += max(0, min(r, R) - max(l, L) + 1);
    }
    B[MN[r]] = (seg){l, r};
}
signed main() {
    pw[0] = 1;
    for (int i = 1; i <= 8; ++i) pw[i] = pw[i - 1] * i;
    read(n), read(m), read(X);
    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= m; ++j) read(a[i][j]), c[i * m + j] = a[i][j];
    sort(c + 1, c + n * m + 1);
    for (int i = 1; i <= n * m; ++i) {
        if (!mp.count(c[i])) mp[c[i]] = ++tot;
        if (mp.count(c[i] ^ X)) {
            int ta = mp[c[i] ^ X], tb = mp[c[i]];
            to[ta] = tb, to[tb] = ta;
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= m; ++j) a[i][j] = mp[a[i][j]];
    for (int i = 1; i <= m; ++i) mn[0][i] = 1e9;
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j)
            if (i >> j & 1) {
                for (int k = 1; k <= m; ++k)
                    mx[i][k] = max(mx[i ^ (1 << j)][k], a[j][k]);
                for (int k = 1; k <= m; ++k)
                    mn[i][k] = min(mn[i ^ (1 << j)][k], a[j][k]);
                break;
            }
        for (int j = 1; j <= m; ++j) MX[j] = mx[i][j], MN[j] = mn[i][j];
        tpa = tpb = 0;
        long long ans = 0;
        now = 0;
        for (int j = 1; j <= m; ++j) {
            while (tpa && MX[sa[tpa]] <= MX[j]) {
                dela(sa[tpa - 1] + 1, sa[tpa]);
                --tpa;
            }
            while (tpb && MN[sb[tpb]] >= MN[j]) {
                delb(sb[tpb - 1] + 1, sb[tpb]);
                --tpb;
            }
            sa[++tpa] = j;
            adda(sa[tpa - 1] + 1, j);
            sb[++tpb] = j;
            addb(sb[tpb - 1] + 1, j);
            ans += now;
        }
        for (int j = 1; j <= tpa; ++j) A[MX[sa[j]]].l = 0;
        for (int j = 1; j <= tpb; ++j) B[MN[sb[j]]].l = 0;
        int cnt = __builtin_popcount(i);
        res += ans * (n - cnt + 1) * pw[cnt] * pw[n - cnt];
    }
    printf("%lld\n", res);
    return 0;
}

*/


/*
 * #include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MAXN = 3e5 + 10; // 定义常量表示最大事情个数
const int MAXT = 5000 + 10; // 定义常量表示最大时间范围

struct Segment { // 定义结构体表示一个区间
    int l, r; // 左端点和右端点
};

int n, m, X; // 定义变量表示矩形的行数、列数和目标值
int a[9][MAXN]; // 定义数组存储矩形的元素
int mx[256][MAXN]; // 定义数组存储每个子集对应的每列的最大值
int mn[256][MAXN]; // 定义数组存储每个子集对应的每列的最小值
int pw[10]; // 定义数组存储阶乘
int tot; // 定义变量表示离散化后的元素个数
int c[MAXN * 8]; // 定义数组存储所有的元素
Segment A[MAXN * 8], B[MAXN * 8]; // 定义数组存储每个值作为最大值或最小值的区间
unordered_map<int, int> mp; // 定义哈希表存储每个元素对应的离散化后的值
int sa[MAXN], tpa, sb[MAXN], tpb, MX[MAXN], MN[MAXN]; // 定义单调栈和临时变量
long long res = 0; // 定义变量表示最终答案
int now, to[MAXN * 8]; // 定义变量表示当前合法子矩形的个数和每个值对应的异或目标值

// 删除一个区间对当前合法子矩形个数的影响
void dela(int l, int r) {
    int val = to[MX[r]]; // 找到当前最大值对应的最小值
    if (B[val].l) { // 如果存在这样的区间
        Segment t = B[val]; // 取出这个区间
        int L = t.l, R = t.r;
        now -= max(0, min(r, R) - max(l, L) + 1); // 减去这个区间和当前区间的交集长度
    }
    A[MX[r]].l = 0; // 清空当前区间
}

// 添加一个区间对当前合法子矩形个数的影响
void adda(int l, int r) {
    int val = to[MX[r]]; // 找到当前最大值对应的最小值
    if (B[val].l) { // 如果存在这样的区间
        Segment t = B[val]; // 取出这个区间
        int L = t.l, R = t.r;
        now += max(0, min(r, R) - max(l, L) + 1); // 加上这个区间和当前区间的交集长度
    }
    A[MX[r]] = (Segment){l, r}; // 更新当前区间
}

// 删除一个区间对当前合法子矩形个数的影响，同上，只是方向相反
void delb(int l, int r) {
    int val = to[MN[r]];
    if (A[val].l) {
        Segment t = A[val];
        int L = t.l, R = t.r;
        now -= max(0, min(r, R) - max(l, L) + 1);
    }
    B[MN[r]].l = 0;
}

// 添加一个区间对当前合法子矩形个数的影响，同上，只是方向相反
void addb(int l, int r) {
    int val = to[MN[r]];
    if (A[val].l) {
        Segment t = A[val];
        int L = t.l, R = t.r;
        now += max(0, min(r, R) - max(l, L) + 1);
    }
    B[MN[r]] = (Segment){l, r};
}

int main() {
    ios::sync_with_stdio(false); // 加速输入输出流
    cin.tie(nullptr); // 解除cin和cout的绑定，防止刷新缓冲区
    pw[0] = 1;
    for (int i = 1; i <= 8; ++i) {
        pw[i] = pw[i - 1] * i;
    }
    cin >> n >> m >> X; // 输入矩形的行数、列数和目标值
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j]; // 输入矩形的元素
            c[i * m + j] = a[i][j]; // 将元素存入数组中
        }
    }
    sort(c + 1, c + n * m + 1); // 对所有的元素排序
    for (int i = 1; i <= n * m; ++i) {
        if (!mp.count(c[i])) mp[c[i]] = ++tot; // 如果当前元素没有被离散化过，就给它分配一个新的值
        if (mp.count(c[i] ^ X)) { // 如果当前元素异或目标值的结果也被离散化过，就记录它们之间的对应关系
            int ta = mp[c[i] ^ X], tb = mp[c[i]];
            to[ta] = tb, to[tb] = ta;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            a[i][j] = mp[a[i][j]]; // 将矩形中的元素替换为离散化后的值
        }
    }
    for (int i = 1; i <= m; ++i) mn[0][i] = 1e9; // 初始化每列的最小值为一个很大的数
    for (int i = 1; i < (1 << n); ++i) { // 枚举每个子集，即每个子矩形用到的行
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) { // 找到第一个在子集中的行
                for (int k = 1; k <= m; ++k) {
                    mx[i][k] = max(mx[i ^ (1 << j)][k], a[j][k]); // 更新每列的最大值为当前行和之前子集中的最大值中较大者
                }
                for (int k = 1; k <= m; ++k) {
                    mn[i][k] = min(mn[i ^ (1 << j)][k], a[j][k]); // 更新每列的最小值为当前行和之前子集中的最小值中较小者
                }
                break;
            }
        }
        for (int j = 1; j <= m; ++j) MX[j] = mx[i][j], MN[j] = mn[i][j]; // 将每列的最大值和最小值存入临时变量中
        tpa = tpb = 0; // 初始化单调栈为空
        long long ans = 0;
        now = 0;
        for (int j = 1; j <= m; ++j) { // 枚举每列
            while (tpa && MX[sa[tpa]] <= MX[j]) {
                dela(sa[tpa - 1] + 1, sa[tpa]); // 如果当前最大值比单调栈顶的最大值大，就删除单调栈顶对应的区间对答案的贡献，并出栈
                --tpa;
            }
            while (tpb && MN[sb[tpb]] >= MN[j]) {
                delb(sb[tpb - 1] + 1, sb[tpb]); // 如果当前最小值比单调栈顶的最小值小，就删除单调栈顶对应的区间对答案的贡献，并出栈
                --tpb;
            }
            sa[++tpa] = j;
            adda(sa[tpa - 1] + 1, j); // 如果当前最大值比单调栈顶的最大值大，就将当前列入栈，并添加当前区间对答案的贡献
            sb[++tpb] = j;
            addb(sb[tpb - 1] + 1, j); // 如果当前最小值比单调栈顶的最小值小，就将当前列入栈，并添加当前区间对答案的贡献
            ans += now; // 将当前合法子矩形的个数累加到答案中
        }
        for (int j = 1; j <= tpa; ++j) A[MX[sa[j]]].l = 0; // 清空每个最大值对应的区间
        for (int j = 1; j <= tpb; ++j) B[MN[sb[j]]].l = 0; // 清空每个最小值对应的区间
        int cnt = __builtin_popcount(i); // 计算当前子集中有多少行
        res += ans * (n - cnt + 1) * pw[cnt] * pw[n - cnt]; // 计算当前子集对最终答案的贡献，即每个合法子矩形被多少矩形包含
    }
    cout << res << endl; // 输出最终答案
    return 0;
}
*/