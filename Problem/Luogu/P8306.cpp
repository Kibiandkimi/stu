//
// Created by kibi on 23-10-28.
//
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

        static void read_(vector<int> &x){
            auto judge = [](int c){return ('A' <= c && c <= 'Z') ||
                                            ('a' <= c && c <= 'z') ||
                                            ('0' <= c && c <= '9');};
            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            while(judge(c)){
                x.emplace_back(c);
                c = getchar();
            }
        }
    };

    class Trie{
        class Node{
        public:
            int sum;
            Node *son[26 * 2 + 10]{};
            Node(){
                sum = 0;
                memset(son, 0, sizeof son);
            }
        };

        Node *rt;

        static int get(int c){
            return ('A' <= c && c <= 'Z') ? (c - 'A') : ('a' <= c && c <= 'z') ? (26 + c - 'a') : (26 + 26 + c - '0');
        }

    public:
        Trie(){
            rt = new Node;
        }

        void add(vector<int> &str){
            auto now = rt;
            for(auto &i : str){
                int c = get(i);
                if(!now->son[c]){
                    now->son[c] = new Node;
                    now->son[c]->sum = 1;
                }else{
                    now->son[c]->sum++;
                }
                now = now->son[c];
            }
        }

        int query(vector<int> &str){
            auto now = rt;
            for(auto &i : str){
                int c = get(i);
                if(!now->son[c]){
                    return 0;
                }else{
                    now = now->son[c];
                }
            }
            return now->sum;
        }

        void del(Node *x){
            for(auto &i : x->son){
                if(i){
                    del(i);
                    free(i);
                }
            }
        }

        ~Trie(){
            del(rt);
            free(rt);
        }
    };

    auto read = Tools::read;

    int T;
    read(T);

    while(T--){
        Trie trie;
        int n, q;
        read(n), read(q);
        while(n--){
            vector<int> str;
            Tools::read_(str);
            trie.add(str);
        }
        while(q--){
            vector<int> str;
            Tools::read_(str);
            printf("%d\n", trie.query(str));
        }
    }
}