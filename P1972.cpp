//
// Created by kibi on 22-8-12.
//
#include <bits/stdc++.h>
using namespace std;
int n, a[1000005], m;
int lo[1000005];
int res[1000005];
int tr[4000005];
vector<pair<pair<int, int>, int> > q;

bool cmp(pair<pair<int, int>, int> ta,  pair<pair<int, int>, int> b){
    return ta.first.second < b.first.second;
}

void insert(int x, int v){
    for(int i = x; i <= n; i+=(i&-i)){
        tr[i] += v;
    }
}

int query(int x){
    int ans = 0;
    if(x == 0){
        return 0;
    }
    for(int i = x; i > 0; i-=(i&-i)){
        ans += tr[i];
    }
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        int l, r;
        scanf("%d %d", &l, &r);
        q.push_back({{l,r}, i});
    }
    sort(q.begin(), q.end(), cmp);
    int sq = q.size(), last = 0;
    for(int i = 0; i < sq; i++){
        if(last != q[i].first.second){
            for(int j = last+1; j <= q[i].first.second; j++){
                if(lo[a[j]]){
                    insert(lo[a[j]], -1);
                }
                insert(j, 1);
                lo[a[j]] = j;
            }
        }
        last = q[i].first.second;
//        printf("%d\n", query(q[i].second) - query(q[i].first-1));
        res[q[i].second] = query(q[i].first.second) - query(q[i].first.first-1);
    }
    for(int i = 1; i <= m; i++){
        printf("%d\n", res[i]);
    }
}