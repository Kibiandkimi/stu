//
// Created by kibi on 24-10-6.
//
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
vector<pii>r;
int T;
int n,m;
int main() {
    // freopen("temp.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--) {
        cin>>n>>m;
        r.clear();
        r.push_back(mp(0,0));
        for (int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        r.push_back(mp(a,b));
        }
        sort(r.begin(),r.end());
        bool flag=1;
        for (int i=1;i<=m;i++){
            if (r[i].first-r[i-1].first-1>=r[i].second||r[i].second-r[i-1].second==r[i].first-r[i-1].first) {
                continue;
            }else{
                flag=0;
            }
        }
        if (flag){
            cout<<"Yes\n";
        }else{
            cout<<"No\n";
        }
    }

}