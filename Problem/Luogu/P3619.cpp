//
// Created by Kibi on 24-8-2.
//
#include <bits/stdc++.h>
using namespace std;

enum Result {
    Ok,
    Fail,
};

int main(){
    auto read = []{
        uint s = 0, c = getchar();
        while(c < '0' || '9' < c){
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        return s;
    };

    auto readi = []{
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
        return s * w;
    };

    auto Z = read();

    while(Z--){
        using U = tuple<long long, long long>;

        auto n = read();
        long long T = readi();
        vector<U> tasks(n);
        for(auto &i : tasks){
            i = {readi(), readi()};
        }

        sort(tasks.begin(), tasks.end(), [](const U &a, const U &b){
            if(get<1>(a) >= 0 && get<1>(b) >= 0){
                return get<0>(a) < get<0>(b);
            }
            if(get<1>(a) >= 0 || get<1>(b) >= 0){
                return get<1>(a) >= 0;
            }
            return get<0>(a) + get<1>(a) > get<0>(b) + get<1>(b);
        });

        auto calc = [&tasks, T] {
            auto temp = T;
            for(auto &i : tasks) {
                if(temp <= get<0>(i) || temp + get<1>(i) <= 0) {
                    return Fail;
                }
                temp += get<1>(i);
            }
            return Ok;
        };

        switch (calc()) {
            case Ok:
                printf("+1s\n");break;
            case Fail:
                printf("-1s\n");
        }
    }
}