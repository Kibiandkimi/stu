//
// Created by kibi on 2022/8/3.
//
#include <bits/stdc++.h>
using namespace std;
int n;
char c[100005], s[200005];
int d[200005], ls[200005], rs[200005];

int main(){
    scanf("%s", c+1);
    n = strlen(c+1);

    s[0] = '#', s[1] = '$';
    int cnt = 1;
    for(int i = 1; i <= n; i++){
        s[++cnt] = c[i];
        s[++cnt] = '$';
    }
    n = (n+1)*2;
    s[n] = '~';

    int mid, r = 0;
    for(int i = 1; i <= n; i++){
        //        if(i > r){
        //            int j = 0;
        //            while(c[i+j]==c[i-j]&&c[i+j]!=0){
        //                j++;
        //            }
        //            j--;
        //            if(j >= 0){
        //                l = i-j;
        //                r = i+j;
        //            }
        //            d[i] = j+1;
        //        }else{
        //            if(d[l+r-i]+i > r){
        //                int j = 0;
        //                while(c[r+j]==c[i-(r-i)-j]&&c[r+j]!=0){
        //                    j++;
        //                }
        //                j--;
        //                d[i] =r+j-i-1;
        //                if(j > 0){
        //                    l = i-(r-i)-j;
        //                    r+=j;
        //                }
        //            }else{
        //                d[i] = d[l+r-i];
        //                if(i+d[i] > n){
        //                    d[i] = n-i;
        //                }
        //            }
        //        }
        if(i < r){
            d[i] = min(d[mid*2-i], r-i);
        }else{
            d[i] = 1;
        }
        while(s[i+d[i]]==s[i-d[i]]){
            d[i]++;
        }
        if(d[i]+i > r){
            r = d[i]+i;
            mid = i;
        }
        rs[i+d[i]-1] = max(rs[i+d[i]-1], d[i]-1);
        ls[i-d[i]+1] = max(ls[i-d[i]+1], d[i]-1);
        //        d[i] = (d[i]-1)/2;
    }

    for(int i = n; i >= 1; i -= 2){
        rs[i] = max(rs[i], rs[i+2]-2);
    }

    for(int i = 3; i <= n; i+=2){
        ls[i] = max(ls[i], ls[i-2]-2);
    }
    int ans = 0;
    for(int i = 1; i <= n; i+=2){
        if(rs[i]&&ls[i]){
            ans = max(ans, rs[i]+ls[i]);
        }
    }
    printf("%d", ans);
}