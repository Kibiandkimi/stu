#include <bits/stdc++.h>
typedef unsigned long long ull;
const int N = 400000;
bool s[N + 1][256];

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, ull a1, ull a2) {
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 256; j++)
            s[i][j] = (myRand(a1, a2) & (1ull << 32)) != 0;
}
using namespace std;
int n, m;
ull a1, a2;
int main() {
    freopen("qi.in", "r", stdin);
    freopen("qi.out", "w", stdout);
    cin >> n >> m >> a1 >> a2;
    gen(n, a1, a2);
    char t[64];
    bool a[256];
    int kk;
    bool lsans = false;
    for (int i = 1; i <= m; i++) {

        scanf("%s %d", &t, &kk);
        for (int j = 0; j < 64; j++) {
            if (t[j] == '0') {
                a[j * 4] = a[j * 4 + 1] = a[j * 4 + 2] = a[j * 4 + 3] = false;
            } else if (t[j] == '1') {
                a[j * 4] = a[j * 4 + 1] = a[j * 4 + 2] = false;
                a[j * 4 + 3] = true;
            } else if (t[j] == '2') {
                a[j * 4] = a[j * 4 + 1] = a[j * 4 + 3] = false;
                a[j * 4 + 2] = true;
            } else if (t[j] == '3') {
                a[j * 4] = a[j * 4 + 1] = false;
                a[j * 4 + 2] = a[j * 4 + 3] = true;
            } else if (t[j] == '4') {
                a[j * 4] = a[j * 4 + 2] = a[j * 4 + 3] = false;
                a[j * 4 + 1] = true;
            } else if (t[j] == '5') {
                a[j * 4] = a[j * 4 + 2] = false;
                a[j * 4 + 1] = a[j * 4 + 3] = true;
            } else if (t[j] == '6') {
                a[j * 4] = a[j * 4 + 3] = false;
                a[j * 4 + 1] = a[j * 4 + 2] = true;
            } else if (t[j] == '7') {
                a[j * 4] = false;
                a[j * 4 + 1] = a[j * 4 + 2] = a[j * 4 + 3] = true;
            } else if (t[j] == '8') {
                a[j * 4] = true;
                a[j * 4 + 1] = a[j * 4 + 2] = a[j * 4 + 3] = false;
            } else if (t[j] == '9') {
                a[j * 4] = a[j * 4 + 3] = true;
                a[j * 4 + 2] = a[j * 4 + 1] = false;
            } else if (t[j] == 'A') {
                a[j * 4] = a[j * 4 + 2] = true;
                a[j * 4 + 1] = a[j * 4 + 3] = false;
            } else if (t[j] == 'B') {
                a[j * 4] = a[j * 4 + 2] = a[j * 4 + 3] = true;
                a[j * 4 + 1] = false;
            } else if (t[j] == 'C') {
                a[j * 4] = a[j * 4 + 1] = true;
                a[j * 4 + 2] = a[j * 4 + 3] = false;
            } else if (t[j] == 'D') {
                a[j * 4] = a[j * 4 + 1] = a[j * 4 + 3] = true;
                a[j * 4 + 2] = false;
            } else if (t[j] == 'E') {
                a[j * 4] = a[j * 4 + 1] = a[j * 4 + 2] = true;
                a[j * 4 + 3] = false;
            } else if (t[j] == 'F') {
                a[j * 4] = a[j * 4 + 1] = a[j * 4 + 2] = a[j * 4 + 3] = true;
            }
        }

        if(lsans){
            for(bool & j : a){
                j = !j;
            }
        }
        lsans = false;
        for (int j = 1; j <= n; j++) {
            int sum = 0;
            for (int k = 0; k < 256; k++) {
                sum += a[k] ^ s[j][k];
            }
            sum = kk - sum;
            if(sum >= 0){
                lsans = true;
                break;
            }
        }
        if(lsans){
            printf("%d\n", 1);
        }else{
            printf("%d\n", 0);
        }

    }

    fclose(stdin);
    fclose(stdout);
}