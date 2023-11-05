//
// Created by kibi on 23-11-4.
//

// TODO must use O2, try opt

#include <bits/stdc++.h>
using namespace std;

int main(){
    static const int Mod = 1024523;

    static auto read = [](int &x){
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

    static auto read_bool = [](bool &x){
        static auto judge = [](int c){return c == 'A' || c == 'B';};
        int c = getchar();
        while(!judge(c)){
            c = getchar();
        }
        x = c == 'A';
    };

    static auto add = [](int &a, const int b){
        a = (a + b) > Mod ? a + b - Mod : a + b;
    };

    static int n, m;
    read(n), read(m);

    bool raw_a[n], raw_b[m];
    for(auto &i : raw_a){
        read_bool(i);
    }
    for(auto &i : raw_b){
        read_bool(i);
    }

    class Node{
    public:
        vector<vector<int>> f;

        Node():f(n + 1, vector<int>(n + 1)){}
    };
    Node raw_f1, raw_f2;
    auto a = raw_a - 1, b = raw_b - 1;
    auto f1 = &raw_f1, f2 = &raw_f2;
    raw_f1.f[0][0] = 1;
    for(static int i = 1; i <= n + m; i++){
        swap(f1, f2);
        //        *f1 = Node();
        for (int j = max(0, i - m); j <= n; j++) {
            for (int k = max(0, i - m); k <= n; k++) {
                f1->f[j][k] = 0;
                if (j && k && a[j] == a[k]) {
                    add(f1->f[j][k], f2->f[j - 1][k - 1]);
                }
                if (j && i - k && a[j] == b[i - k]) {
                    add(f1->f[j][k], f2->f[j - 1][k]);
                }
                if (i - j && k && b[i - j] == a[k]) {
                    add(f1->f[j][k], f2->f[j][k - 1]);
                }
                if (i - j && i - k && b[i - j] == b[i - k]) {
                    add(f1->f[j][k], f2->f[j][k]);
                }
            }
        }
    }


    printf("%d\n", f1->f[n][n]);
}