//
// Created by kibi on 23-10-1.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    const int N = 750;

    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c){
                if(c == EOF){
                    x = 0;
                    return;
                }
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
    };

    class Node{
    public:
        int v, s;

        explicit Node(int v = 0, int s = 0) : v(v), s(s){}

        class Cmp{
        public:
            bool operator () (const Node &a, const Node &b) {
                return a.v > b.v;
            }
        };
    };

    auto read = Tools::read;

    while(true){
        int k;
        read(k);

        if(!k){
            return 0;
        }

        using Node_pq = priority_queue<Node, vector<Node>, Node::Cmp>;
        static Node_pq q;
        static int ans[N + 5], u[N + 5];
        for(int i = 1; i <= k; i++){
            read(ans[i]);
        }
        for(int i = 2; i <= k; i++){
            for(int j = 1; j <= k; j++){
                read(u[j]);
            }

            sort(u + 1, u + 1 + k);

            Node_pq{}.swap(q);

            for(int j = 1; j <= k; j++){
                q.emplace(ans[j] + u[1], 1);
            }

            for(int j = 1; j <= k; j++){
                Node tem = q.top();
                q.pop();
                ans[j] = tem.v;
                if(tem.s < k){
                    q.emplace(tem.v - u[tem.s] + u[tem.s + 1], tem.s + 1);
                }
            }
        }
        for(int i = 1; i < k; i++){
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans[k]);
    }
}