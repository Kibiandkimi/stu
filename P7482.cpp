//
// Created by kibi on 23-9-30.
//

// TODO not finish

#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;
    static const int N = 100000, Mod = 1000000007;

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

        static void add(int &x, int val){
            x = (x + val) % Mod;
        }

        static int sub(int a, int b){
            return (int)((ll)a * b % Mod);
        }
    };

    auto read = Tools::read;

    static int n;
    read(n);

    static int raw_data[N + 5];
    for(int i = 1; i <= n; i++){
        read(raw_data[i]);
    }

    static int ans;

    class Work{
        static void solve(int l, int r){
            auto add = Tools::add;
            auto sub = Tools::sub;
            static ll pre_f[N + 5][2], pre_g[N + 5][2];
            static int order_f[N + 5], order_g[N + 5];
            if(l == r){
                add(ans, raw_data[l]);
                return;
            }

            int mid = (l + r) >> 1;
            solve(l, mid);
            solve(mid + 1, r);

            static ll d[N + 5][2][2]; // j->self k->mid
            d[mid][0][0] = d[mid][1][0] = d[mid][0][1] = 0, d[mid][1][1] = raw_data[mid];
            pre_f[mid][0] = 0, pre_f[mid][1] = raw_data[mid];
            order_f[1] = mid;
            for(int i = mid - 1; i >= l; i--){
                d[i][1][0] = d[i + 1][0][0] + raw_data[i];
                d[i][1][1] = max(d[i + 1][0][1], d[i + 1][0][0]) + raw_data[i];
                d[i][0][0] = max(d[i + 1][1][0], d[i + 1][0][0]);
                d[i][0][1] = max({d[i][0][0], d[i + 1][1][1], d[i + 1][0][1]});
                pre_f[i][0] = max(d[i][1][0], d[i][0][0]);
                pre_f[i][1] = max(d[i][1][1], d[i][0][1]);
                order_f[mid - i + 1] = i;
            }

            order_g[1] = mid + 1;
            d[mid + 1][0][0] = d[mid + 1][1][0] = d[mid + 1][0][1] = 0, d[mid + 1][1][1] = raw_data[mid + 1];
            pre_g[mid + 1][0] = 0, pre_g[mid + 1][1] = raw_data[mid + 1];
            for(int i = mid + 2; i <= r; i++){
                d[i][1][0] = d[i - 1][0][0] + raw_data[i];
                d[i][1][1] = max(d[i - 1][0][1], d[i - 1][0][0]) + raw_data[i];
                d[i][0][0] = max(d[i - 1][0][0], d[i - 1][1][0]);
                d[i][0][1] = max({d[i][0][0], d[i - 1][1][1], d[i - 1][0][1]});
                pre_g[i][0] = max(d[i][0][0], d[i][1][0]);
                pre_g[i][1] = max(d[i][0][1], d[i][1][1]);
                order_g[i - mid] = i;
            }

            auto cmp_f = [&](int a, int b){
                return pre_f[a][0] - pre_f[a][1] < pre_f[b][0] - pre_f[b][1];
            };
            sort(order_f + 1, order_f + 1 + mid - l + 1, cmp_f);

            auto cmp_g = [&](int a, int b){
                return pre_g[a][0] - pre_g[a][1] < pre_g[b][0] - pre_g[b][1];
            };
            sort(order_g + 1, order_g + 1 + r - mid, cmp_g);

            static int f[N + 5][2], g[N + 5][2];
            for(int i = l; i <= mid; i++){
                f[i][0] = (int)(pre_f[i][0] % Mod);
                f[i][1] = (int)(pre_f[i][1] % Mod);
            }
            for(int i = mid + 1; i <= r; i++){
                g[i][0] = (int)(pre_g[i][0] % Mod);
                g[i][1] = (int)(pre_g[i][1] % Mod);
            }

            // f0l + g1r >= f1l + g0r
            // f0l - f1l >= g0r - g1r

            int it_l, it_r, sum;

            for(it_l = 1, it_r = 1, sum = 0; it_l <= mid - l + 1 && it_r <= r - mid; it_r++){
                while(pre_f[order_f[it_l]][0] - pre_f[order_f[it_l]][1] < pre_g[order_g[it_r]][0] - pre_g[order_g[it_r]][1]
                       && it_l <= mid - l + 1){
                    it_l++;
                }
                if(it_l > mid - l + 1){
                    break;
                }
                add(sum, g[order_g[it_r]][1]);
                add(ans, sum);
                add(ans, sub(f[order_f[it_l]][0], it_r));
            }
            it_l++;
            while(it_l <= mid - l + 1){
                add(ans, sum);
                add(ans, sub(f[order_f[it_l]][0], it_r - 1));
                it_l++;
            }


            // f0l + g1r < f1l + g0r
            // f0l - f1l < g0r - g1r

            for(it_l = 1, it_r = 1, sum = 0; it_l <= mid - l + 1 && it_r <= r - mid; it_l++){
                while(pre_f[order_f[it_l]][0] - pre_f[order_f[it_l]][1] >= pre_g[order_g[it_r]][0] - pre_g[order_g[it_r]][1] && it_r <= r - mid){
                    it_r++;
                }
                if(it_r > r - mid){
                    break;
                }
                add(sum, f[order_f[it_l]][1]);
                add(ans, sum);
                add(ans, sub(g[order_g[it_r]][0], it_l));
            }
            it_r++;
            while(it_r <= r - mid){
                add(ans, sum);
                add(ans, sub(g[order_g[it_r]][0], it_l - 1));
                it_r++;
            }
        }

    public:
        Work(){
            solve(1, n);
        }
    };

    Work();

    printf("%d\n", ans);
}