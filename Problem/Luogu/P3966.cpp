//
// Created by kibi on 2022/10/20.
//

/*
 * TODO a terrible code and not correct, how to deal it
#include <bits/stdc++.h>
using namespace std;

const int SizeN = 1000005, SizeM = 1000005;
class Graph {
    int head[SizeN], nxt[SizeM], to[SizeM], tot;

public:
    void addEdge(int u, int v, bool flag = true) {
        to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
        if (!flag) {
            return;
        }
        to[++tot] = u, nxt[tot] = head[v], head[v] = tot;
    }
    int begin(int x) {
        return head[x];
    }
    int next(int x) {
        return nxt[x];
    }
    int get(int x) {
        return to[x];
    }
};

class Trie{
    Graph g{};
    int cntNode, cntWord, rt;
    char c[SizeM]{};
    int y[SizeN][26]{}, id[SizeN]{}, fa[SizeN]{}, id[SizeN]{};

public:
    Trie(){
        rt = 0;
        c[cntNode++] = 0;
    }

    int addWord(const char *word){
        int u = rt;
        for(int i = 0; word[i]; i++){
            char str = word[i] - 'a';
            if(y[u][str]){
                u = y[u][str];
            }else{
                g.addEdge(u, cntNode++);
                y[u][str] = g.get(g.begin(u));
                fa[y[u][str]] = u;
                u = y[u][str];
                c[u] = str;
            }
        }
        id[u]++;
        if(!id[u]){
            id[u] = ++cntWord;
        }
        return u;
    }
    int getFa(int x){
        return fa[x];
    }

    int queryPos(const char *str, int u) {
        for(int i = 0; str[i]; i++){
            if(!y[u][str[i]-'a']){
                return -1;
            }
            u = y[u][str[i]-'a'];
        }
        return u;
    }

    int queryPos(char str, int u) {
        return y[u][str] ? y[u][str] : -1;
    }

    int getVal(int x){
        return c[x];
    }

    int isEnd(int u){
        return id[u];
    }

    int _addId(){
        return cntWord++;
    }

    int _getCntWord(){
        return cntWord;
    }

    int begin(int u){
        return g.begin(u);
    }

    int next(int u){
        return g.next(u);
    }

    int get(int u){
        return g.get(u);
    }
};

class AC{
    Trie tr;
    int nxt[SizeN]{};
    vector<int> sameId[205];
    int getFail(int u){
        static int c, now, res;
        c = tr.getVal(u);
        now = nxt[tr.getFa(u)];
        while(now != -1 && tr.queryPos(c, now) == -1 && now){
            now = nxt[now];
        }
        if(now == -1){
            return 0;
        }
        res = tr.queryPos(c, now);
        res = res == -1 ? 0 : res;
        return res;
    }
    void f(int u){
        for(int i = tr.begin(u); i; i = tr.next(i)){
            static int str, now;
            str = tr.getVal(tr.get(i));
            now = tr.queryPos(str, u);
            nxt[now] = nxt[now] !=-1 ? nxt[now] : getFail(now);
            f(now);
        }
    }
public:
    int ans[SizeN]{};
    AC(){
        memset(nxt, -1, sizeof nxt);
    }
    void addWord(char *word){
        static int tem, now, beforeCnt;
        static bool flag;
        now = 0;
        beforeCnt = tr._getCntWord();
        tem = tr.addWord(word);
        flag = beforeCnt == tr._getCntWord();
        if(flag){
            sameId[tr.isEnd(tem)].push_back(tr._addId());
        }
    }
    void build(){
        f(0);
    }
    void match(const char *str, int r = -1){
        static int now;
        now = 0;
        memset(ans, 0, sizeof ans);
        for(int i = 0; r == -1 ? str[i]: i < r; i++){
            static int c, tem;
            c = str[i] - 'a';
            while(tr.queryPos(c, now) == -1 && now != 0){
                now = nxt[now];
            }
            now = tr.queryPos(c, now);
            tem = now;
            while(tem){
                int id = tr.isEnd(tem);
                if(id){
                    ans[id]++;
                    for(auto &j : sameId[id]){
                        ans[j]++;
                    }
                }
                tem = nxt[tem];
            }
        }
    }
};

void read(int &x);
int readStr(char *c);

int main(){
    static int n, pos = 1, st[205], ans[205] = {0};
    static char c[1000205];
    static AC ac;
    read(n);
    for(int i = 1; i <= n; i++){
        st[i] = pos;
        int len = readStr(c + pos);
        ac.addWord(c + pos);
        pos = pos + len + 1;
    }
    ac.build();
    for(int i = 1; i <= n; i++){
        ac.match(c+st[i]);
        for(int j = 1; j <= n; j++){
            ans[j] += ac.ans[j];
        }
    }
    for(int i = 1; i <= n; i++){
        printf("%d\n", ans[i]);
    }
}

void read(int &x){
    int s = 0, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s;
}

int readStr(char *c){
    static int t;
    t = getchar();
    while(t < 'a' || 'z' < t){
        t = getchar();
    }
    static int i;
    i = 0;
    while('a' <= t && t <= 'z'){
        c[i++] = t;
        t = getchar();
    }
    return i;
}
*/

#include <bits/stdc++.h>
        using namespace std;

void read(int &x);
int readStr(char *c);
int n, tr[1100005][26] = {0}, cntNode, sum[1100005] = {0}, id[1100005] = {0}, fail[1100005] = {0}, tem[1100005], iii;
int main(){
    static char c[1100005];
    read(n);
    for(int i = 1; i <= n; i++){
        static int len, now;
        now = 0;
        len = readStr(c+1);
        for(int p = 1; p <= len; p++){
            static int u;
            u = c[i] - 'a';
            if(!tr[now][u]){
                tr[now][u] = ++cntNode;
            }
            now = tr[now][u];
            sum[now]++;
        }
        id[i] = now;
    }
    static queue<int> q;
    //    vector<int> a;
    for(int i = 0; i < 26; i++){
        if(tr[0][i]){
            q.push(tr[0][i]);
            //            a.emplace_back(tr[0][i]);
            tem[iii++] = tr[0][i];
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0; i < 26; i++){
            static int v;
            v = tr[u][i];
            if(v){
                q.push(v);
                tem[iii++] = v;
                //                a.emplace_back(v);
                fail[v] = tr[fail[u]][i];
            }else{
                tr[u][i] = tr[fail[u]][i];
            }
        }

    }
    for(int i = cntNode; i >= 0; i--){
        //        sum[fail[a[i]]] += sum[a[i]];
        sum[fail[tem[i]]] += sum[tem[i]];
    }
    for(int i = 1; i <= n; i++){
        printf("%d\n", sum[id[i]]);
    }
}

void read(int &x){
    int s = 0, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s;
}

int readStr(char *c){
    static int t;
    t = getchar();
    while(t < 'a' || 'z' < t){
        t = getchar();
    }
    static int i;
    i = 0;
    while('a' <= t && t <= 'z'){
        c[i++] = (char)t;
        t = getchar();
    }
    return i;
}