//
// Created by kibi on 2021/7/26.
//
#include <bits/stdc++.h>
using namespace std;
int a[500005];
int t1[250005]={},t2[250005]={},s[500005]={};
long long f(int x, int y){
    if(x==y){
        return 0;
    }
    int mid = (x+y)/2;
    long long ss = 0;
    ss+=f(x,mid);
    ss+=f(mid+1,y);
    int ii=1;
    for(int i = x; i <= mid; i++){
        t1[ii] = a[i];ii++;
    }
    ii=1;
    for(int i = mid + 1; i <= y; i++){
        t2[ii] = a[i];ii++;
    }
    ii=1;
    int i1=1, i2=1;
    int nl=1, sl=0;
    while(i1<=mid-x+1&&i2<=y-mid){
        if(t1[i1]>t2[i2]){
            s[ii]=t1[i1];
            i1++;
            ii++;
            ss+=y-mid-i2+1;
            sl++;

        }else{
            s[ii]=t2[i2];
            i2++;
            ii++;
            //            ss+=mid-x+1-i1;
            sl++;
        }
        if(s[ii]==s[ii-1]){
            ss-=nl;
            nl++;
        }else{
            nl=1;
        }
    }
    while(i1<=mid-x+1){
        s[ii]=t1[i1];
        i1++;
        ii++;
        //        ss+=sl;
        sl++;
        if(s[ii]==s[ii-1]){
            ss-=nl;
            nl++;
        }else{
            nl=1;
        }
    }
    while(i2<=y-mid){
        s[ii]=t2[i2];
        i2++;
        ii++;
        //        ss+=sl;
        if(s[ii]==s[ii-1]){
            ss-=nl;
            nl++;
        }else{
            nl=1;
        }
    }
    for(int i = x; i <= y; i++){
        a[i] = s[i-x+1];
    }
    return ss;
}
int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    long long s;
    s = f(1,n);
    //    f(1,n);
    cout << s;
}