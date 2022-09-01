#include <bits/stdc++.h>
using namespace std;
struct Tree{
    int siz, son[2];
    long long val;
    unsigned int rnk;
}tr[1100005];
mt19937 rnd(random_device{}());
int n, m, root, cnt, debugOpt;
long long last, finalAns;

bool getType(int c);
void read(int &x);
int newNode(long long x);
void updSize(int x);
void split(int &x, int &y, long long k, int pos);
int merge(int x, int y);
int queryRnk(long long x, int pos);
int queryKth(long long k, int pos);

int main(){
    read(n), read(m);
    while(n--){
        int t;
        read(t);
        if(!root){
            root = newNode(t);
        }else{
            int l, r;
            split(l, r, t, root);
            root = merge(merge(l, newNode(t)), r);
        }
    }
    while(m--){
        int opt, tx;
        read(opt), read(tx);
        debugOpt = opt;
        long long x = tx;
        x ^= last;
        if(opt == 1){
            int l, r;
            split(l, r, x, root);
            root = merge(merge(l, newNode(x)), r);
        }else if(opt == 2){
            int l, r, z;
            split(l, z, x, root);
            split(l, r, x-1, l);
            r = merge(tr[r].son[0], tr[r].son[1]);
            root = merge(merge(l, r), z);
        }else if(opt == 3){
            last = queryRnk(x, root);
        }else if(opt == 4){
            last = queryKth(x, root);
        }else if(opt == 5){
            int l, r;
            split(l, r, x-1, root);
            last = tr[queryKth(tr[l].siz, l)].val;
            root = merge(l, r);
        }else if(opt == 6){
            int l, r;
            split(l, r, x, root);
            last = tr[queryKth(1, r)].val;
            root = merge(l, r);
        }else{
            throw "error opt";
        }
        if(3<=opt){
            finalAns ^= last;
        }
    }
    printf("%lld", finalAns);
    return 0;
}

bool getType(int c){
    return c<'0'||'9'<c;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

int newNode(long long x){
    tr[++cnt].val = x;
    tr[cnt].rnk = rnd();
    tr[cnt].siz = 1;
    return cnt;
}

void updSize(int x){
    tr[x].siz = tr[tr[x].son[0]].siz + tr[tr[x].son[1]].siz + 1;
}

void split(int &x, int &y, long long k, int pos){
    if(!pos){
        x = y = 0;
    }else{
        if(tr[pos].val <= k){
            x = pos;
            split(tr[pos].son[1], y, k, tr[pos].son[1]);
        }else{
            y = pos;
            split(x, tr[pos].son[0], k, tr[pos].son[0]);
        }
        updSize(pos);
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else{
        if(tr[x].rnk < tr[y].rnk){
            tr[x].son[1] = merge(tr[x].son[1], y);
            updSize(x);
            return x;
        }else{
            tr[y].son[0] = merge(x, tr[y].son[0]);
            updSize(y);
            return y;
        }
    }
}

int queryRnk(long long x, int pos){
    int l, r;
    split(l, r, x-1, pos);
    int ans = tr[l].siz+1;
    root = merge(l, r);
    return ans;
}

int queryKth(long long k, int pos){
    while(true){
        if(k == -1 || pos == 0){
            printf("%d\n", debugOpt);
            throw "error k or pos";
        }
        if(tr[tr[pos].son[0]].siz >= k){
            pos = tr[pos].son[0];
        }else if(tr[tr[pos].son[0]].siz+1 == k){
            return pos;
        }else{
            k -= tr[tr[pos].son[0]].siz + 1;
            pos = tr[pos].son[1];
        }
    }
}