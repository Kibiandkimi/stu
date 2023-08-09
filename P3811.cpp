//
// Created by kibi on 22-8-25.
//
#include <bits/stdc++.h>
using namespace std;
int inv[3000005], n, p;

int main(){
    scanf("%d %d", &n, &p);
    inv[1] = 1;
    for(int i = 2; i <= n; i++){
        inv[i] = (long long)(p-p/i)*inv[p%i]%p;
    }
    for(int i = 1; i <= n; i++){
        printf("%d\n", inv[i]);
    }
}

// 2023/8/9

/*

#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 3000000;

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
    static int inv[N + 5];

    int n, p;
    read(n), read(p);

    inv[1] = 1;
    for(int i = 2; i <= n; i++){
        inv[i] = (int)((long long)(p - p/i) * inv[p % i] % p);
    }

    for(int i = 1; i <= n; i++){
        printf("%d\n", inv[i]);
    }
}

 * */