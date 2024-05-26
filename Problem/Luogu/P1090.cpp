//
// Created by kibi on 22-8-13.
//
//
// Created by kibi on 22-8-13.
//
#include <bits/stdc++.h>
using namespace std;
long long n, a[100005], ans;

//priority_queue<long long, vector<long long>, greater<> > q;

queue<long long> q1, q2;
long long s1, s2;

void read(int &x){
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

inline long long sea(){
    long long res;
    if(q1.empty()){
        res =  q2.front();
        q2.pop();
        s2--;
        return res;
    }
    if(q2.empty()){
        res =  q1.front();
        q1.pop();
        s1--;
        return res;
    }
    if(q1.front()>q2.front()){
        res = q2.front();
        q2.pop();
        s2--;
    }else{
        res = q1.front();
        q1.pop();
        s1--;
    }
    return res;
}

int main(){
    scanf("%lld", &n);
    s1 = n;
    for(int i = 1; i <= n; i++){
        int t;
//        scanf("%lld", &t);
        read(t);
        a[t]++;
//        q.push(a[i]);
    }
//    sort(a+1, a+1+n);
    for(int i = 0; i <= 100004; i++){
        while(a[i]--){
            q1.push(i);
        }
    }
    while(s1+s2>1){
        long long u, v;
        u = sea();
        v = sea();
        ans += u+v;
        q2.push(u+v);
        s2++;
    }
    printf("%lld", ans);
}