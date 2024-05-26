//
// Created by kibi on 23-11-8.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    class Node{
    public:
        int x, y, z;

        Node() = default;
        Node(int x, int y, int z):x(min(x, y)), y(max(x, y)), z(z){}
    };

    int n;
    read({&n});
    while(n){
        static int cnt;
        Node node[3 * n];
        for (int i = 0; i < 3 * n; i += 3) {
            int x, y, z;
            read({&x, &y, &z});
            node[i] = {x, y, z};
            node[i + 1] = {x, z, y};
            node[i + 2] = {y, z, x};
        }
        int f[3 * n][3 * n];
        memset(f, -1, sizeof f);
        int ans = 0;
        for(int i = 0; i < 3 * n; i++){
            f[0][i] = node[i].z;
            ans = max(ans, f[0][i]);
        }
        for(int i = 1; i < 3 * n; i++){
            for(int j = 0; j < 3 * n; j++){
                for(int k = 0; k < 3 * n; k++){
                    if(f[i - 1][k] != -1 &&
                        node[k].x > node[j].x &&
                        node[k].y > node[j].y){
                        f[i][j] = max(f[i][j], f[i - 1][k] + node[j].z);
                        ans = max(ans, f[i][j]);
                    }
                }
            }
        }
        ++cnt;
        printf("Case %d: maximum height = %d\n", cnt, ans);
        read({&n});
    }
}