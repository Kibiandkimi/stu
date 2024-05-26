//
// Created by kibi on 2021/7/9.
//
#include <bits/stdc++.h>
using namespace std;
int vis[205];
struct node{
    int s,step,f;
};
node a[205];
int main(){
    int n;
    cin >> n;
    int f,t;
    cin >> f >> t;
    for(int i = 1; i <= n; i++){
        cin >> a[i].s;
        a[i].f = i;
    }

    a[f].step = 0;
    queue<node> q;
    q.push(a[f]);
    while(!q.empty()){
        node tem, now;
        tem = now = q.front();
        if(now.f == t){
            cout << now.step;
            return 0;
        }
        tem.f+=a[tem.f].s;
        if(tem.f<=n&&!vis[tem.f]){
            tem.step++;
            tem.s=a[tem.f].s;
            q.push(tem);
            vis[tem.f] = 1;
        }
        tem = now;
        tem.f-=a[tem.f].s;
        if(tem.f>0&&!vis[tem.f]){
            tem.step++;
            tem.s=a[tem.f].s;
            q.push(tem);
            vis[tem.f] = 1;
        }
        q.pop();
    }
    cout << -1;
    return 0;
}