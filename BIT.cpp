/*
 * 树状数组部分
 */
// --- 一维树状数组 ----------------------------
int lowbit(int x) { return x & -x; }

const int N = 100005;
int n, a[N], b[N];
// a[p] += v
void update(int p, int v) {
    while(p <= n) {
        b[p] += v;
        p += lowbit(p);
    }
}
// query a[1:p]
int query(int p) {
    int ret = 0;
    while(p > 0) {
        ret += b[p];
        p -= lowbit(p);
    }
    return ret;
}

// --- 二维树状数组 ----------------------------
int n, m, c[1005][1005];
// a[x][y] += v
void update(int x, int y, int v) {
    for(int i = x; i <= n; i += lowbit(i))
        for(int j = y; j <= m; j += lowbit(j))
            c[i][j] += v;
}
// sum[1:x][1:y]
int query(int x, int y) {
    int ret = 0;
    for(int i = x; i; i -= lowbit(i))
        for(int j = y; j; j -= lowbit(j))
            ret += c[i][j];
        return ret;
}