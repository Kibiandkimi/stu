//
// Created by kibi on 23-10-30.
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

    class BIT{
        vector<int> data;
        int n;

    public:
        explicit BIT(int n):n(n), data(n + 1, 0){}

        void add(int pos, int val){
            pos++;
            while(pos <= n){
                data[pos] += val;
                pos += pos & -pos;
            }
        }

        int query(int pos){
            pos++;
            int sum = 0;
            while(pos){
                sum += data[pos];
                pos -= pos & -pos;
            }
            return sum;
        }
    };

    auto read = Tools::read;

    static int n;
    read(n);

    n <<= 1;

    static auto mp = [](int pos){return pos > 0 ? pos + (n >> 1) - 1 : - pos - 1;};

    BIT bit(n);
    vector<int> pos[n];
    int raw_data[n];
    for(int i = 0; i < n; i++){
        int siz;
        read(siz);
        raw_data[i] = siz;
        pos[mp(siz)].emplace_back(i);
        bit.add(i, 1);
    }

    bool vis[n];
    memset(vis, 0, sizeof vis);
    long long ans = 0;
    for(int i = n - 1; i >= 0; i--){
        if(vis[i]){
            continue;
        }
        vis[i] = true;
        int now = mp(raw_data[i]);
        pos[now].pop_back();
        int nxt = pos[mp(-raw_data[i])].back();
        pos[mp(-raw_data[i])].pop_back();
        vis[nxt] = true;
        ans = ans + (bit.query(i - 1) - bit.query(nxt)) + ((raw_data[i] < 0) ? 1 : 0);
        bit.add(nxt, -1);
    }

    printf("%lld\n", ans);
}