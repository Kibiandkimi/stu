//
// Created by kibi on 23-7-19.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 10000, M = 5000;

void read(int&);

int main(){

    class Aim{
    public:
        int x, y, v;
        static bool cmp(Aim a, Aim b){
            return a.y == b.y ? a.x < b.x : a.y < b.y;
        };
    };

    static Aim aim[N+5], sum[4*N+5];
    int n, m, cnt = 0;

    read(n), read(m);

    for(int i = 1; i <= n; i++){
        read(aim[i].x), read(aim[i].y), read(aim[i].v);

        sum[++cnt] = {aim[i].x-(m), aim[i].y-(m), aim[i].v};
        sum[++cnt] = {aim[i].x-(m), aim[i].y, -aim[i].v};
        sum[++cnt] = {aim[i].x, aim[i].y-(m), -aim[i].v};
        sum[++cnt] = {aim[i].x, aim[i].y, aim[i].v};
    }

    for(int i = 1; i <= 4*n; i++){
        (sum[i].x < 0) && (sum[i].x = -1);
        (sum[i].y < 0) && (sum[i].y = -1);
    }

    sort(sum+1, sum+1+4*n, Aim::cmp);

    int res[M+10][2] = {0}, ans = 0, now = 1;

    for(int i = -1; i <= M+3; i++){
        //        i -> y
        for(int j = -1; j <= M+3; j++){
            //                j -> x
            if(sum[now].x != j || sum[now].y != i){
                res[j+2][(i+1)%2] = res[j+1][(i+1)%2] + res[j+2][((i+1)%2)^1] - res[j+1][((i+1)%2)^1];
            }else{
                res[j+2][(i+1)%2] = 0;
                while(sum[now].x == j && sum[now].y == i){
                    res[j+2][(i+1)%2] += sum[now].v;
                    now++;
                }
                res[j+2][(i+1)%2] += res[j+1][(i+1)%2] + res[j+2][((i+1)%2)^1] - res[j+1][((i+1)%2)^1];
            }
            ans = max(ans, res[j+2][(i+1)%2]);
        }
    }

    //    cout << (-1)%2;
    printf("%d\n", ans);

}

void read(int &x){
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