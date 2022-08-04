//
// Created by kibi on 2022/8/4.
//
#include <bits/stdc++.h>
using namespace std;
int n, a[100005];

struct node{
    int v;
    bool operator < (node b) const{
        return v > b.v;
    }
};

priority_queue<int> q1;
priority_queue<node> q2;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    printf("%d\n", a[1]);
    if(n < 2){
        return 0;
    }
    q1.push(min(a[1], a[2]));
    q2.push({max(a[1], a[2])});
    if(a[3] < q1.top()){
        q1.push(a[3]);
    }else{
        q2.push({a[3]});
    }
    if(q1.size()>q2.size()){
        printf("%d\n", q1.top());
    }else{
        printf("%d\n", q2.top().v);
    }
    for(int i = 4; i < n; i+=2){
        int x = i, y = i+1;
        if(a[x] < q1.top()){
            q1.push(a[x]);
        }else{
            q2.push({a[x]});
        }
        if(a[y] < q1.top()){
            q1.push(a[y]);
        }else{
            q2.push({a[y]});
        }
        while(fabs(q1.size() - q2.size()) > 1){
            if(q1.size() > q2.size()){
                q2.push({q1.top()});
                q1.pop();
            }else{
                q1.push(q2.top().v);
                q2.pop();
            }
        }
        if(q1.size()>q2.size()){
            printf("%d\n", q1.top());
        }else{
            printf("%d\n", q2.top().v);
        }
    }

}