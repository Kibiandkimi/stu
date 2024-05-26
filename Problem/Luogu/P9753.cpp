//
// Created by kibi on 23-10-28.
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

        static void read_(vector<int> &x){
            auto judge = [](int c){return 'a' <= c && c <= 'z';};
            int c;
            c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            while(judge(c)){
                x.emplace_back(c);
                c = getchar();
            }
            x.shrink_to_fit();
        }
    };

    auto read = Tools::read;

    vector<int> str;
    Tools::read_(str);

    int pre[str.size()], f[str.size()];
    for(int i = 0; i < str.size(); i++){
        pre[i] = i - 1;
    }
    for(int i = 1; i < str.size(); i++){
        while(str[pre[i]] != str[i]){
            pre[i] = pre[pre[i]] - 1;
            if(pre[i] < 0){
                break;
            }
        }
    }
    long long ans = 0;
    for(int i = 0; i < str.size(); i++){
        f[i] = 0;
        if(pre[i] > 0){
            f[i] = f[pre[i] - 1] + 1;
            ans += f[i];
        }else if(pre[i] == 0){
            f[i] = 1;
            ans += f[i];
        }
    }

    printf("%lld\n", ans);
}