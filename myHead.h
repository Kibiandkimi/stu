//
// Created by kibi on 2022/10/17.
//

#ifndef STU_MYHEAD_H
#define STU_MYHEAD_H

#include <bits/stdc++.h>
const int Size = 1000005;
class Graph {
    int head[Size / 2], nxt[Size], to[Size], tot;

public:
    /*
    Graph() {
        //         are these necessary?
        memset(head, 0, sizeof head);
        memset(to, 0, sizeof to);
        memset(nxt, 0, sizeof nxt);
        tot = 0;
    }
     */
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
    __attribute__((unused)) int next(int x) {
        return nxt[x];
    }
    int get(int x) {
        return to[x];
    }
};

class Lca {
    int fa[Size][20]{}, dep[Size]{};
    Graph *g;
    void f(int u) {
        for (int i = 1; (1 << i) <= dep[u]; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (int i = g->begin(u); i; i = g->next(i)) {
            static int v;
            v = g->get(i);
            if (v != fa[u][0]) {
                fa[v][0] = u;
                dep[v] = dep[u] + 1;
                f(v);
            }
        }
    }

public:
    explicit Lca(Graph *gT, int u = 1) {
        dep[u] = 1, fa[u][0] = 1;
        g = gT;
        f(u);
    }
    int getLca(int x, int y) {
        if (x == y) {
            return x;
        }
        if (dep[x] < dep[y]) {
            std::swap(x, y);
        }

        for (int i = log(dep[x] - dep[y]) / log(2); i >= 0; i--) {
            if (dep[fa[x][i]] >= dep[y]) {
                x = fa[x][i];
            }
            if (x == y) {
                return x;
            }
        }
        for (int i = log(dep[x]) / log(2); i >= 0; i--) {
            if (fa[x][i] != fa[y][i]) {
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    int getDis(int u, int v, int lca = -1) {
        if (lca == -1) {
            lca = getLca(u, v);
        }
        return dep[u] + dep[v] - 2 * dep[lca];
    }
    int getFa(int x) {
        return fa[x][0];
    }
    int _getDep(int x) {
        return dep[x];
    }
};

// TODO classes Trie and AC are not complete, they may have some mistake, maybe another way to make it

class Trie{
    Graph g{};
    int cntNode, cntWord, rt;
    char c[Size]{};
    int y[Size][26]{}, id[Size]{}, fa[Size]{};

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
    int nxt[Size]{};
    std::vector<int> sameId[205];
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
    int ans[Size]{};
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

class Manacher{

    int readStr(char *c){
        int tem = getchar();
        while(tem < 'a' || 'z' < tem){
            tem =getchar();
        }
        static int i = 0;
        while('a' <= tem && tem <= 'z'){
            c[i++] = (char)tem;
            tem = getchar();
        }
        return i;
    }

    int main(){
        static char raw[24000005], str[46000005];
        static int len = readStr(raw+1), d[46000005], ans = 0;
        str[0] = '#';
        for(int i = 1; i <= len; i++){
            str[i*2] = raw[i];
            str[i*2 - 1] = '*';
        }
        str[len*2+1] = '*';
        len = len*2+1;
        for(int i = 1; i <= len; i++){
            static int mid = 0, r = 0;
            if(i <= r){
                d[i] = std::min(d[(mid<<1)-i], r-i+1);
            }
            while(str[i - d[i]] == str[i + d[i]] && i + d[i] <= len){
                ++d[i];
            }
            if(d[i] + i > r){
                r = d[i] + i - 1, mid = i;
            }
            if(d[i] > ans){
                ans = d[i];
            }
        }
        printf("%d", ans-1);
        return 0;
    }
public:
    Manacher(){
        main();
    }

};

#endif//STU_MYHEAD_H
