//
// Created by kibi on 2021/10/5.
//
#include <bits/stdc++.h>
using namespace std;
char c[300];
bool flag = false;
int k,len;
int q[300];
int fr, ta;
int main(){
    scanf("%s%d", c+1, &k);
    len = strlen(c+1);
    if(k==len-1){
        for(int i = 1; i <= len; i++){
            if(c[i] == '0'){
                printf("0");
                return 0;
            }
        }
    }
    for(int i = 1; i <= len; i++){
        c[i] = c[i] - '0';
    }
    int p = 1;
    while(k>0&&p<=len){
        //        if(len - p + 1==k){
        //            flag = true;
        //            break;
        //        }
        while(fr<ta&&c[p]<q[ta]&&k--)ta--;
        q[++ta] = c[p];
        p++;
    }
    while(!q[fr+1])fr++;
    if(fr == ta){
        cout << 0;
    }else{
        //        if(q[fr+1]==0) {
        //            int mn = 1e9;
        //            for (int i = 1; c[i] != 0; i++) {
        //                mn = min(mn, int(c[i]));
        //            }
        //            cout << mn;
        //        }
        for(int i = fr+1; i <= ta-max(k,0); i++){
            cout << q[i];
        }

        //        if(!flag) {
        for (int i = p; i <= len; i++) {
            cout << (int) c[i];
        }
        //        }
    }
}