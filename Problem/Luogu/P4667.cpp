//
// Created by kibi on 24-7-26.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    auto read_char = [](int &x){
        int c = getchar();
        while(c != '/' && c != '\\'){
            c = getchar();
        }
        x = c;
    };

    int n, m;
    read(n), read(m);

    if(abs(n - m) % 2){
        printf("NO SOLUTION\n");
        return 0;
    }

    vector<vector<vector<bool>>> w(n + 1, vector<vector<bool>>(m + 1, vector<bool>(4)));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int x;
            read_char(x);
            w[i][j][3] = (x == '/');
            w[i + 1][j][1] = (x == '\\');
            w[i][j + 1][2] = (x == '\\');
            w[i + 1][j + 1][0] = (x == '/');
        }
    }

    vector<vector<int>> dis(n + 1, vector<int>(m + 1, -1));
    // memset(dis, -1, sizeof dis);

    using P = tuple<int, int>;

    dis[0][0] = 0;

    queue<P> q;
    q.emplace(0, 0);
    while(!q.empty()){
        auto now = q.front();
        q.pop();

        stack<P> stk;

        auto opt = [&q, &stk, &dis, &w, n, m](P point){
            auto [x, y] = point;

            if(x == n && y == m){
                printf("%d\n", dis[x][y]);
                return true;
            }

            if(x > 0 && y > 0 && (dis[x - 1][y - 1] == -1 || dis[x - 1][y - 1] > dis[x][y] + w[x][y][0])){
                if(w[x][y][0] == 0){
                    stk.emplace(x - 1, y - 1);
                    dis[x - 1][y - 1] = dis[x][y];
                }else{
                    q.emplace(x - 1, y - 1);
                    dis[x - 1][y - 1] = dis[x][y] + 1;
                }
            }

            if(x > 0 && y < m && (dis[x - 1][y + 1] == -1 || dis[x - 1][y + 1] > dis[x][y] + w[x][y][1])){
                if(w[x][y][1] == 0){
                    stk.emplace(x - 1, y + 1);
                    dis[x - 1][y + 1] = dis[x][y];
                }else{
                    q.emplace(x - 1, y + 1);
                    dis[x - 1][y + 1] = dis[x][y] + 1;
                }
            }

            if(x < n && y > 0 && (dis[x + 1][y - 1] == -1 || dis[x + 1][y - 1] > dis[x][y] + w[x][y][2])){
                if(w[x][y][2] == 0){
                    stk.emplace(x + 1, y - 1);
                    dis[x + 1][y - 1] = dis[x][y];
                }else{
                    q.emplace(x + 1, y - 1);
                    dis[x + 1][y - 1] = dis[x][y] + 1;
                }
            }

            if(x < n && y < m && (dis[x + 1][y + 1] == -1 || dis[x + 1][y + 1] > dis[x][y] + w[x][y][3])){
                if(w[x][y][3] == 0){
                    stk.emplace(x + 1, y + 1);
                    dis[x + 1][y + 1] = dis[x][y];
                }else{
                    q.emplace(x + 1, y + 1);
                    dis[x + 1][y + 1] = dis[x][y] + 1;
                }
            }

            return false;
        };

        if(opt(now)){
            return 0;
        }

        while(!stk.empty()){
            now = stk.top();
            stk.pop();
            if(opt(now)){
                return 0;
            }
        }
    }

}