//
// Created by kibi on 2021/8/10.
//
#include <bits/stdc++.h>
using namespace std;
int n,m;
long long a[500005],s[500005],mx=-1e9;
struct node{
    int i;
    long long s;
};
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        s[i] = s[i-1] + a[i];
    }
    deque<node> q;
    //    q.push_back(node({1 ,s[1]}));
    q.push_back(node({0 ,0}));
    for(int i = 1; i <= n; i++){
        if(!q.empty()&&q.front().i<i-m){
            q.pop_front();
        }
        mx = max(mx, s[i]-q.front().s);
        while(!q.empty()&&q.back().s>s[i]){
            q.pop_back();
        }
        q.push_back(node({i ,s[i]}));
    }
    cout << mx;
}