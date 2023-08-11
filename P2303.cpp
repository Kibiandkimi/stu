//
// Created by kibi on 23-8-11.
//


#include <bits/stdc++.h>
using namespace std;

int main(){
    class Tools{
    public:
        static void read(unsigned int &x){
            unsigned int s = 0, c = getchar();
            while(c < '0' || '9' < c){
                c = getchar();
            }
            while('0' <= c && c <= '9'){
                c = c - '0';
                s = s * 10 + c;
                c = getchar();
            }
            x = s;
        }
    };

    unsigned int n;

    Tools::read(n);

    long long ans = n;
    for (int i = 2; i*i <= n; ++i)
    {
        if(n % i == 0)
        {
            int b = 0;
            while(n % i == 0){
                ++b;
                n /= i;
            }
            ans /= i;
            ans *= b*i-b+i;
        }
    }
    if(n > 1)
    {
        ans /= n;
        ans *= n + n - 1;
    }
    printf("%lld\n", ans);
}