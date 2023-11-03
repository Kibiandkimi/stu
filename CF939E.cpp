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

    int m;
    read(m);

    double avg = 0;
    double mx = 0;
    int num = 0;

    vector<int> st{0};
    while(m--){
        int opt;
        read(opt);
        if(opt == 1){
            int t;
            read(t);
            st.emplace_back(t);
            double now = avg + (((double)t - avg) / (double)(num + 1.0));
            int now_num = num + 1;
            while(now_num < st.size()){
                if(st[now_num] < now){
                    now = now + (((double)st[now_num] - now) / (double)(now_num + 1));
                    now_num++;
                }else{
                    break;
                }
            }
            mx = max(mx, t - now);
            num = now_num - 1;
            if(!num){
                avg = 0;
                continue;
            }
            avg = now - ((double)(t - now) / (double)(now_num - 1));
        }else if(opt == 2){
            printf("%lf\n", mx);
        }
    }
}