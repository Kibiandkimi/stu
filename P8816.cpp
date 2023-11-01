//
// Created by kibi on 23-11-1.
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
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    using Node = pair<int, int>;

    Node node[n];
    for(auto &i : node){
        read(i.first), read(i.second);
    }

    sort(node, node + n,
         [](const Node &a, const Node &b)
         {return a.first == b.first ? a.second < b.second : a.first < b.first;});

    int ans = m + 1;
    int f[n][n];
    for(int i = 0; i < n; i++){
        for(auto &j : f[i]){
            j = 1;
        }
        for(int j = i + 1; j < n; j++){
            for(int k = 0; k < j; k++){
                if(node[j].first >= node[k].first &&
                    node[j].second >= node[k].second &&
                    node[k].first >= node[i].first &&
                    node[k].second >= node[i].second){
                    f[i][j] = max(f[i][j], f[i][k] + 1);
                }
            }
            if(node[j].first >= node[i].first &&
                node[j].second >= node[i].second &&
                node[j].second - node[i].second +
                                node[j].first - node[i].first - f[i][j] + 1 <= m){
                ans = max(ans, m + f[i][j]);
            }
        }
    }
    printf("%d\n", ans);
}