//
// Created by kibi on 23-10-31.
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

    bool data[n][m];
    int high[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int t;
            read(t);
            data[i][j] = t ^ ((i + j) & 1);
            if(!i){
                high[i][j] = 1;
            }else{
                high[i][j] = (data[i][j] == data[i - 1][j]) ? high[i - 1][j] + 1 : 1;
            }
        }
    }

    int mxl[n][m], mxr[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!j){
                mxl[i][j] = 0;
            }else{
                mxl[i][j] = (data[i][j] == data[i][j - 1]) ? mxl[i][j - 1] : j;
            }
        }

        for(int j = m - 1; j >= 0; j--){
            if(j == m - 1){
                mxr[i][j] = m - 1;
            }else{
                mxr[i][j] = (data[i][j] == data[i][j + 1]) ? mxr[i][j + 1] : j;
            }
        }
    }

    int ans1 = 0, ans2 = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(i && data[i][j] == data[i - 1][j]){
                mxl[i][j] = max(mxl[i][j], mxl[i - 1][j]);
                mxr[i][j] = min(mxr[i][j], mxr[i - 1][j]);
            }
            int a = mxr[i][j] - mxl[i][j] + 1, b = min(a, high[i][j]);
            if(a < 0){
                throw exception();
            }
            ans1 = max(ans1, b * b);
            ans2 = max(ans2, a * high[i][j]);
        }
    }

    printf("%d\n%d\n", ans1, ans2);
}