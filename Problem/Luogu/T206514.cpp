//
// Created by kibi on 2021/10/31.
//
#include <bits/stdc++.h>
using namespace std;
string s;
int s0, s1, mx = -1e9;
int a[100005];
int main(){
    cin >> s;
    int sa = s.size();
    for(int i = 0; i <= sa; i++){
        if(s[i]=='0'){
            s0++;
        }else{
            s1++;
        }
        if(s0-s1<0){
            a[i] = -1;
            s0 = s1 = 0;
        }else{
            a[i] = s0-s1;
        }
        mx = max(a[i], mx);
    }
    cout << mx;
}