//
// Created by kibi on 22-8-14.
//
#include <bits/stdc++.h> // scanf
using namespace std;
const int MAXN = 10000005; // Set a right value according to your solution.
int n, a[MAXN + 1];
int s[10000005][2], nd = -1;

namespace Generator {

    unsigned long long k1, k2;
    int thres;

    inline unsigned long long xorShift128Plus() {
        unsigned long long k3 = k1, k4 = k2;
        k1 = k4, k3 ^= (k3 << 23), k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
        return k2 + k4;
    }

    inline void generate() {
        for (int i = 1; i <= n; ++i) {
            a[i] = xorShift128Plus() % thres;
        }
    }

} // namespace Generator.

//int b[10000005];

int main() {
    scanf("%d", &n);
    scanf("%llu %llu %d", &Generator::k1, &Generator::k2, &Generator::thres);
    Generator::generate();
    // Now array a[1..n] represents the sequence A in the statement.
//    for(int i = 1; i <= n; i++) {
//        scanf("%d", &a[i]);
//    }




//    bool st = false;
//    for(int i = 1; i < n; i++){
//        if(!st){
//            if(a[i]>a[i+1]){
//                st = true;
//                swap(a[i], a[i+1]);
//                i++;
//            }
//        }else{
//            if(a[i] < a[i+1]){
//                break;
//            }
//        }
//    }

//    int c[10000005], ls[10000005];
//    for(int i = 1; i <= n; i++){
//        c[i] = a[i];
//    }
//    int m = unique(c+1, c+1+n)-c-1;
//    for(int i = 1; i <= n; i++){
//        ls[i]
//    }

//    stack<int> q1, q2;
//    for(int i = 1; i <= n; i++){
//        while(!q1.empty()&&q1.top()>=a[i]){
//            q1.pop();
//            q2.pop();
//        }
//        q1.push(a[i]);
//        q2.push(i);
//    }
    for(int i = 1; i <= n; i++){
        while(nd>=0 && s[nd][0]>=a[i]){
            nd--;
        }
        s[++nd][0] = a[i];
        s[nd][1] = i;
    }

    int now = 1;
//    for(int i = 0; i <= n;){
//        while(!b[i]&&i<=n){
//            i++;
//        }
//        if(i > n){
//            break;
//        }
//        while(a[now] <= i && now <= n){
//            now++;
//        }
//        if(now > n){
//            break;
//        }
//        if(b[i] <= now){
//            i++;
//        }else{
//            swap(a[now], a[b[i]]);
//            now = b[i]+1;
//            i++;
//        }
//    }
//    stack<pair<int, int> > b;
//    stack<int> b1;
//    stack<int> b2;
//    while(!q1.empty()){
//        b1.push(q1.top());
//        b2.push(q2.top());
//        q1.pop();
//        q2.pop();
//    }
    int tn = nd;
    nd = 0;
    while(nd<=tn&&now<=n){
        if(now < s[nd][1]){
            if(a[now] > s[nd][0]) {
                swap(a[now], a[s[nd][1]]);
                now = s[nd][1] + 1;
//                b1.pop();
//                b2.pop();
                nd++;
            }else{
                now++;
            }
        }else{
//            b1.pop();
//            b2.pop();
            nd++;
        }
    }

    unsigned long long ans = 0;
    for(int i = 1; i <= n; i++){
//        printf("%d", a[i]);
        ans += i * (unsigned long long)a[i];
    }
    printf("%llu", ans);
    return 0;
}