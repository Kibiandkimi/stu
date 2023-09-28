//
// Created by kibi on 2022/9/1.
//
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
            last = tr[queryKth(x, root)].val;
        }else if(opt == 5){
            int l, r;
            //            split(l, r, x-1, root);
            //            last = tr[queryKth(tr[l].siz, l)].val;
            //            root = merge(l, r);
            split(l, r, x-1, root);
            int u = l;
            while(tr[u].son[1]){
                u = tr[u].son[1];
            }
            last = tr[u].val;
            root = merge(l, r);
        }else if(opt == 6){
            int l, r;
            //            split(l, r, x, root);
            //            last = tr[queryKth(1, r)].val;
            //            root = merge(l, r);
            split(l, r, x, root);
            int u = r;
            while(tr[u].son[0]){
                u = tr[u].son[0];
            }
            last = tr[u].val;
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
    return pos;
}

// 2023/9/28

// TODO try 01trie

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){
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

        static int pow(int a, int p){
            int res = 1;
            while(p){
                if(p & 1){
                    res *= a;
                }
                a *= a;
                p >>= 1;
            }
            return res;
        }

        static int abs(int x){
            return x < 0 ? -x : x;
        }
    };

    class Trie{
        class Node{
        public:
            int sum;
            int ls, rs;

            Node():sum(0), ls(0), rs(0){};
        };
        Node root;
        Node data[7500000];
        int cnt{1};

    public:
        void insert(int x, int val = 1){
            static bool num[35];
            static int i;
            memset(num, 0, sizeof num);
            for(i = 0; x; i++){
                num[i] = x & 1;
                x >>= 1;
            }
            Node *now = &root;
            for(i = 30; i >= 0; i--){

                if(now->sum == -1){
                    int temp = now->ls;
                    now->ls = 0;
                    if(temp & (1 << i)){
                        now->rs = cnt++;
                        data[now->rs].ls = temp - (1 << i);
                        data[now->rs].sum = -1;
                        if(!i){
                            data[now->rs].sum = 1;
                        }
                    }else{
                        now->ls = cnt++;
                        data[now->ls].ls = temp;
                        data[now->ls].sum = -1;
                        if(!i){
                            data[now->ls].sum = 1;
                        }
                    }
                    now->sum = 1;
                }

                now->sum += val;
                if(!num[i]){
                    if(!now->ls){
                        now->ls = cnt++;
                        int temp = 0;
                        for(int j = 0; j < i; j++){
                            temp += num[j] * Tools::pow(2, j);
                        }
                        data[now->ls].ls = temp;
                        data[now->ls].sum = -1;
                        if(!i){
                            data[now->ls].sum = 1;
                        }
                        return;
                    }
                    now = &data[now->ls];
                }else{
                    if(!now->rs){
                        now->rs = cnt++;
                        int temp = 0;
                        for(int j = 0; j < i; j++){
                            temp += num[j] * Tools::pow(2, j);
                        }
                        data[now->rs].ls = temp;
                        data[now->rs].sum = -1;
                        if(!i){
                            data[now->rs].sum = 1;
                        }
                        return;
                    }
                    now = &data[now->rs];
                }
            }
            now->sum += val;
        }

        int query_rnk_by_num(int x){
            static int num[35], i, rnk;
            memset(num, 0, sizeof num);
            for(i = 0; x; i++){
                num[i] = x & 1;
                x >>= 1;
            }
            Node *now = &root;
            for(i = 30, rnk = 1; i >= 0; i--){
                if(now->sum == -1){
                    return rnk;
                }
                if(!num[i]){
                    now = &data[now->ls];
                }else{
                    rnk += Tools::abs(data[now->ls].sum);
                    now = &data[now->rs];
                }
            }
            return rnk;
        }

        int query_num_by_rnk(int rnk){
            int res = 0;
            Node *now = &root;
            for(int i = 30; i >= 0; i--){
                if(now->sum == -1){
                    return res + now->ls;
                }
                if(rnk <= Tools::abs(data[now->ls].sum)){
                    now = &data[now->ls];
                }else{
                    rnk -= Tools::abs(data[now->ls].sum);
                    now = &data[now->rs];
                    res += Tools::pow(2, i);
                }
            }
            return res;
        }

        int query_sum_by_num(int x){
            static int num[35], i;
            memset(num, 0, sizeof num);
            for(i = 0; x; i++){
                num[i] = x & 1;
                x >>= 1;
            }
            Node *now = &root;
            for(i = 30; i >= 0; i--){
                if(now->sum == -1){
                    return 1;
                }
                if(!num[i]){
                    now = &data[now->ls];
                }else{
                    now = &data[now->rs];
                }
            }
            return Tools::abs(now->sum);
        }

        int query_pre(int x){
            int rnk = query_rnk_by_num(x);
            return query_num_by_rnk(--rnk);
        }

        int query_suc(int x){
            int rnk = query_rnk_by_num(x), sum = query_sum_by_num(x);
            return query_num_by_rnk(rnk + sum);
        }

    };

    auto read = Tools::read;

    static int n, m;
    read(n), read(m);

    static Trie trie;
    for(int i = 1; i <= n; i++){
        static int x;
        read(x);
        trie.insert(x);
    }

    static int ans;

    for(int i = 1; i <= m; i++){
        static int opt, x, last;
        read(opt), read(x);
        x ^= last;
        switch(opt){
            case 1:
                trie.insert(x);
                break;
            case 2:
                trie.insert(x, -1);
                break;
            case 3:
                last = trie.query_rnk_by_num(x);
                break;
            case 4:
                last = trie.query_num_by_rnk(x);
                break;
            case 5:
                last = trie.query_pre(x);
                break;
            case 6:
                last = trie.query_suc(x);
                break;
            default:
                throw exception();
        }
        if(last < 0){
            printf("%c", 'A' + opt - 1);
            return 0;
            throw exception();
        }
        if(opt > 2){
            ans ^= last;
        }
    }

    printf("%d\n", ans);

}
 *
 * */