//
// Created by kibi on 2022/6/19.
//
//太难了，待理解
#include <bits/stdc++.h>
using namespace std;
int T;
int a[1000005], b[1000005];
//a[i]以i结尾的AA, b[i]以i开头的AA
struct SA{
    char S[1000005]; //字符串
    int n; //长度

    int sa[1000005], rk[1000005], cnt[1000005], height[1000005];//SA

    int st[1000005][25], lg2[1000005];//st表

    struct node{
        int id, x, y;
    }aa[1000005], bb[1000005];

    void build_sa(){
        n = strlen(S + 1);

        memset(cnt, 0, sizeof cnt);
        memset(height, 0, sizeof height);
        memset(sa, 0, sizeof sa);
        memset(rk, 0, sizeof rk);

        for(int i = 1; i <= n; i++){
            aa[i].id = aa[i].x = aa[i].y = bb[i].id = bb[i].x = bb[i].y = 0;
        }

        //按首字母计数排序（桶排序？）
        for(int i = 1; i <= n; i++){
            cnt[S[i]] = 1;
        }
        for(int i = 1; i <= 256; i++){
            cnt[i] += cnt[i-1];
        }
        for(int i = 1; i <= n; i++){
            rk[i] = cnt[S[i]];
        }

        //基数排序？ + 倍增
        for(int L = 1; L < n; L *= 2){
            for(int i = 1; i <= n; i++){
                aa[i].id = i;
                aa[i].x = rk[i];
                aa[i].y = rk[i + L];
            }

            for(int i = 1; i <= n; i++){
                cnt[i] = 0;
            }
            for(int i = 1; i <= n; i++){
                cnt[aa[i].y]++;
            }
            for(int i = 1; i <= n; i++){
                cnt[i] += cnt[i - 1];
            }
            for(int i = n; i >= 1; i--){
                bb[ cnt[aa[i].y]-- ] = aa[i];
            }

            for(int i = 1; i <= n; i++){
                cnt[i] = 0;
            }
            for(int i = 1; i <= n; i++){
                cnt[aa[i].x]++;
            }
            for(int i = 1; i <= n; i++){
                cnt[i] += cnt[i - 1];
            }
            for(int i = n; i >= 1; i--){
                aa[ cnt[bb[i].x]-- ] = bb[i];
            }

            for(int i = 1; i <= n; i++){
                if(aa[i].x==aa[i-1].x && aa[i].y==aa[i-1].y){
                    rk[aa[i].id] = rk[aa[i-1].id];
                }else {
                    rk[aa[i].id] = rk[aa[i-1].id] + 1;
                }
            }
        }

        for(int i = 1; i <= n; i++){
            sa[rk[i]] = i;
        }

        int k = 0;
        for(int i = 1; i <= n; i++){
            if(k){
                k--;
            }
            int j = sa[rk[i] - 1];
            while(i+k<=n && j+k<=n && S[i+k]==S[j+k]){
                k++;
            }
            height[rk[i]] = k;
        }
    }

    void build_st(){
        lg2[0] = -1;
        for(int i = 1; i < 1000005; i++){
            lg2[i] = lg2[i/2] + 1;
        }
        lg2[0] = 0;
        for(int i = 1; i <= n; i++){
            st[i][0] = height[i];
        }
        for(int j = 1; (1 << j) <= n; j++){
            for(int i = 1; i + (1 << j) - 1 <= n; i++){
                st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }

    int lcp(int l, int r){
        l = rk[l], r = rk[r];
        if(l > r){
            swap(l, r);
        }
        l++;
        int k = lg2[r-l+1];
        return min(st[l][k], st[r - (1<<k) + 1][k]);
    }
}Sa[2];
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%s", Sa[0].S+1);

        int n = strlen(Sa[0].S+1);
        for(int i = 1; i <= n; i++){
            a[i] = b[i] = 0;
        }
        for(int i = 1; i <= n; i++){
            Sa[1].S[i] = Sa[0].S[n-i+1];
        }
        Sa[0].build_sa();
        Sa[1].build_sa();
        Sa[0].build_st();
        Sa[1].build_st();

        for(int Len = 1; Len <= n/2; Len++){
            for(int i = Len; i <= n; i += Len){
                int l = i, r = i + Len, L = n - (r - 1) + 1, R = n - (l - 1) + 1;
                int lcp = Sa[0].lcp(l, r);
                lcp = min(lcp, Len);
                int lcs = Sa[1].lcp(L, R);
                lcs = min(lcs, Len - 1);
                if(lcp + lcs >= Len){
                    b[i - lcs]++;
                    b[i - lcs + (lcp + lcs - Len + 1)]--;
                    a[r + lcp]--;
                    a[r + lcp - (lcp + lcs - Len + 1)]++;
                }
            }
        }

        for(int i = 1; i <= n; i++){
            a[i] += a[i - 1];
            b[i] += b[i - 1];
        }
        long long s = 0;
        for(int i = 1; i < n; i++){
            s += a[i]*b[i+1];
        }
        printf("%lld\n", s);
    }
}