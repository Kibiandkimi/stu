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

/*
#include <bits/stdc++.h>
using namespace std;

const int N = 10000000, Max = 100000;

void read(int&);

int main(){
    static int bucket[Max+5];
    static queue<long long> q1, q2;

    int n;
    read(n);

    for(int i = 1; i <= n; i++){
        int t;
        read(t);
        bucket[t]++;
    }
    for(int i = 1; i <= Max+1; i++){
        while(bucket[i]--) {
            q1.push(i);
        }
    }
    long long ans = 0;
    for(int t = 1; t < n; t++){
        long long v[2];
        for(long long & i : v){
            if(q1.empty()){
                i = q2.front();
                q2.pop();
            }else if(q2.empty()){
                i = q1.front();
                q1.pop();
            }else{
                i = min(q1.front(), q2.front());
                i == q1.front() ? q1.pop() : q2.pop();
            }
        }
        ans += v[0] + v[1];
        q2.push(v[0] + v[1]);
    }
    printf("%lld\n", ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}
 * */