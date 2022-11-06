//
// Created by kibi on 2022/11/5.
//
#include <bits/stdc++.h>

namespace Raw {
    using namespace std;

    int a[100005], b[100005];

    //struct Node{
    //	int l, r, ls, rs, mn, mx;
    //};
    //
    //struct Tr{
    //	int *raw;
    //	Node tr[400005];
    //	void build(int u, int l, int r){
    //		tr[u].l = l, tr[u].r = r;
    //		if(l == r){
    //			tr[u].mn = tr[u].mx = raw[l];
    //			return ;
    //		}
    //		int mid = (l+r)/2;
    //		tr[u].ls = u*2;
    //		tr[u].rs = u*2+1;
    //		build(tr[u].ls, l, mid);
    //		build(tr[u].rs, mid+1, r);
    //		tr[u].mx = max(tr[tr[u].ls].mx, tr[tr[u].rs].mx);
    //		tr[u].mn = min(tr[tr[u].ls].mn, tr[tr[u].rs].mn);
    //	}
    //	int queryMx(int u, int l, int r){
    //		if(l <= tr[u].l && tr[u].r <= r){
    //			return tr[u].mx;
    //		}
    //		int res = -1e9;
    //		if(l <= tr[tr[u].ls].r){
    //			res = max(res, tr[u].ls);
    //		}
    //		if(r >= tr[tr[u].rs].l){
    //			res = max(res, tr[u].rs);
    //		}
    //		return res;
    //	}
    //	int queryMn(int u, int l, int r){
    //		if(l <= tr[u].l && tr[u].r <= r){
    //			return tr[u].mn;
    //		}
    //		int res = 1e9;
    //		if(l <= tr[tr[u].ls].r){
    //			res = min(res, tr[u].ls);
    //		}
    //		if(r >= tr[tr[u].rs].l){
    //			res = min(res, tr[u].rs);
    //		}
    //		return res;
    //	}
    //
    //}ta, tb;

    void read(int &x);
    void read(long long &x);

    int main() {
        freopen("game.in", "r", stdin);
        freopen("game.out", "w", stdout);
        int n, m, q;
        read(n), read(m), read(q);
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }
        for (int i = 1; i <= m; i++) {
            read(b[i]);
        }
        for (int i = 1; i <= q; i++) {
            static int l1, r1, l2, r2, t;
            read(l1), read(r1), read(l2), read(r2);
            static long long ans;
            if (l1 == r1) {
                ans = 1e18;
                for (int j = l2; j <= r2; j++) {
                    ans = min(ans, (long long) a[l1] * b[j]);
                }
            } else if (l2 == r2) {
                ans = -1e18;
                for (int j = l1; j <= r1; j++) {
                    ans = max(ans, (long long) a[j] * b[l2]);
                }
            } else {
                ans = -1e18;
                for (int j = l1; j <= r1; j++) {
                    static long long res;
                    res = 1e18;
                    for (int k = l2; k <= r2; k++) {
                        res = min(res, (long long) a[j] * b[k]);
                    }
                    ans = max(ans, res);
                }
            }
            printf("%lld\n", ans);
        }
        fclose(stdin);
        fclose(stdout);
    }

    void read(int &x) {
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }

    void read(long long &x) {
        long long s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c) {
            if (c == '-') {
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9') {
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    }
}

#include <bits/stdc++.h>
using namespace std;

const int Inf = 1e9;

int a[100005], b[100005];

class Node{
public:
    int l, r, ls, rs, mn, mx, mnn, mxx;
    bool exiMnn, exiMxx;
};

class Tem{
public:
    int Mx, Mn, Mxx, Mnn;
    bool ExiMxx, ExiMnn;
    Tem(){
        Mx = -Inf, Mn = Inf, Mxx = -Inf, Mnn = Inf, ExiMxx = false, ExiMnn = false;
    }
    Tem(int Mx, int Mn, int Mxx, int Mnn, bool ExiMxx, bool ExiMnn){
        this -> Mx = Mx, this -> Mn = Mn, this -> Mxx = Mxx, this -> Mnn = Mnn,
        this -> ExiMxx = ExiMxx, this -> ExiMnn = ExiMnn;
    }

    Tem& operator += (const Tem&V){
        Mx = max(Mx, V.Mx), Mn = min(Mn, V.Mn),
        Mxx = max(Mxx, V.Mxx), Mnn = min(Mnn, V.Mnn),
        ExiMxx = ExiMxx || V.ExiMxx, ExiMnn = ExiMnn || V.ExiMnn;
        return *this;
    }
};

class Tr{
    int *raw;
    Node tr[400005]{};
public:
    explicit Tr(int *raw){
        this -> raw = raw;
    }

    void build(int u, int l, int r){
        tr[u].l = l, tr[u].r = r;
        if(l == r){
            tr[u].mn = tr[u].mx = raw[l];
            tr[u].mxx = raw[l] <= 0 ? raw[l]+((tr[u].exiMxx=true)&&false) : -Inf+((tr[u].exiMxx=false)&&false);
            tr[u].mnn = raw[l] >= 0 ? raw[l]+((tr[u].exiMnn=true)&&false) : Inf+((tr[u].exiMnn=false)&&false);
            return ;
        }
        int mid = (l+r)/2;
        tr[u].ls = u*2;
        tr[u].rs = u*2+1;
        build(tr[u].ls, l, mid);
        build(tr[u].rs, mid+1, r);
        tr[u].mx = max(tr[tr[u].ls].mx, tr[tr[u].rs].mx);
        tr[u].mn = min(tr[tr[u].ls].mn, tr[tr[u].rs].mn);
        tr[u].mnn = min(tr[tr[u].ls].mnn, tr[tr[u].rs].mnn);
        tr[u].mxx = max(tr[tr[u].ls].mxx, tr[tr[u].rs].mxx);
        tr[u].exiMxx = tr[tr[u].ls].exiMxx || tr[tr[u].rs].exiMxx;
        tr[u].exiMnn = tr[tr[u].ls].exiMnn || tr[tr[u].rs].exiMnn;
    }

    Tem query(int u, int l, int r){
        if(l <= tr[u].l && tr[u].r <= r){
            return {tr[u].mx, tr[u].mn,tr[u].mxx, tr[u].mnn,
                    tr[u].exiMxx, tr[u].exiMnn};
        }
        Tem res;
        if(l <= tr[tr[u].ls].r){
            res += query(tr[u].ls, l, r);
        }
        if(r >= tr[tr[u].rs].l){
            res += query(tr[u].rs, l, r);
        }
        return res;
    }
};

void read(int &x);

int main(){
    int n, m, q;
    read(n), read(m), read(q);
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }
    for(int i = 1; i <= m; i++){
        read(b[i]);
    }
    static Tr ta(a), tb(b);
    ta.build(1, 1, n), tb.build(1, 1, m);
    for(int i = 1; i <= q; i++){
        static int l1, r1, l2, r2;
        read(l1), read(r1), read(l2), read(r2);
        static long long ans;
        //        if(l1 == r1){
        //            ans = 1e18;
        //            for(int j = l2; j <= r2; j++){
        //                ans = min(ans, (long long)a[l1] * b[j]);
        //            }
        //        }else if(l2 == r2){
        //            ans = -1e18;
        //            for(int j = l1; j <= r1; j++){
        //                ans = max(ans, (long long)a[j] * b[l2]);
        //            }
        //        }else{
        //            ans = -1e18;
        //            for(int j = l1; j <= r1; j++){
        //                static long long res;
        //                res = 1e18;
        //                for(int k = l2; k <= r2; k++){
        //                    res = min(res, (long long)a[j] * b[k]);
        //                }
        //                ans = max(ans, res);
        //            }
        //        }
        static long long bMn, bMx, aMn, aMx, aMnn, aMxx;
        static bool aExiMnn, aExiMxx;
        Tem tA = ta.query(1, l1, r1), tB = tb.query(1, l2, r2);
        bMn = tB.Mn, bMx = tB.Mx,
        aMn = tA.Mn, aMx = tA.Mx, aMnn = tA.Mnn, aMxx = tA.Mxx,
        aExiMnn = tA.ExiMnn, aExiMxx = tA.ExiMxx;
        ans = max(aMx * (aMx>0?bMn:bMx), (aMn * (aMn>0?bMn:bMx)));
        if(aExiMnn){
            ans = max(aMnn * bMn, ans);
        }
        if(aExiMxx){
            ans = max(aMxx * bMx, ans);
        }
        printf("%lld\n", ans);
    }
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
