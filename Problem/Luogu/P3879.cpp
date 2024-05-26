//
// Created by kibi on 2022/11/10.
//
#include <bits/stdc++.h>

using namespace std;

void read(int&);

int main(){

    static const int MaxM = 10005;
    static const int MaxN = 5005005;

    class Trie{
        class Node{
        public:
            int a[26]{}, id;
            Node(){
                memset(a, 0, sizeof a);
                id = 0;
            }
        };
        //        vector<Node> node;
        Node node[1005005];
        int cntNode, cntWord;
    public:
        explicit Trie(int size){
            //            node.resize(size);
            cntNode = cntWord = 0;
        }
        int add(const int *s, int l){
            static int now;
            now = 0;
            for(int i = 0; i < l; i++){
                //                if(now >= node.size()){
                //                    node.resize(node.size()+l+25);
                //                }
                if(node[now].a[s[i]]){
                    now = node[now].a[s[i]];
                }else{
                    now = node[now].a[s[i]] = ++cntNode;
                }
            }
            if(!node[now].id) {
                node[now].id = ++cntWord;
            }
            return node[now].id;
        }
        int query(const int *s, int l = -1){
            static int now;
            now = 0;
            for(int i = 0; l == -1 ? s[i] != ' ' : i < l; i++){
                now = node[now].a[s[i]];
                if(!now){
                    return -1;
                }
            }
            return node[now].id;
        }
    };

    static int n, y[MaxN];
    static int s[MaxN], mx;
    read(n);
    for(int i = 1; i <= n; i++){
        static int it, l;
        read(l);

        while(l--) {
            static char c[25];
            //            memset(c, 0, sizeof c);
            scanf("%s", c);
            for(int j = 0; c[j]; j++, it++){
                s[it] = c[j]-'a';
                y[it] = i;
            }
            y[it] = i;
            s[it] = ' ';
            ++it;
        }

        mx = it;

    }

    static int m;
    read(m);
    static Trie trie(m*10);
    static int repeat[MaxM];
    for(int i = 1; i <= m; i++){
        static int c[25], it;
        static char s[25];
        //        memset(s, 0, sizeof s);
        scanf("%s", s);
        for(it = 0; s[it]; it++){
            c[it] = s[it] - 'a';
        }
        repeat[i] = trie.add(c, it);
    }

    static vector<int> ans[MaxM];
    for(int i = 0; i < mx; i++){
        if(s[i] == ' '){
            continue;
        }
        static int res;
        res = trie.query(s+i);
        if(res > 0){
            if(ans[res].empty() || ans[res].back() != y[i]) {
                ans[res].push_back(y[i]);
            }
        }
        while(s[i] != ' ' && i < mx){
            i++;
        }
    }

    for(int i = 1; i <= m; i++){
        for(auto &j : ans[repeat[i]]){
            printf("%d ", j);
        }
        if(i == m){
            return 0;
        }
        printf("\n");
    }
}

void read(int &x){
    int s = 0, w = 1, c = ::getchar();
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