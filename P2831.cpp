//
// Created by kibi on 2021/10/3.
//
//^
#include <bits/stdc++.h>
using namespace std;
int T,n,m,lines[25][25],st[1<<19],dp[1<<19];
double eps = 1e-8,x[25],y[25];
void eq(double &a, double &b, int i, int j){
    a= -(y[i]*x[j]-y[j]*x[i])/(x[j]*x[j]*x[i]-x[i]*x[i]*x[j]);
    b= (y[i]*x[j]*x[j]-y[j]*x[i]*x[i])/(x[i]*x[j]*x[j]-x[j]*x[i]*x[i]);
}
int main(){
    scanf("%d", &T);
    for(int i = 0; i < (1<<18); i++){
        int j = 1;
        for(;j<=18&&i&1<<(j-1);j++);
        st[i]=j;
    }
    while(T--){
        memset(lines, 0, sizeof(lines));
        memset(dp, 1, sizeof(dp));
        dp[0] = 0;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++){
            scanf("%lf %lf", &x[i], &y[i]);
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(fabs(x[i]-x[j])<eps){
                    continue;
                }
                double a,b;
                eq(a,b,i,j);
                if(a>-eps){
                    continue;
                }
                for(int k = 1; k <= n; k++){
                    if(fabs(a*x[k]*x[k]+b*x[k]-y[k])<eps){
                        lines[i][j]|=(1<<(k-1));
                    }
                }
            }
        }
        for(int i = 0; i < (1<<n); i++){
            int j = st[i];
            dp[i|1<<(j-1)] = min(dp[i|1<<(j-1)],dp[i]+1);
            for(int k = 1; k <= n; k++){
                dp[i|lines[j][k]] = min(dp[i|lines[j][k]],dp[i]+1);
            }
        }
        printf("%d\n", dp[(1<<n)-1]);
    }
}

// 2023/8/23

/*

#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 18;
    static const double eps = 1e-8;

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

        static void read(double &x){
            double s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c){
                if(c == '-'){
                    w = -1;
                }
                c = getchar();
            }
            int cnt = 0;
            while('0' <= c && c <= '9' || c == '.'){
                if(c == '.'){
                    cnt = 1;
                }else{
                    if(cnt){
                        s = s + (c - '0') / pow(10, cnt);
                        cnt++;
                    }else{
                        s = s * 10 + c - '0';
                    }
                }
                c = getchar();
            }
            x = s * w;
        }

        static void solve(double &a, double &b, double x1, double y1, double x2, double y2){
            // y1 = ax_1^2 + bx_1
            // y2 = ax_2^2 + bx_2
            // y1/x1 = ax1 + b
            // b = y1/x1 - ax1
            // y2/x2 = ax2 + b
            // b = y2/x2 - ax2
            // y1/x1 - ax1 = y2/x2 - ax2
            // y1/x1 - y2/x2 = a(x1 - x2)
            // a = (y1/x1 - y2/x2) / (x1 - x2);
            a = (y1/x1 - y2/x2) / (x1 - x2);
            b = (y1/x1 + y2/x2 - a * (x1 + x2)) / 2;
        }

        static bool equal(double x, double y, double a, double b){
            return (fabs(a*(x*x) + b*x - y) < eps);
        }
    };

    class Pig{
    public:
        double x, y;
    };

    static int pre[1 << N];

    for(int i = 0; i < (1 << N) - 1; i++){
        static int j;
        j = 0;
        while(j < N && (i & (1 << j))){
            j++;
        }
        pre[i] = j;
    }

    int T;
    Tools::read(T);

    static int f[1 << N];

    while(T--){
        static int n, m;
        Tools::read(n), Tools::read(m);

        static Pig pig[N + 5];
        for(int i = 0; i < n; i++){
            static double x, y;
            Tools::read(x), Tools::read(y);
            pig[i] = {x, y};
        }

        static int line[N + 5][N + 5];
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                line[i][j] = line[j][i] = 0;

                if(fabs(pig[i].x - pig[j].x) < eps){
                    continue;
                }

                static double a, b;
                Tools::solve(a, b, pig[i].x, pig[i].y, pig[j].x, pig[j].y);

                if(a > -eps){
                    continue;
                }

                line[i][j] = (1 << i) | (1 << j);

                for(int k = 0; k < n; k++){
                    if(Tools::equal(pig[k].x, pig[k].y, a, b)){
                        line[i][j] |= (1 << k);
                    }
                }
                line[j][i] = line[i][j];
            }
        }

        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        for(int i = 0; i < (1 << n) - 1; i++){
            static int j;
            j = pre[i];
            f[i | (1 << j)] = min(f[i | (1 << j)], f[i] + 1);
            for(int k = 0; k < n; k++){
                f[i | line[j][k]] = min(f[i | line[j][k]], f[i] + 1);
            }
        }
        printf("%d\n", f[(1 << n) - 1]);
    }
}

 * */