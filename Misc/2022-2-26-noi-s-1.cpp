//
// Created by kibi on 2022/3/26.
//
// no use
#include <bits/stdc++.h>
using namespace std;
int n,q;
int to,ba;
stack<int> s;
int a[500005], b[500005];
bool f[500005];
vector<int> v[500005];
int w[500005];
int main(){
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
    }
    f[1] = true;
    //    to = ba = 1;
    w[1] = 1;
    s.push(1);
    for(int i = 2; i <= n; i++){
        while(!s.empty()){
            if(a[s.top()]==a[i]||b[s.top()]>=b[i]){
                s.pop();
            }else{
                v[s.top()].push_back(i);
                w[i] = s.top();
                s.push(i);
            }
        }
        if(s.size()==0){
            f[i] = true;
            w[i] = i;
            s.push(i);
        }
    }


}