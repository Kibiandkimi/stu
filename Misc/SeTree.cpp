/*
 * 线段树部分
 */

// --- 单点加/查、区间查 ---------------------------
const int NN = 1005;
int a[NN], mx[NN << 2], sum[NN << 2], tag[NN << 2];
void update(int x, int L, int R) {
    if(L != R) {
        mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
        sum[x] = sum[x << 1] + sum[x << 1 | 1];
    }
}
void build(int x, int L, int R) {
    if(L == R) {
        mx[x] = a[L];
        sum[x] = a[L];
        return;
    }
    int mid = (L + R) >> 1;
    build(x << 1, L, mid);
    build(x << 1 | 1, mid + 1, R);
    update(x, L, R);
}
// ask for a[p]
int query(int x, int L, int R, int p) {
    pushdown(x, L, R);
    if(L == R) return mx[x];
    int mid = (L + R) >> 1;
    if(p <= mid) return query(x << 1, L, mid, p);
    else return query(x << 1 | 1, mid + 1, R, p);
}
// change a[p] to v
void modify(int x, int L, int R, int p, int v) {
    pushdown(x, L, R);
    if(L == R) {
        mx[x] = sum[x] = v;
        return;
    }
    int mid = (L + R) >> 1;
    if(p <= mid) modify(x << 1, L, mid, p, v);
    else modify(x << 1 | 1, mid + 1, R, p, v);
    update(x, L, R);
}
// ask for max(a[l...r])
int query_mx(int x, int L, int R, int l, int r) {
    pushdown(x, L, R);
    if(l == L && r == R) return mx[x];
    int mid = (L + R) >> 1;
    if(r <= mid) return query_mx(x << 1, L, mid, l, r);
    else if(l > mid) return query_mx(x << 1 | 1, mid + 1, R, l, r);
    else{
        int u = query_mx(x << 1, L, mid, l, mid);
        int v = query_mx(x << 1 | 1, mid + 1, R, mid + 1, r);
        return max(u, v);
    }
}
// ask for sum(a[l...r])
int query_sum(int x, int L, int R, int l, int r) {
    pushdown(x, L, R);
    // cout << L<<" "<<R<<" "<<sum[x]<<" "<<tag[x]<<endl;
    if(l == L && r == R) return sum[x];
    int mid = (L + R) >> 1;
    if(r <= mid) return query_sum(x << 1, L, mid, l, r);
    else if(l > mid) return query_sum(x << 1 | 1, mid + 1, R, l, r);
    else{
        int u = query_sum(x << 1, L, mid, l, mid);
        int v = query_sum(x << 1 | 1, mid + 1, R, mid + 1, r);
        return u + v;
    }
}

// --- 区间加、区间查 ---------------------------
// --- 如果要用上面的 query() 函数，需要加上 pushdown
// UPDATED
void pushdown(int x, int L, int R) {
    if(tag[x] == 0) return;
    int mid = L + R >> 1;
    if(L != R) {
        tag[x << 1] += tag[x];
        mx[x << 1] += tag[x];
        sum[x << 1] += tag[x] * (mid - L + 1);
        tag[x << 1 | 1] += tag[x];
        mx[x << 1 | 1] += tag[x];
        sum[x << 1 | 1] += tag[x] * (R - mid);
    }
    tag[x] = 0;
}
// a[l...r] += v
// UPDATED
void modify(int x, int L, int R, int l, int r, int v) {
    pushdown(x, L, R);
    if(L == l && R == r) {
        tag[x] += v;
        mx[x] += v;
        sum[x] += v * (R - L + 1);
        return;
    }
    int mid = (L + R) >> 1;
    if(r <= mid) modify(x << 1, L, mid, l, r, v);
    else if(l > mid) modify(x << 1 | 1, mid+1, R, l, r, v);
    else{
        modify(x << 1, L, mid, l, mid, v);
        modify(x << 1 | 1, mid+1, R, mid+1, r, v);
    }
    update(x, L, R);
}


// --- 标记永久化 -----------------------
// --- 无需 pushdown -------------------
// --- 注意需修改 update() -------------
// UPDATED
void update(int x, int L, int R) {
    if(L != R) {
        mx[x] = max(mx[x << 1], mx[x << 1 | 1]) + tag[x];
        sum[x] = sum[x << 1] + sum[x << 1 | 1] + tag[x] * (R - L + 1);
    }
}
// UPDATED
void modify(int x, int L, int R, int l, int r, int v) {
    if(L == l && R == r) {
        tag[x] += v;
        sum[x] += v * (R - L + 1);
        mx[x] += v;
        return;
    }
    int mid = (L + R) >> 1;
    if(r <= mid) modify(x << 1, L, mid, l, r, v);
    else if(l > mid) modify(x << 1 | 1, mid+1, R, l, r, v);
    else{
        modify(x << 1, L, mid, l, mid, v);
        modify(x << 1 | 1, mid+1, R, mid+1, r, v);
    }
    update(x, L, R);
}
// UPDATED
int query(int x, int L, int R, int l, int r, int cur) {
    if(l == L && r == R)
        // return mx[x] + cur;
        return sum[x] + cur * (r - l + 1);
    cur += tag[x];
    int mid = (L + R) >> 1;
    if(r <= mid) return query(x << 1, L, mid, l, r, cur);
    else if(l > mid) return query(x << 1 | 1, mid + 1, R, l, r, cur);
    else{
        int u = query(x << 1, L, mid, l, mid, cur);
        int v = query(x << 1 | 1, mid + 1, R, mid + 1, r, cur);
        // return max(u, v);
        return u + v;
    }
}


// --- 双标记 pushdown --------------
// UPDATED
const int P = 1000000007;
long long mul[N << 1], add[N << 1];
void pushdown(int x, int L, int R) {
    if(tag[x] == 0) return;
    int mid = L + R >> 1;
    if(L != R) {
        mul[x << 1] = mul[x << 1] * mul[x] % P;
        add[x << 1] = (add[x << 1] * mul[x] + add[x]) % P;
        sum[x << 1] = (sum[x << 1] * mul[x] + add[x] * (mid - L + 1)) % P;
        mul[x << 1 | 1] = mul[x << 1 | 1] * mul[x] % P;
        add[x << 1 | 1] = (add[x << 1 | 1] * mul[x] + add[x]) % P;
        sum[x << 1 | 1] = (sum[x << 1 | 1] * mul[x] + add[x] * (R - mid)) % P;
    }
    mul[x] = add[x] = 0;
}

/*
 * 可持久化
 */
const int N = 100005;
struct Node{
    int lc, rc, sum;
}a[20 * N];     // log n
int cnt, root[N];
// a[p] = v;
void modify(int& x, int L, int R, int p, int v) {
    a[++cnt] = a[x];
    x = cnt;
    if(L == R) {
        a[x].sum += v;
        return;
    }
    int mid = (L + R) >> 1;
    if(p <= mid) modify(a[x].lc, L, mid, p, v);
    else modify(a[x].rc, mid+1, R, p, v);
    a[x].sum = a[a[x].lc].sum + a[a[x].rc].sum;     // a[0].sum = 0;
}
int query(int x, int L, int R, int l, int r) {
    if(x == 0) return 0;
    if(l == L && r == R) return a[x].sum;
    int mid = (L + R) >> 1;
    if(r <= mid) return query(a[x].lc, L, mid, l, r);
    else if(l > mid) return query(a[x].rc, mid + 1, R, l, r);
    else{
        int u = query(a[x].lc, L, mid, l, mid);
        int v = query(a[x].rc, mid + 1, R, mid + 1, r);
        return u + v;
    }
}
int main() {
    for(int i=1; i<=Q; i++) {
        root[i] = root[i-1];
        modify(root[i], 1, n, a[i], 1);
    }
    query(root[k], 1, n, l, r);
    return 0;
}