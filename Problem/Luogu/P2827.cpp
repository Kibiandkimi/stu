//
// Created by kibi on 2022/10/13.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);

int main(){
    static const int minInt = INT_MIN;
    static int n, m, q, u, v, t, raw[100005], sum;
    read(n), read(m), read(q), read(u), read(v), read(t);
    for(int i = 1; i <= n; i++){
        read(raw[i]);
    }
    sort(raw+1, raw+1+n);
    static queue<int> qRaw, q1, q2;
    for(int i = n; i > 0; i--){
        qRaw.push(raw[i]);
    }
    while(m--){
        static int i = 1, tem1, tem2, tem3, ans, len1, len2;
        tem1 = qRaw.empty() ? minInt : qRaw.front(), tem2 = q1.empty() ? minInt : q1.front(), tem3 = q2.empty() ? minInt : q2.front();
        if(tem1 >= tem2 && tem1 >= tem3){
            qRaw.pop();
            ans = tem1;
        }else if(tem2 >= tem1 && tem2 >= tem3){
            q1.pop();
            ans = tem2;
        }else{
            q2.pop();
            ans = tem3;
        }
        ans += sum;
        len1 = (int)((long long)ans * u / v);
        len2 = ans - len1;
        sum += q;
        q1.push(len1 - sum), q2.push(len2 - sum);
        if(i % t == 0){
            printf("%d ", ans);
            i = 0;
        }
        i++;
        //        sum += q;
    }
    printf("\n");
    while(!qRaw.empty() || !q1.empty() || !q2.empty()){
        static int i = 1, tem1, tem2, tem3, ans;
        tem1 = qRaw.empty() ? minInt : qRaw.front(), tem2 = q1.empty() ? minInt : q1.front(), tem3 = q2.empty() ? minInt : q2.front();
        if(tem1 >= tem2 && tem1 >= tem3){
            qRaw.pop();
            ans = tem1;
        }else if(tem2 >= tem1 && tem2 >= tem3){
            q1.pop();
            ans = tem2;
        }else{
            q2.pop();
            ans = tem3;
        }
        ans += sum;
        if(i % t == 0){
            printf("%d ", ans);
            i = 0;
        }
        i++;
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if (c == '-'){
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