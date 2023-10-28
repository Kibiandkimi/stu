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

        static void read_str(vector<int> &x){
            static auto judge = [](int c){return 'a' <= c && c <= 'z';};
            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            while(judge(c)){
                x.emplace_back(c - 'a');
                c = getchar();
            }
        }
    };

    class Trie{
        class Node{
        public:
            int num;
            Node *son[26][26]{};

            Node():num(0){
                memset(son, 0, sizeof son);
            }
        };

        Node *rt{new Node};

        long long ans;

        void calc(Node *u, int dep){
            if(dep != 0) {
                ans = ans + (u->num / 2) * (long long) (dep * 2 - 1);
            }
            for(auto &i : u->son){
                for(auto &j : i) {
                    if (j) {
                        calc(j, dep + 1);
                    }
                }
            }
        }

    public:
        void add(vector<int> &val){
            Node *now = rt;
            for(int i = 0; i < val.size(); i++){
                if(!now->son[val[i]][val[val.size() - i - 1]]){
                    now->son[val[i]][val[val.size() - i - 1]] = new Node;
                }
                now->num++;
                now = now->son[val[i]][val[val.size() - i - 1]];
            }
            now->num++;
        }

        long long calc(){
            ans = 0;
            calc(rt, 0);
            return ans;
        }
    };

    auto read = Tools::read;

    int n;
    read(n);

    Trie trie;
    vector<int> str[n];
    for(auto &i : str){
        Tools::read_str(i);
        trie.add(i);
    }

    printf("%lld\n", trie.calc());
}