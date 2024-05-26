//
// Created by kibi on 22-9-4.
//
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int n, k;
long long dp[505][505][6];
char s[505];

void read(int &x);

int main(){
    read(n), read(k);
    scanf("%s", s+1);
    for(int i = 1; i <= n; i++){
        dp[i][i-1][0] = 1;
    }
    for(int len = 1; len <= n; len++){
        for(int l = 1; l <= n-len+1; l++){
            int r = l+len-1;
            if(len <= k){
                dp[l][r][0] = dp[l][r-1][0]&&(s[r]=='*'||s[r]=='?');
            }
            if(len >= 2){
                if((s[l]=='('||s[l]=='?')&&(s[r]==')'||s[r]=='?')){
                    dp[l][r][1] = (dp[l+1][r-1][0]+dp[l+1][r-1][2]+dp[l+1][r-1][3]+dp[l+1][r-1][4])%mod;
                }
                for(int i = l; i <= r-1; i++){
                    dp[l][r][2] = (dp[l][r][2]+dp[l][i][3]*dp[i+1][r][0])%mod;
                    dp[l][r][3] = (dp[l][r][3]+(dp[l][i][2]+dp[l][i][3])*dp[i+1][r][1])%mod;
                    dp[l][r][4] = (dp[l][r][4]+(dp[l][i][4]+dp[l][i][5])*dp[i+1][r][1])%mod;
                    dp[l][r][5] = (dp[l][r][5]+dp[l][i][4]*dp[i+1][r][0])%mod;
                }
            }
            dp[l][r][5] = (dp[l][r][5]+dp[l][r][0])%mod;
            dp[l][r][3] = (dp[l][r][3]+dp[l][r][1])%mod;
        }
    }
    printf("%lld\n", dp[1][n][3]);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

// 2023/8/24

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 500, Mod = 1000000007;

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

        static bool judge(const int &c){
            return (c == '(' || c == ')' || c == '*' || c == '?');
        }

        static bool check(const int &c, const int v){
            return c == '?' || c == v;
        }
    };

    auto read = Tools::read;

    int n, k;
    read(n), read(k);

    static int str[N + 5];
    int c = getchar();
    while(!Tools::judge(c)){
        c = getchar();
    }
    for(int i = 1; i <= n; i++){
        str[i] = c;
        c = getchar();
    }

    static int f[N + 5][N + 5][6];

    for(int i = 1; i <= n; i++){
        f[i][i - 1][0] = 1;
    }

    for(int len = 1; len <= n; len++){
        for(int l = 1; l <= (n - len + 1); l++){
            static auto check = Tools::check;
            int r = l + len - 1;
            if(len <= k){
                f[l][r][0] = f[l][r - 1][0] && check(str[r], '*');
            }
            if(len >= 2){
                if(check(str[l], '(') && check(str[r], ')')){
                    f[l][r][1] = (int)(((long long)
                                                 f[l + 1][r - 1][0] +
                                         f[l + 1][r - 1][2] +
                                         f[l + 1][r - 1][3] +
                                         f[l + 1][r - 1][4]
                                         ) % Mod);
                }
                for(int i = l; i < r; i++){
                    f[l][r][2] = (f[l][r][2] + f[l][i][3] * f[i + 1][r][0]) % Mod;
                    f[l][r][3] = (int)((f[l][r][3] +
                                         ((long long)f[l][i][2] + f[l][i][3]) * f[i + 1][r][1]) % Mod);
                    f[l][r][4] = (int)((f[l][r][4] +
                                         ((long long)f[l][i][4] + f[l][i][5]) * f[i + 1][r][1]) % Mod);
                    f[l][r][5] = (f[l][r][5] + f[l][i][4] * f[i + 1][r][0]) % Mod;
                }
            }
            f[l][r][3] = (f[l][r][3] + f[l][r][1]) % Mod;
            f[l][r][5] = (f[l][r][5] + f[l][r][0]) % Mod;
        }
    }
    printf("%d\n", f[1][n][3]);
}
 *
 * */