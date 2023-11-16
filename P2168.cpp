//
// Created by kibi on 23-11-15.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;

    auto read = [](initializer_list<int*> x){
        auto read = [](int &x){
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
        };

        for(auto &i : x){
            read(*i);
        }
    };

    auto read_ll = [](initializer_list<ll*> x){
        auto read_ll = [](ll &x){
            ll s = 0, w = 1, c = getchar();
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
        };

        for(auto &i : x){
            read_ll(*i);
        }
    };

    class Node{
    public:
        int dep{0};
        ll val;
        vector<Node*> son;

        explicit Node(const ll &val):val(val){}

        Node(const ll &val, const vector<Node*> &son):val(val), son(son){}

        Node(const int &dep, const ll &val, const vector<Node*> &son):dep(dep), val(val), son(son){}
    };

    class Cmp{
    public:
        bool operator () (const Node *a, const Node *b){
            return a->val == b->val ? a->dep > b->dep : a->val > b->val;
        }
    };

    int n, k;
    read({&n, &k});

    priority_queue<Node*, vector<Node*>, Cmp> q;
    for (int i = 0; i < n; ++i) {
        ll t;
        read_ll({&t});
        q.emplace(new Node{t});
    }

    while((n - 1) % (k - 1) != 0){
        q.emplace(new Node{0});
        n++;
    }

    ll ans = 0;
    while(q.size() > 1){
        vector<Node*> now(k);
        ll sum = 0;
        int dep = 0;
        for(auto &i : now){
            if(q.empty()){
                throw runtime_error("Error priority_queue size!");
            }
            i = q.top();
            q.pop();
            sum += i->val;
            dep = max(dep, i->dep);
        }
        ans += sum;
        q.emplace(new Node{dep + 1, sum, now});
    }

    Node *rt = q.top();
    q.pop();

    printf("%lld\n%d\n", ans, rt->dep);
}