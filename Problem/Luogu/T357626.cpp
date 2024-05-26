#include <bits/stdc++.h>
using namespace std;

const int N = 500 * 2;

void read(int&);
void read(char*);

int main(){

//    TODO have not complete yet

    class Number{

    public:
        char a[245]{}, len{};
        Number(int raw){
            memset(a, 0, sizeof a);
            len = 0;
            while(raw){
                a[len++] = (char)(raw % 10);
                raw /= 10;
            }
        }

        Number(const Number *number){
            memset(a, 0, sizeof a);
            len = number->len;
            for(int i = 0; i < len; i++){
                a[i] = number -> a[i];
            }
        }

        Number(){
            memset(a, 0, sizeof a);
            len = 0;
        }

        void operator += (const Number &b){
            len = max(len, b.len);
            for(int i = 0; i < len; i++){
                a[i] += b.a[i];
                a[i+1] += a[i]/10;
                a[i] %= 10;
            }
            a[len] ? len++ : 0;
        }

        bool operator == (const Number &b) const{
            if(len != b.len){
                return false;
            }
            for(int i = 0; i < len; i++){
                if(a[i] != b.a[i]){
                    return false;
                }
            }
            return true;
        }

        bool operator != (const Number &b) const{
            return !(Number(this) == b);
        }
    };

    int n, k;
    static int p[N + 5][N + 5], s[N + 5][N + 5];
    read(n), read(k);
    n*=2;
    while(k--){
        int x, y;
        char ch[2];
        read(x), read(ch), read(y);
        if(ch[0] == '<' && ch[1] == '='){
            p[x][y] = 2, p[y][x] = 4;
        }else if(ch[0] == '<'){
            p[x][y] = 1, p[x][y] = 5;
        }else if(ch[0] == '='){
            p[x][y] = p[y][x] = 3;
        }else if(ch[1] == '='){
            p[x][y] = 4, p[y][x] = 2;
        }else{
            p[x][y] = 5, p[y][x] = 1;
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            s[i][j] = s[i][j-1] + (p[i][j]>2);
        }
    }

    static Number f[N + 5][N + 5];

    f[1][n] = 0;

    for(int i = 1; i < n; i++){
        if(!p[i][i+1] || (p[i][i+1]>=2&&p[i][i+1]<=4)){
            f[i][i+1] = 1;
        }
    }

    for(int len = 2; len <= n; len += 2){
        for(int l = 1; l + len - 1 <= n; l++){
            int r = l + len -1;
            if(f[l][r] == 0){
                if(p[l][l+1] != 1 && p[l][l+1] != 5 && f[l+2][r] != 0){
                    if(!(s[l][r] - s[l][l+1]) && !(s[l+1][r] - s[l+1][l+1])){
                        f[l][r] += f[l+2][r];
                    }
                }
                if(p[r-1][r] != 1 && p[r-1][r]!=5&&f[l][r-2] != 0){
                    if(!(s[r][r-2]-s[r][l-1])&&!(s[r-1][r-2]-s[r-1][l-1])){
                        f[l][r] += f[l][r-2];
                    }
                }
                if(p[l][r] != 1 && p[l][r]!=5 && f[l+1][r-1]!=0){
                    if(!(s[l][r-1]-s[l][l]) && !(s[r][r-1]-s[r][l])){
                        f[l][r] += f[l+1][r-1];
                    }
                }
            }
        }
    }

    for(int i = f[1][n].len-1; i >= 0; i--){
        printf("%d", (int)f[1][n].a[i]);
    }

    if(f[1][n].len == 0){
        printf("0\n");
    }

}

void read(char *x){
    int c = getchar();
    while(c != '<' && c != '>' && c != '='){
        c = getchar();
    }
    int cnt = 0;
    while(c == '<' || c == '>' || c == '='){
        x[cnt++] = c;
        c = getchar();
    }
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