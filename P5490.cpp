//
// Created by kibi on 2021/8/24.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
struct node{
    ll y1,y2,x,f;
};
struct seg{
    ll l,r,sum,len;
};
node a[1000005];
seg tr[4000005];
ll d[1000005];
bool cmp(node a, node b){
    return a.x<b.x;
}
void build(ll x, ll l, ll r){
    tr[x].l = l;
    tr[x].r = r;
    tr[x].sum = tr[x].len = 0;
    if(l == r)return;
    ll mid = (l+r)/2;
    build(x<<1, l, mid);
    build(x<<1|1, mid+1, r);
}
void pushup(ll x){
    int l = tr[x].l, r = tr[x].r;
    if(tr[x].sum){
        tr[x].len = d[r+1] - d[l];
    }else{
        tr[x].len = tr[x*2].len + tr[x*2+1].len;
    }
}
void change(ll x, ll l, ll r, ll c){
    if(d[tr[x].r+1] <= l||r <= d[tr[x].l]){
        return;
    }
    if(l <= d[tr[x].l] && d[tr[x].r+1] <= r){
        tr[x].sum += c;
        pushup(x);
        return;
    }
    change(x*2, l, r, c);
    change(x*2+1, l, r, c);
    pushup(x);
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        int x1,x2,y1,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        d[i*2-1] = y1;
        d[i*2] = y2;
        a[i*2-1] = {y1,y2,x1,1};
        a[i*2] = {y1,y2,x2,-1};
    }
    sort(a+1, a+1+2*n, cmp);
    sort(d +1, d +1+2*n);
    ll to = unique(d+1, d+2*n+1) - d - 1;
    n*=2;
    build(1, 1, to-1);
    ll ans = 0;
    for(int i = 1; i < n; i++){
        change(1, a[i].y1, a[i].y2, a[i].f);
        ans += tr[1].len * (a[i+1].x - a[i].x);
    }
    printf("%lld", ans);
}

// 2023/9/28

/*
 *

 #include <bits/stdc++.h>
using namespace std;

int main(){

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
   };

   class Line{
   public:
       int l, r, y;
       bool left;

       static bool cmp(const Line &a, const Line &b){
           return a.y == b.y ? a.left : a.y < b.y;
       }
   };

   auto read = Tools::read;

   int n;
   read(n);

   static Line line[2 * N + 5];
   static int pre_x[2 * N + 5];
   for(int i = 1; i <= n; i++){
       static int x1, y1, x2, y2;
       read(x1), read(y1), read(x2), read(y2);
       line[(i << 1) - 1] = {x1, x2, y1, true};
       line[i << 1] = {x1, x2, y2, false};
       pre_x[(i << 1) - 1] = x1;
       pre_x[i << 1] = x2;
   }

   sort(pre_x + 1, pre_x + 2 * n + 1);
   sort(line + 1, line + 2 * n + 1, Line::cmp);

   static map<int, int> to_mp;
   static int cnt_of_mp, segTree_data[2 * N + 5];
   to_mp[pre_x[1]] = ++cnt_of_mp;
   for(int i = 2; i <= 2 * n; i++){
       if(pre_x[i] != pre_x[i - 1]) {
           to_mp[pre_x[i]] = ++cnt_of_mp;
           segTree_data[cnt_of_mp - 1] = pre_x[i] - pre_x[i - 1];
       }
   }

   class SegTree{
       class Node{
       public:
           int l, r, len, sum, flag;
           Node *ls, *rs;
       };
       Node node[4 * 2 * N + 5]{};

       void build(Node *u, int l, int r, const int *data){
           static int cnt = 1;
           u->l = l, u->r = r;
           if(l == r){
               u->len = data == nullptr ? 0 : data[l];
               return;
           }

           int mid = (l + r) >> 1;
           u->ls = &node[++cnt], u->rs = &node[++cnt];
           build(u->ls, l, mid, data);
           build(u->rs, mid + 1, r, data);
           u->len = u->ls->len + u->rs->len;
       }

       void modify(Node *u, int l, int r, bool val){
           if(l <= u->l && u->r <= r){
               u->flag += val ? 1 : -1;
               if(!u->flag){
                   if(u->l == u->r){
                       u->sum = 0;
                   }else {
                       u->sum = u->ls->sum + u->rs->sum;
                   }
               }else{
                   u->sum = u->len;
               }
               return;
           }

           //            push_down(u);

           if(l <= u->ls->r){
               modify(u->ls, l, r, val);
           }
           if(r >= u->rs->l){
               modify(u->rs, l, r, val);
           }

           u->sum = u->flag ? u->len : u->ls->sum + u->rs->sum;
       }
   public:
       SegTree(int n, const int *data){
           build(&node[1], 1, n, data);
       }

       int query_(){
           return node[1].sum;
       }

       void modify(int l, int r, bool val){
           modify(&node[1], l, r, val);
       }
   };

   static SegTree tree(cnt_of_mp - 1, segTree_data);

   int last = line[1].y;
   tree.modify(to_mp[line[1].l], to_mp[line[1].r] - 1, line[1].left);

   long long ans = 0;
   for(int i = 2; i <= 2 * n; i++){
       if(line[i].y != last){
           ans += (long long)(line[i].y - last) * tree.query_();
       }
       tree.modify(to_mp[line[i].l], to_mp[line[i].r] - 1, line[i].left);
       last = line[i].y;
   }

   printf("%lld\n", ans);

}

 *
 * */