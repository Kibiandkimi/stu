//
// Created by kibi on 23-7-20.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 250000;

void read(int&);

int main(){
    int n, h[N+5];
    read(n);

    stack<int> st;
    int ans = n;
    for(int i = 1; i <= n; i++){
        read(h[i]), read(h[i]);
        while(!st.empty() && h[i] <= st.top()){
            if(st.top() == h[i]){
                ans--;
            }
            st.pop();
        }
        st.push(h[i]);
    }

    printf("%d\n", ans);

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