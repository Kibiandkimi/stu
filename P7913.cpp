//
// Created by kibi on 2021/12/12.
//
#include <bits/stdc++.h>
using namespace std;
int n,m1,m2;
pair<int, int> a[100005], b[100005];
priority_queue<int> h_id;
priority_queue<pair<int, int> > h_ed;
int sa[100005], sb[100005];
bool cmp(pair<int, int> a, pair<int, int> b){

    return a.first<b.first;
}
int main(){
    scanf("%d %d %d", &n, &m1, &m2);
    for(int i = 1; i <= m1; i++){
        scanf("%d %d", &a[i].first, &a[i].second);
    }
    sort(a+1, a+1+m1, cmp);
    for(int i = 1; i <= n; i++)h_id.push(-i);
    for(int i = 1; i <= m1; i++){
        if(!h_ed.empty()){
            while(-h_ed.top().first < a[i].first){
                h_id.push(-h_ed.top().second);
                h_ed.pop();
                if(h_ed.empty()){
                    break;
                }
            }
        }
        if(!h_id.empty()){
            int x = -h_id.top();
            h_id.pop();
            sa[x]++;
            h_ed.push(make_pair(-a[i].second, x));
        }
    }
    for(int i = 1; i <= n; i++)sa[i] += sa[i-1];
    while(!h_ed.empty()){
        h_ed.pop();
    }
    while(!h_id.empty()){
        h_id.pop();
    }
    for(int i = 1; i <= m2; i++){
        scanf("%d %d", &b[i].first, &b[i].second);
    }
    sort(b+1, b+1+m2, cmp);
    for(int i = 1; i <= n; i++)h_id.push(-i);
    for(int i = 1; i <= m2; i++){
        if(!h_ed.empty()){
            while(-h_ed.top().first < b[i].first){
                h_id.push(-h_ed.top().second);
                h_ed.pop();
                if(h_ed.empty()){
                    break;
                }
            }
        }
        if(!h_id.empty()){
            int x = -h_id.top();
            h_id.pop();
            sb[x]++;
            h_ed.push(make_pair(-b[i].second, x));
        }
    }
    for(int i = 1; i <= n; i++)sb[i] += sb[i-1];
    int mx = 0;
    for(int i = 0; i <= n; i++){
        mx = max(mx, sa[i]+sb[n-i]);
    }
    printf("%d", mx);
    return 0;
}
