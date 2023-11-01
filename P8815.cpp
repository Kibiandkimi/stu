//
// Created by kibi on 23-11-1.
//

#include <bits/stdc++.h>
using namespace std;

int main() {
    class Tools {
    public:
        static void read_str(vector<int> &x) {
            static auto judge = [](int c) {
                return c == '0' || c == '1' || c == '|' || c == '&' || c == '(' || c == ')';
            };

            int c = getchar();
            while (!judge(c)) {
                c = getchar();
            }
            while (judge(c)) {
                x.emplace_back(c);
                c = getchar();
            }
            x.shrink_to_fit();
        }
    };

    auto read = Tools::read_str;

    vector<int> str;
    read(str);

    int n = str.size();

    int lst1[n], lst2[n], now1[n], now2[n];
    memset(now1, -1, sizeof now1);
    memset(now2, -1, sizeof now2);
    for(int i = 0, dep = 0; i < n; i++){
        switch(str[i]){
            case '(':
                ++dep;
                break;
            case ')':
                --dep;
                break;
            case '|':
                now1[dep] = i;
                break;
            case '&':
                now2[dep] = i;
                break;
            default:
                (str[i] != '0' && str[i] != '1') ? (throw exception()) : (void)0;
        }

        lst1[i] = now1[dep];
        lst2[i] = now2[dep];
    }

    static int cnt1 = 0, cnt2 = 0;
    static const int *l1 = lst1, *l2 = lst2;
    static auto s = str;

    auto f = [](int l, int r, auto &&f)->bool{
        if(l1[r] >= l){
            bool ans = f(l, l1[r] - 1, f);
            if(ans){
                cnt1++;
                return true;
            }
            return f(l1[r] + 1, r, f);
        }
        if(l2[r] >= l){
            bool ans = f(l, l2[r] - 1, f);
            if(!ans){
                ++cnt2;
                return false;
            }
            return f(l2[r] + 1, r, f);
        }
        if(s[l] == '(' && s[r] == ')'){
            return f(l + 1, r - 1, f);
        }
        return s[l] == '1';
    };

    bool ans = f(0, n - 1, f);
    printf("%d\n%d %d\n", ans, cnt2, cnt1);
}

// TODO how to build tree
/*
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

        static void read_str(vector<int> &x){
            static auto judge = [](int c){
                return c == '0' || c == '1' || c == '|' || c == '&' || c == '(' || c == ')';
            }

            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            while(judge(c)){
                x.emplace_back(c);
                c = getchar();
            }
            x.shrink_to_fit();
        }
    };

    class Trie{
    public:
        class Node{
        public:
            int type{2};
            Node *ls{nullptr}, *rs{nullptr};
        };

        Node *rt;

    };

    auto read = Tools::read_str;

    vector<int> str;
    read(str);
    reverse(str.begin(), str.end());

    Trie trie;
    trie.rt = new Trie::Node;
    Node *now = rt;
    stack<Node*> fa;
    fa.push(rt);
    now = rt.rs = new Node;
    stack<int> stk;
    for(auto &i : str){
        if(i == '0' || i == '1'){
            now.type = i == '1';
            now = stk.top();
            stk.pop();
        }else if(i == ')'){
            now.ls = new Node;
            stk.push(now);
            now = now.ls;
        }else if(i == '&' || i == '|'){
            now.type = (i == '&' ? -1 : -2);
            now.ls = new Node;
            stk.push(now);
            now = now.ls;
        }else if(i == '('){
            if(stk.empty()){
                throw exception();
            }
            now = stk.top();
            stk.pop();
        }
    }
}
 */