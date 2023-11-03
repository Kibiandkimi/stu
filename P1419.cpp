//
// Created by kibi on 23-11-3.
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

    static int n, s, t;
    read(n), read(s), read(t);

    int data_[n];
    for(auto &i : data_){
        read(i);
    }

    using ll = long long;

    double sum_[n];
    sum_[0] = data_[0];
    for(int i = 1; i < n; i++){
        sum_[i] = sum_[i - 1] + data_[i];
    }

    static int *data = data_;
    static double *sum = sum_;
    auto judge = [](double k){
        double res = -1000000000;

        deque<pair<int, double>> q;

        for(int i = 0; i < n; i++){
            sum[i] -= (i + 1) * k;
        }

        for(int i = s - 1; i < t; i++){
            while(!q.empty() && q.back().second < sum[i]){
                q.pop_back();
            }
            q.emplace_back(i, sum[i]);
        }

        int i, l, r;

        for(i = 0, l = s - 1, r = t - 1; r < n - 1; i++, l++, r++){
            while(!q.empty() && q.front().first < l){
                q.pop_front();
            }
            res = max(res, q.front().second - (!i ? 0 : sum[i - 1]));
            while(!q.empty() && q.back().second < sum[r + 1]){
                q.pop_back();
            }
            q.emplace_back(r + 1, sum[r + 1]);
        }

        for(; l < n; i++, l++){
            while(!q.empty() && q.front().first < l){
                q.pop_front();
            }
            res = max(res, q.front().second - (!i ? 0 : sum[i - 1]));
        }

        for(i = 0; i < n; i++){
            sum[i] += (i + 1) * k;
        }

        return res >= 0;
    };

    double l = -1000000000, r = 1000000000, res = -1000000000;
    while(l <= r){
        double mid = (l + r) / 2.0;
        if(judge(mid)){
            res = mid;
            l = mid + 0.0001;
        }else{
            r = mid - 0.0001;
        }
    }

    printf("%.3lf\n", res);
}