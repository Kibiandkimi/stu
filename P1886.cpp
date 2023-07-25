//
// Created by kibi on 23-7-20.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

void read(int&);

int main(){
    int n, k;
    read(n), read(k);
    static int a[N+5];
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }
    static deque<pair<int, int> > q_min, q_max;
    //    q_min - up, q_max down
    for(int i = 1; i <= k; i++){
        while(!q_min.empty() && a[i] <= q_min.back().first){
            q_min.pop_back();
        }
        while(!q_max.empty() && a[i] >= q_max.back().first){
            q_max.pop_back();
        }
        q_min.emplace_back(a[i], i);
        q_max.emplace_back(a[i], i);
    }

    int ans_max[N+5] = {0, q_max.front().first}, ans_min[N+5] = {0, q_min.front().first};

    for(int i = k+1; i <= n; i++){
        if(!q_min.empty() && q_min.front().second < i-k+1){
            q_min.pop_front();
        }
        if(!q_max.empty() && q_max.front().second < i-k+1){
            q_max.pop_front();
        }
        while(!q_min.empty() && a[i] <= q_min.back().first){
            q_min.pop_back();
        }
        while(!q_max.empty() && a[i] >= q_max.back().first){
            q_max.pop_back();
        }
        q_min.emplace_back(a[i], i);
        q_max.emplace_back(a[i], i);
        ans_min[i-k+1] = q_min.front().first;
        ans_max[i-k+1] = q_max.front().first;

    }

    for(int i = 1; i <= n-k+1; i++){
        printf("%d ", ans_min[i]);
    }
    printf("\n");
    for(int i = 1; i <= n-k+1; i++){
        printf("%d ", ans_max[i]);
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if (c == '-'){
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