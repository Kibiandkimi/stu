//
// Created by kibi on 2021/9/12.
//
#include <bits/stdc++.h>
using namespace std;
int n,k;
struct ll{
    vector<int> s;
    void push_back(int a){
        s.push_back(a);
    }
    int size() const{
        return s.size();
    }
    void init(char *a){
        int p = 0;
        while(a[p]!=0){
            p++;
        }
        for(int i = p-1; i >= 0; i--){
            s.push_back(a[i]);
        }
    }
    ll qs(int l, int r){
        ll ret;
        int fro = s.size()-l, to = s.size()-r;
        for(int i = to; i <= fro; i++){
            ret.push_back(s[i]);
        }
        return ret;
    }
    ll operator+(const ll&b){
        ll ret;
        int sa = s.size(), sb = b.size();
        int ss = min(sa, sb);
        int p = -1, jw = 0, i;
        for(i = 0; i < ss; i++){
            ret.push_back(this->s[i]+b.s[i]+jw);
            p++;
            jw = 0;
            if(ret.s[i]>9){
                ret.s[i]-=10;
                jw = 1;
            }
        }
        if(sa > sb){
            for(; i < sa; i++){
                ret.push_back(this->s[i]+jw);
                jw = 0;
            }
        }else{
            for(; i < sb; i++){
                ret.push_back(b.s[i]+jw);
                jw = 0;
            }
        }
        if(jw){
            ret.push_back(1);
        }
        return ret;
    }
    ll operator*(const ll&b){
        ll ret;
        int sa = s.size(), sb = b.size();
        for(int i = 0; i < sa; i++){
            ll t;
            int jw = 0;
            for(int j = 0; j < i; j++){
                t.push_back(0);
            }
            for(int j = 0; j < sb; j++){
                t.push_back(jw+s[i]*b.s[j]);
                jw = t.s[j+i]/10;
                t.s[j+i]%=10;
            }
            ret = ret + t;
        }
        return ret;
    }
};
ll max(ll a, ll b){
    if(a.size()>b.size()){
        return a;
    }else if(b.size()>a.size()){
        return b;
    }
    int s = a.size();
    for(int i = s-1; i >= 0; i--){
        if(a.s[i]>b.s[i]){
            return a;
        }else if(b.s[i]>a.s[i]){
            return b;
        }
    }
    return a;
}
char a[50];
ll f[50][50],r,ans[50],lans;
int main(){
    cin >> n >> k;
    scanf("%s", a);
    for(int i = 0; i < n; i++)a[i]-='0';
    r.init(a);
    for(int i = 1; i < n; i++){
        f[i][1] = r.qs(1, i);
        for(int j = 2; j <= k; j++){
            for(int fr = j-1; fr < i; fr++){
                if(f[fr][j-1].size()){
                    f[i][j] = max(f[i][j], f[fr][j-1]*r.qs(fr+1, i));
                }
            }
        }
        if(f[i][k].size()){
            ans[i] = f[i][k] * r.qs(i+1, n);
        }
    }
    for(int i = 1; i <= n; i++){
        ll tmp = max(ans[i], lans);
        lans = tmp;
    }
    for(int i = lans.size()-1; i >= 0; i--){
        printf("%d", lans.s[i]);
    }
}

/*
 * t
 #include <bits/stdc++.h>
using namespace std;
struct ll{
   vector<int> a;
   int size() const {
       return this->a.size();
   }
   void pb(int t){
       a.push_back(t);
   }
   ll operator+(const ll &b){
       ll ret;
       ll r = *this;
       int rn = r.size(), bn = b.size(), jw = 0, p = 0;
       int mn = min(rn, bn);
       while(p<mn){
           ret.pb(r.a[p]+b.a[p]+jw);
           jw = ret.a[p]/10;
           ret.a[p]%=10;
           p++;
       }
       if(rn > bn){
           while(p<rn) {
               ret.pb(r.a[p] + jw);
               jw = ret.a[p] / 10;
               ret.a[p] %= 10;
               p++;
           }
       }else if(bn > rn){
           while(p<bn){
               ret.pb(b.a[p] + jw);
               jw = ret.a[p] / 10;
               ret.a[p] %= 10;
               p++;
           }
       }
       if(jw){
           ret.pb(jw);
       }
       return ret;
   }
   ll operator*(ll &b){
       ll ret, r = *this;
       int sa = r.size(), sb = b.size();
       for(int i = 0; i < sa; i++){
           ll t;
           int jw = 0;
           for(int j = 0; j < i; j++){
               t.pb(0);
           }
           for(int j = 0; j < sb; j++){
               t.pb(jw+a[i]*b.a[j]);
               jw = t.a[j+i]/10;
               t.a[j+i]%=10;
           }
           ret = ret + t;
       }
       return ret;
   }
};
int n,k;
char a[50];
ll r,dp[200][100],s[200][200];
int main(){
   cin >> n >> k;
//    cin >> a;
   for(int i = 1; i <= n; i++){
       int t;
       scanf("%1d", &t);
//        r.pb(t);
       a[i] = t;
   }

for(int i = n; i >= 1; i--){
   r.pb(a[i]);
}

for(int i = 1; i <= n; i++){
   for(int j = i; j <= n; j++){
       for(int p = n-j+1; p <= n-i+1; p++){
           s[i][j].pb(r.a[p]);
       }
   }
}

for(int i = 1; i <= n; i++){
   for(int j = 1; j <= i && j <= k+1; j++){
       if(j==1){

       }
   }
}
}
 */