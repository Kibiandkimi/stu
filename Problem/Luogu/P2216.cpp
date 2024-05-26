//
// Created by kibi on 23-11-3.
//

// TODO use function to opt

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

    int a, b, n;
    read(a), read(b), read(n);

    int data[a][b];
    for(auto &i : data){
        for(auto &j : i){
            read(j);
        }
    }

    int mxl[a][b], mnl[a][b], mxh[a][b], mnh[a][b];
    for(int i = 0; i < a; i++){
        deque<pair<int, int>> mxq, mnq;
        for(int j = 0; j < n; j++){
            while(!mxq.empty() && mxq.back().second < data[i][j]){
                mxq.pop_back();
            }
            while(!mnq.empty() && mnq.back().second > data[i][j]){
                mnq.pop_back();
            }
            mnq.emplace_back(j, data[i][j]);
            mxq.emplace_back(j, data[i][j]);
        }
        mxl[i][n - 1] = mxq.front().second;
        mnl[i][n - 1] = mnq.front().second;
        for(int j = n; j < b; j++){
            while(!mxq.empty() && mxq.front().first <= j - n){
                mxq.pop_front();
            }
            while(!mnq.empty() && mnq.front().first <= j - n){
                mnq.pop_front();
            }
            while(!mxq.empty() && mxq.back().second <= data[i][j]){
                mxq.pop_back();
            }
            while(!mnq.empty() && mnq.back().second >= data[i][j]){
                mnq.pop_back();
            }
            mnq.emplace_back(j, data[i][j]);
            mxq.emplace_back(j, data[i][j]);
            mxl[i][j] = mxq.front().second;
            mnl[i][j] = mnq.front().second;
        }
    }

    int ans = 1000000000;
    for(int j = n - 1; j < b; j++){
        deque<pair<int, int>> mxq, mnq;
        for(int i = 0; i < n; i++){
            while(!mxq.empty() && mxq.back().second <= mxl[i][j]){
                mxq.pop_back();
            }
            while(!mnq.empty() && mnq.back().second >= mnl[i][j]){
                mnq.pop_back();
            }
            mxq.emplace_back(i, mxl[i][j]);
            mnq.emplace_back(i, mnl[i][j]);
        }
        mxh[n - 1][j] = mxq.front().second;
        mnh[n - 1][j] = mnq.front().second;
        ans = min(ans, mxh[n - 1][j] - mnh[n - 1][j]);
        for(int i = n; i < a; i++){
            while(!mxq.empty() && mxq.front().first <= i - n){
                mxq.pop_front();
            }
            while(!mnq.empty() && mnq.front().first <= i - n){
                mnq.pop_front();
            }
            while(!mxq.empty() && mxq.back().second <= mxl[i][j]){
                mxq.pop_back();
            }
            while(!mnq.empty() && mnq.back().second >= mnl[i][j]){
                mnq.pop_back();
            }
            mxq.emplace_back(i, mxl[i][j]);
            mnq.emplace_back(i, mnl[i][j]);
            ans = min(ans, mxq.front().second - mnq.front().second);
        }
    }

    printf("%d\n", ans);
}