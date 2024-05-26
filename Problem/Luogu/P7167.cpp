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

    class Plate{
    public:
        int d, c;
    };

    int n, q;
    read({&n, &q});

    Plate plate[n];
    for(auto &i : plate){
        read({&i.d, &i.c});
    }
    stack<int> stk;
    int nxt[n][20];
    int sum[n][20];
    for(int i = 0; i < n; i++){
        while(!stk.empty() && plate[stk.top()].d < plate[i].d){
            nxt[stk.top()][0] = i;
            sum[stk.top()][0] = plate[i].c;
            stk.pop();
        }
        stk.emplace(i);
    }
    while(!stk.empty()){
        nxt[stk.top()][0] = -1;
        sum[stk.top()][0] = 0;
        stk.pop();
    }

    for(int i = 1; i < 20; i++){
        for(int j = 0; j < n; j++){
            if(nxt[j][i - 1] == -1){
                nxt[j][i] = -1;
                sum[j][i] = sum[j][i - 1];
                continue;
            }
            nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
            sum[j][i] = sum[j][i - 1] + sum[nxt[j][i - 1]][i - 1];
        }
    }

    while(q--){
        int r, v;
        read({&r, &v});
        r--;
        v -= plate[r].c;
        if(v <= 0){
            printf("%d\n", r + 1);
            continue;
        }
        if(v > sum[r][19]){
            printf("0\n");
            continue;
        }
        int now = r;
        for(int i = 19; i >= 0; i--){
            if(sum[now][i] < v){
                v -= sum[now][i];
                now = nxt[now][i];
            }
        }
        now = nxt[now][0];
        printf("%d\n", now + 1);
    }

}