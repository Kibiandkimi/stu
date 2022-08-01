//
// Created by kibi on 2022/6/12.
//
//O2
#include <bits/stdc++.h>
using namespace std;
int n,q,sq;
int a[1000005], st[1005], nd[1005], bel[1000005], mark[1005];
vector<int> v[1005];

bool cmp(int a, int b){
    return a<b;
}

void update(int b){
    for(int i = st[b]; i <= nd[b]; i++){
        v[b][i-st[b]] = a[i];
    }
    sort(v[b].begin(), v[b].end(), cmp);
}

int main(){
    scanf("%d %d", &n, &q);
    sq = sqrt(n);
    for(int i = 1; i <= sq; i++){
        st[i] = n/sq*(i-1)+1;
        nd[i] = n/sq*i;
    }
    nd[sq] = n;

    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    for(int i = 1; i <= sq; i++){
        for(int j = st[i]; j <= nd[i]; j++){
            bel[j] = i;
            v[i].push_back(a[j]);
        }
        sort(v[i].begin(),v[i].end(),cmp);
    }


    while(q--){
        char t;
        scanf("%s", &t);
        int l,r,k;
        scanf("%d %d %d", &l, &r, &k);
        if(t == 'M'){
            if(bel[l] == bel[r]){
                for(int i = l; i <= r; i++){
                    a[i] += k;
                }
                update(bel[l]);
            }else{
                for(int i = l; i <= nd[bel[l]]; i++){
                    a[i] += k;
                }
                update(bel[l]);
                for(int i = st[bel[r]]; i <= r; i++){
                    a[i] += k;
                }
                update(bel[r]);
                for(int i = bel[l] + 1; i < bel[r]; i++){
                    mark[i] += k;
                }
            }
        }else{
            int s = 0;
            if(bel[l] == bel[r]){
                for(int i = l; i <= r; i++){
                    s += (a[i]+mark[bel[i]] >= k);
                }
            }else{
                for(int i = l; i <= nd[bel[l]]; i++){
                    s += (a[i]+mark[bel[i]] >= k);
                }
                for(int i = st[bel[r]]; i <= r; i++){
                    s += (a[i]+mark[bel[i]] >= k);
                }
                for(int i = bel[l] + 1; i < bel[r]; i++){
                    s += v[i].end() - lower_bound(v[i].begin(), v[i].end(), k-mark[i]);
                }
            }
            printf("%d\n", s);
        }
    }

    return 0;
}