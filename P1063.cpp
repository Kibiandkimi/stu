#include <bits/stdc++.h>
using namespace std;
int n;
int a[205][2];
int v[205][205];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i][0]);
        a[i - 1][1] = a[i][0];
        a[i + n][0] = a[i][0];
        a[i - 1 + n][1] = a[i - 1][1];
    }
    a[n][1] = a[1][0];
    a[n + n][1] = a[n][1];
    for (int i = 1; i <= n; i++) {
        for (int l = 1; l + i - 1 <= 2 * n; l++) {
            for (int j = l; j < l + i - 1; j++) {
                v[l][l + i - 1] = max(v[l][l + i - 1], v[l][j] + v[j + 1][l + i - 1] + a[l][0] * a[j + 1][0] * a[l + i - 1][1]);
            }
        }
    }
    int t = 0;
    for (int i = 1; i <= n; i++) {
        t = max(t, v[i][i + n - 1]);
    }
    printf("%d", t);
}