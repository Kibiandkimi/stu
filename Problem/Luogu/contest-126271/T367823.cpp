//
// Created by kibi on 23-8-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 100000, MaxA = 100000;

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

    class TreeArray{
        int data[4 * MaxA + 5]{}, n;

    public:
        explicit TreeArray(int n):n(n){}

        void add(int x){
            while(x <= n){
                data[x]++;
                x += (x&-x);
            }
        }

        int query(int x){
            int res = 0;
            while(x){
                res += data[x];
                x -= (x&-x);
            }
            return res;
        }
    };

    auto read = Tools::read;

    int n;
    read(n);

    static int raw_data[N + 5], bucket[MaxA + 5], max_a = 0;
    for(int i = 1; i <= n; i++){
        read(raw_data[i]);
        bucket[raw_data[i]]++;
        max_a = max(max_a, raw_data[i]);
    }

    static int pre_sum_of_bucket[MaxA + 5];
    for(int i = 1; i <= max_a; i++){
        pre_sum_of_bucket[i] = pre_sum_of_bucket[i - 1] + bucket[i];
    }

    static TreeArray tree(max_a);

    static int num_of_left[N + 5], num_of_right[N + 5];
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        int tot = n - pre_sum_of_bucket[raw_data[i]], pre = tree.query(max_a) - tree.query(raw_data[i]);
        num_of_left[i] = pre, num_of_right[i] = tot - pre;
        ans += min(num_of_left[i], num_of_right[i]);
        tree.add(raw_data[i]);
    }

    printf("%lld\n", ans);
}