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

// 2024-4-11
/*
#include <bits/stdc++.h>
using namespace std;

class MonotonicQueue{
    deque<pair<int, int>> q;
    int cnt{0};

public:
    template<typename Cmp>
    void push(int v, Cmp cmp){
        while(!q.empty() && cmp(q.back().second, v)){
            q.pop_back();
        }
        q.emplace_back(++cnt, v);
    }

    void update(int v){
        while(!q.empty() && q.front().first <= v){
            q.pop_front();
        }
    }

    int get() const{
        return q.front().second;
    }
};

int main(){
    int n, k;
    cin >> n >> k;
    int data[n];
    for(auto &i : data){
        cin >> i;
    }

    auto less = [](const int &a, const int &b){
        return a <= b;
    };
    auto more = [](const int &a, const int &b){
        return a >= b;
    };

    MonotonicQueue q_min, q_max;
    for(int i = 0; i < k; i++){
        q_min.push(data[i], more);
        q_max.push(data[i], less);
    }

    int ans[n - k + 1][2];
    for(int i = k; i < n; i++){
        ans[i - k][0] = q_min.get();
        ans[i - k][1] = q_max.get();
        q_min.push(data[i], more);
        q_max.push(data[i], less);
        q_min.update(i - k + 1);
        q_max.update(i - k + 1);
    }
    ans[n - k][0] = q_min.get();
    ans[n - k][1] = q_max.get();
    for(int i = 0; i <= n - k; i++){
        printf("%d ", ans[i][0]);
    }
    printf("\n");
    for(int i = 0; i <= n - k; i++){
        printf("%d ", ans[i][1]);
    }
    printf("\n");
}
 * */