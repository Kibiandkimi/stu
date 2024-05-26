//
// Created by kibi on 22-8-31.
//
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n, mn, tag, cnt, root, finalAns;
int val[MAXN], rnk[MAXN], son[MAXN][2], siz[MAXN], raw[MAXN];
mt19937 rng(std::random_device{}());

int getType(int c);
void read(int &x);
int newNode(int x);
void updSize(int u);
void split(int &x, int &y, int k, int pos);
int merge(int x, int y);
int queryRnk(int k);

int main(){
    //    srand((unsigned)time(nullptr));

    read(n), read(mn);
    while(n--){
        int opt;
        read(opt);
        if(opt == 'I'){
            int k;
            read(k);
            if(k < mn){
                continue;
            }
            //            k += tag;
            int l, r;
            split(l, r, k + tag, root);
            root = merge(merge(l, newNode(k)), r);
        }else if(opt == 'A'){
            int k;
            read(k);
            tag -= k;
        }else if(opt == 'S'){
            int k;
            read(k);
            tag += k;
            int l, r;
            split(l, r, mn+tag-1, root);
            finalAns += siz[l];
            root = r;
        }else if(opt == 'F'){
            int k;
            read(k);
            k = queryRnk(k);
            if(k == -1){
                printf("-1\n");
                continue;
            }
            int pastTag = val[k]-raw[k], ans = raw[k] + pastTag-tag;
            printf("%d\n", ans);
        }else{
            throw "error opt";
        }
    }
    printf("%d", finalAns);
}

int getType(int c){
    return ('0'<=c&&c<='9')?1:((c=='I'||c=='A'||c=='S'||c=='F')?2:0);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(!getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    if(getType(c) == 2){
        x = c;
        return ;
    }
    while(getType(c)){
        s = s*10 +c-'0';
        c = getchar();
    }
    x = s*w;
}

int newNode(int x){
    val[++cnt] = x+tag;
    rnk[cnt] = rng();
    siz[cnt] = 1;
    raw[cnt] = x;
    return cnt;
}

void updSize(int u){
    siz[u] = siz[son[u][0]] + siz[son[u][1]] + 1;
}

void split(int &x, int &y, int k, int pos){
    if(!pos){
        x = y = 0;
    }else{
        if(val[pos] <= k){
            x = pos;
            split(son[pos][1], y, k, son[pos][1]);
        }else{
            y = pos;
            split(x, son[pos][0], k, son[pos][0]);
        }
        updSize(pos);
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else if(rnk[x] < rnk[y]){
        son[x][1] = merge(son[x][1], y);
        updSize(x);
        return x;
    }else{
        son[y][0] = merge(x, son[y][0]);
        updSize(y);
        return y;
    }

}

int queryRnk(int k){
    //    int l, r;
    //    split(l, r, mn+tag-1, root);
    //    finalAns += siz[l];
    //    root = r;
    int pos = root;
    if(k > siz[root]){
        return -1;
    }
    while(true){
        if(siz[son[pos][1]] >= k){
            pos = son[pos][1];
        }else if(siz[son[pos][1]]+1 == k){
            return pos;
        }else{
            k -= siz[son[pos][1]]+1;
            pos = son[pos][0];
        }
    }
}
