//
// Created by kibi on 2022/10/3.
//
#include <bits/stdc++.h>
using namespace std;
const int Mx = (1<<30);
int n, q, a[200005];
struct Tree{
    int l, r, ls, rs, s/*, tag, lp, rp*/;
}tr[800005];
//struct node{
//    int num, lp, rp;
//};

void read(int &x);
void readAi();
void build(int u, int l, int r);
void update(int u, int v, int p);
int query(int u, int l, int r);

int main(){
    //    freopen("t.out", "w", stdout);
    //    freopen("t.in", "r", stdin);
    read(n), read(q);
    readAi();
    while(q--){
        int opt;
        read(opt);
        if(opt == 1){
            int p, k;
            read(p), read(k);
            if(k < 0 && a[p] > 0 || a[p] < 0 && k > 0){
                //                update(1, (a[p]>0)?1:-1, p);
                update(1, (a[p]>0)?1:0, p);
            }
            a[p] = k;
        }else{
            int l, r;
            read(l), read(r);
            int res = query(1, l, r);
            int num = res;
            //            int lp = res.lp, rp = res.rp;
            long long ans;
            if(num % 2 == 0){
                if(r-l+1>30){
                    ans = -1;
                }else{
                    ans = 1;
                    for(int i = l; i <= r; i++){
                        ans = ans * a[i];
                        if(ans > Mx || -ans > Mx){
                            ans = -1;
                            break;
                        }
                    }
                }
            }
            else{

                int lp = -1, rp = -1;
                for(int i = l, mxi = min(l+30, r); i <= mxi; i++){
                    if(a[i] < 0){
                        lp = i;
                        break;
                    }
                }
                for(int i = r, mni = max(r-30, l); i >= mni; i--){
                    if(a[i] < 0){
                        rp = i;
                        break;
                    }
                }
                if(lp == -1 || rp == -1){
                    ans = -1;
                }else {
                    int l1 = l, r1 = rp - 1, l2 = lp + 1, r2 = r;
                    if (max(r1 - l1 + 1, r2 - l2 + 1) > 30) {
                        ans = -1;
                    } else {
                        ans = 1;
                        for (int i = l1; i <= r1; i++) {
                            ans = ans * a[i];
                            if (ans > Mx || -ans > Mx) {
                                ans = -1;
                                break;
                            }
                        }
                        if (ans != -1) {
                            long long tem = 1;
                            for (int i = l2; i <= r2; i++) {
                                tem = tem * a[i];
                                if (tem > Mx || -tem > Mx) {
                                    ans = -1;
                                    break;
                                }
                            }
                            ans = ans > 0 ? max(ans, tem) : ans;
                        }
                    }
                }
            }
            if(ans == -1){
                printf("Too large\n");
            }else{
                printf("%lld\n", ans);
            }
        }
    }
    //    fclose(stdout);
    //    fclose(stdin);
}

void readAi() {
    //    int t1[200005];
    //    t1[0] = 0;
    for(int i = 1; i <= n; i++){
        read(a[i]);
        //        t1[i] = t1[i-1] + (a[i]<0);
    }
    build(1, 1, n);
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

inline void pushUp(int u){
    tr[u].s = tr[tr[u].ls].s + tr[tr[u].rs].s;
    //    tr[u].lp = min(tr[tr[u].ls].lp, tr[tr[u].rs].lp);
    //    tr[u].rp = max(tr[tr[u].ls].rp, tr[tr[u].rs].rp);
}

//inline void pushDown(int u){
//    if(tr[u].tag){
//        tr[tr[u].ls].tag += tr[u].tag;
//        tr[tr[u].rs].tag += tr[u].tag;
//    }
//}

void build(int u, int l, int r){
    tr[u].l = l, tr[u].r = r/*, tr[u].tag = 0*/;
    if(l == r){
        tr[u].s = (a[l] < 0);
        //        tr[u].lp = tr[u].rp = tr[u].s > 0 ? -1 : l;
        //        tr[u].lp = tr[u].lp < 0 ? (int)1e9 : tr[u].lp;
        return ;
    }
    int mid = (l+r)/2;
    tr[u].ls = u*2, tr[u].rs = u*2+1;
    build(tr[u].ls, l, mid);
    build(tr[u].rs, mid+1, r);
    pushUp(u);
}

void update(int u, int v, int p){
    if(tr[u].l == tr[u].r){
        tr[u].s = v;
        return ;
    }
    if(tr[tr[u].ls].r >= p){
        update(tr[u].ls, v, p);
    }else{
        update(tr[u].rs, v, p);
    }
    pushUp(u);
}

int query(int u, int l, int r){
    if(tr[u].l >= l && tr[u].r <= r){
        return tr[u].s;
    }
    int res = 0;
    if(tr[tr[u].ls].r >= l){
        res += query(tr[u].ls, l, r);
    }
    if(tr[tr[u].rs].l <= r){
        res += query(tr[u].rs, l, r);
    }
    return res;
}