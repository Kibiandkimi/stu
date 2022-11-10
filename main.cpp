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
        vector<Node> node;
        int cntNode, cntWord;
    public:
        explicit Trie(int size){
            node.resize(size);
            cntNode = cntWord = 0;
        }
        int add(const int *s, int l){
            static int now;
            now = 0;
            for(int i = 0; i < l; i++){
                if(now >= node.size()){
                    node.resize(node.size()+l+25);
                }
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

    static int n;
    static vector<int> y[MaxN];
    static int s[MaxN], mx;
    static Trie trie(n * 105);

    read(n);
    for(int i = 1; i <= n; i++){
        static int l;
        read(l);
        while(l--) {
            static char c[25];
            static int s[25], it;
            memset(c, 0, sizeof c);
            memset(s, 0, sizeof s);
            it = 0;
            scanf("%s", c);
            for(int j = 0; c[j] != 0; j++, it++){
                s[j] = c[j]-'a';
            }
            y[trie.add(s, it)].emplace_back(i);
        }
        /*
        static int it, l, c;
        read(l);
        c = getchar();
        while(c == ' '){
            c = getchar();
        }
        while(l){
            s[it] = c == ' ' ? c : c - 'a';
            y[it] = i;
            c = getchar();
            if(c == ' ' || c == '\n'){
                l--;
            }
            ++it;
        }
        s[it++] = ' ';
        mx = it;
         */
    }
    static int m;
    read(m);
    static vector<int> ans[MaxM];
    //    static int repeat[MaxN];
    for(int i = 1; i <= m; i++){
        static char c[25];
        static int s[25], it;
        memset(c, 0, sizeof c);
        memset(s, 0, sizeof s);
        scanf("%s", c);
        for(int j = 0; c[j] != 0; s[++j] = ' '){
            s[j] = c[j] - 'a';
        }
        static int res;
        res = trie.query(s);
        if(res > 0) {
            for (int j = 0, mxj = y[res].size(); j < mxj; j++) {
                printf("%d ", y[res][j]);
            }
        }
        printf("\n");
        /*
        it = 0;
        c[0] = getchar();
        while(c[0] < 'a' || c[0] > 'z'){
            c[0] = getchar();
        }
        c[0] -= 'a';
        c[++it] = getchar();
        while('a' <= c[it] && c[it] <= 'z'){
            c[it] -= 'a';
            c[++it] = getchar();
        }
//        repeat[i] = trie.add(c, it);
         */
    }

    /*
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
     */
    /*
    for(int i = 1; i <= m; i++){
        for(auto &j : ans[i]){
            printf("%d ", j);
        }
        if(i == m){
            return 0;
        }
        printf("\n");
    }
     */
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