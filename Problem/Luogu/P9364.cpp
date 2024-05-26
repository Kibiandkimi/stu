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
            static auto judge = [](const int &c){return 'a' <= c && c <= 'z';};
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
        class Node{
        public:
            bool flag;
            Node *son[26]{};

            Node(){
                flag = false;
                memset(son, 0, sizeof son);
            }
        };

        Node *rt;

        bool query_(vector<int> &str){
            Node *now1 = rt, *now2 = rt;
            for(int i = 0, mxi = str.size(); i < mxi; i++){
                if(i != 0){
                    if(!now1->son[str[i] - 'a']){
                        return false;
                    }
                    now1 = now1->son[str[i] - 'a'];
                }
                if(i != mxi - 1){
                    if(!now2->son[str[i] - 'a']){
                        return false;
                    }
                    now2 = now2->son[str[i] - 'a'];
                }
            }
            return now1->flag && now2->flag;
        }

    public:
        Trie(){
            rt = new Node;
        }

        bool add(vector<int> &str){
            Node *now = rt;
            for(auto &i : str){
                if(!now->son[i - 'a']){
                    now->son[i - 'a'] = new Node;
                }
                now = now->son[i - 'a'];
            }

            if(str.size() == 1){
                now->flag = true;
            }else{
                now->flag = query_(str);
            }
            return now->flag;
        }
    };

    auto read = Tools::read;
    auto read_ = Tools::read_;

    int n;
    read(n);

    Trie trie;
    vector<int> str[n];
    for(auto &i : str){
        read_(i);
    }

    vector<int> *it[n];
    for(int i = 0; i < n; i++){
        it[i] = &str[i];
    }

    sort(it, it + n, [](const vector<int> *a, const vector<int> *b){return a->size() < b->size();});

    int ans = 0;
    for(auto &i : it){
        if(trie.add(*i)){
            ans = max(ans, (int)i->size());
        }
    }

    printf("%d\n", ans);
}