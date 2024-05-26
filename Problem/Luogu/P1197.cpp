//
// Created by kibi on 2021/10/8.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,k,tot;
vector<int> a[400005];
int bcj[400005];
int qs[200005];
int as[200005];
bool xj[400005];
// bool pd[400005];
int find(int x){
    if(bcj[x]!=x){
        bcj[x] = find(bcj[x]);
    }
    return bcj[x];
}
int hm(){
    bool pd[400005];
    for(int i = 0; i < n; i++){
        pd[i] = false;
    }
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if((!xj[i])&&(!pd[find(bcj[i])])){
            cnt++;
            pd[find(bcj[i])] = true;
        }
    }
    //    return cnt?cnt:1;
    return cnt;
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    scanf("%d", &k);
    for(int i = 1; i <= k; i++){
        scanf("%d", &qs[i]);
        xj[qs[i]] = true;
    }
    for(int i = 0; i < n; i++){
        bcj[i] = i;
    }
    for(int i = 0; i < n; i++){
        if(!xj[i]){
            int sa = a[i].size();
            for(int j = 0; j < sa; j++){
                if(!xj[a[i][j]]){
                    if(find(a[i][j])!=find(i)) {
                        bcj[find(a[i][j])] = find(i);
                    }
                }
            }
        }
    }
    as[0] = tot = hm();
    for(int i = k; i >= 1; i--){
        int sa = a[qs[i]].size();
        tot++;
        //        int cnt = 0;
        // int t = -1;
        xj[qs[i]] = false;
        //        vector<int> t;
        for(int j = 0; j < sa; j++){
            if(!xj[a[qs[i]][j]]) {
                //                t.push_back(find(a[qs[i]][j]));
                if(find(a[qs[i]][j])!=find(qs[i])){
                    tot--;
                    if(find(a[qs[i]][j])!=find(qs[i])){
                        bcj[find(a[qs[i]][j])] = find(qs[i]);
                    }
                }
            }
            //        sa = t.size();
            //        bool pd[400005] = {false};
            //        for(int j = 0; j < sa; j++){
            //            if(!pd[t[j]]){
            //                pd[t[j]] = true;
            //                cnt++;
            //            }
        }
        // as[k-i+1] = hm();
        as[k-i+1] = tot;
        // as[k-i+1]
    }
    for(int i = k; i >= 0; i--){
        printf("%d\n", as[i]);
    }
}