//
// Created by kibi on 2022/7/30.
//
#include <bits/stdc++.h>
using namespace std;
int S;
int n, q, w, b1, b2, ic, dc;
int x1[100005], x2[100005];
//int qz[100005];
bool f1[100005];
bool f2[100005];
bool f3[100005];

int pd(int x){
    return (fabs(x-w)<=b1)?ic:((fabs(x-w)>b2)?dc:0);
}

int f(int l, int r, int *x, const bool *tf){
    int now = dc;
    //    bool flag = false;
    for(int i = l; i <= r; i++){
        if(tf[i]){
            break;
        }
        if(now > 0){
            now += pd(x[i]);
        }else{
            now = pd(x[i]);
        }
        //        ans = max(now, ans);
    }
    return now;
}

int main(){
    scanf("%d %d %d %d %d %d %d %d", &S, &n, &q, &w, &b1, &b2, &ic, &dc);
    for(int i = 1; i <= n; i++){
        scanf("%d", &x1[i]);
        x2[n-i+1] = x1[i];

    }
    //    for(int i = 1; i <= n; i++){
    //        qz[i] = qz[i-1]+x1[i];
    //    }
    while(q--){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int a, b;
            scanf("%d %d", &a, &b);
            int aa[15], bb[15];
            for(int i = 1; i <= a; i++){
                scanf("%d", &aa[i]);
                f1[aa[i]] = true;
            }
            for(int i = 1; i <= b; i++){
                scanf("%d", &bb[i]);
                f2[bb[i]] = true;
                f3[n-bb[i]+1] = true;
            }
            int l = 0;
            int ans = -1e9;
            for(int i = 1; i <= n; i++){
                if(f1[i]){
                    int t1 = f(l+1, i-1, x1, f2), t2 = f(1, n-i, x2, f3);
                    ans = max(ans, pd(x1[i]) + (t1>0?t1:0) + (t2>0?t2:0));
                }
                if(f2[i]){
                    l = i;
                }
            }
            printf("%d\n", ans);
            for(int i = 1; i <= a; i++){
                //                scanf("%d", &aa[i]);
                f1[aa[i]] = false;
            }
            for(int i = 1; i <= b; i++){
                //                scanf("%d", &bb[i]);
                f2[bb[i]] = false;
                f3[n-bb[i]+1] = false;
            }

        }else if(op == 2){
            scanf("%d", &w);
        }
    }
}