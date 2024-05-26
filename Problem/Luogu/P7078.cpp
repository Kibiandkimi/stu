//
// Created by kibi on 2022/9/3.
//
#include <bits/stdc++.h>
using namespace std;
int T, n, a[3000005];
struct node{
    node(int tp, int tv){
        p = tp, v = tv;
    }
    int p, v;
    bool operator > (node b) const{
        if(b.v == v){
            return p > b.p;
        }
        return v > b.v;
    }
};

bool getType(int c);
void read(int &x);
//void sub1();
//bool cmp(node a, node b);

int main(){
    read(T);
    read(n);
    for(int t = 1; t <= T; t++){
        if(t == 1){
            for(int i = 1; i <= n; i++){
                read(a[i]);
            }
        }else{
            int k;
            read(k);
            for(int i = 1; i <= k; i++){
                int p, v;
                read(p), read(v);
                a[p] = v;
            }
        }
        deque<node> q1, q2;
        for(int i = 1; i <= n; i++){
            q1.emplace_back(i, a[i]);
        }
        int ans;
        while(true) {
            if(q1.size() + q2.size() == 2){
                ans = 1;
                break;
            }
            int x, y, id;
            y = q1.front().v;
            q1.pop_front();
            if(q2.empty() || !q1.empty()&&q1.back()>q2.back()){
                x = q1.back().v, id = q1.back().p;
                q1.pop_back();
            }else{
                x = q2.back().v, id = q2.back().p;
                q2.pop_back();
            }
            node now = {id, x-y};
            if(q1.empty() || q1.front() > now){
                ans = q1.size()+q2.size()+2;
                int cnt = 0;
                while(true){
                    cnt++;
                    if(q1.size()+q2.size()+1==2){
                        ans -= cnt%2==0;
                        break;
                    }
                    int x, id;
                    if(q2.empty() || !q1.empty()&&q1.back()>q2.back()){
                        x = q1.back().v, id = q1.back().p;
                        q1.pop_back();
                    }else{
                        x = q2.back().v, id = q2.back().p;
                        q2.pop_back();
                    }
                    now = {id, x-now.v};
                    if(!((q1.empty()||q1.front()>now) && (q2.empty()||q2.front()>now))){
                        ans -= cnt%2==0;
                        break;
                    }
                }
                break;
            }else{
                q2.push_front(now);
            }
        }
        printf("%d\n", ans);
    }
}

bool getType(int c){
    return c<'0'||'9'<c;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

//void sub1(){
//    int x = a[1], y = a[2], z = a[3];
//    if(x+y<=z){
//        printf("1\n");
//    }else{
//        printf("3\n");
//    }
//    while(--T){
//        int k;
//        read(k);
//        for(int i = 1; i <= k; i++){
//            int p, v;
//            read(p), read(v);
//            a[p] = v;
//        }
//        x = a[1], y = a[2], z = a[3];
//        if(x+y<=z){
//            printf("1\n");
//        }else{
//            printf("3\n");
//        }
//    }
//}