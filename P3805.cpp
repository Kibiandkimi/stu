//
// Created by kibi on 2022/7/8.
//
#include <bits/stdc++.h>
using namespace std;
char c[11000005];
int l, r, n;
int d1[11000005], d2[11000005];
int ans;
int main(){
    scanf("%s", c+1);
    for(int i = 1; c[i]!=0; i++){
        n++;
    }
    //    n = c.size();
    l = 0, r = -1;
    for(int i = 1; c[i]!=0; i++){
        if(i > r){
            int j;
            for(j = 0; (c[i-j]==c[i+j])&&(c[i+j]!=0); j++){
            }
            j--;
            if(j>=0) {
                l = i - j;
                r = i + j;
            }
            d1[i] = j+1;
        }else{
            if(d1[l+r-i]+i>r) {
                int j;
                for (j = 0; (c[r + j]==c[i - (r - i) - j]) && (c[r+j]!=0); j++) {
                }
                j--;
                d1[i] = r+j-i+1;
                if (j > 0) {
                    l = i - (r - i) - j;
                    r += j;
                }
                //                d1[i] = r - i + 1;
            }else{
                d1[i] = d1[l+r-i];
                if(i + d1[i] > n){
                    d1[i] = n-i;
                }
            }
        }
        ans = max(ans, d1[i]*2-1);
    }
    l = 0;
    r = -1;
    for(int i = 1; c[i+1]!=0; i++){
        if(i >= r){
            int j;
            for(j = 0; (c[i-j+1] == c[i+j]) && (c[i+j]!=0); j++){
            }
            j--;
            if(j > 0){
                r = i+j;
                l = i-j+1;
            }
            d2[i] = j;
        }else{
            if(d2[l+r-i-1]+i+1 > r){
                int j;
                for(j = 0; (c[r+j]==c[i-(r-i)+1-j]) && (c[r+j]!=0); j++){
                }
                j--;
                d2[i] = r+j-i;
                if(j > 0){
                    l = i-(r-i)+1-j;
                    r = r+j;
                }
                //                d2[i] = r-i;
            }else{
                d2[i] = d2[l+r-i-1];
                if(i + d2[i] > n){
                    d2[i] = n-i;
                }
            }
        }
        ans = max(ans, d2[i]*2);
    }
    printf("%d", ans);
}