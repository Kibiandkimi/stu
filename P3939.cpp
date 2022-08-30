//
// Created by kibi on 22-8-30.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> a[300005];
int raw[300005];

bool getType(int c);
void read(int &x);
int find(int x, int c);

int main(){
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        int c;
        read(c);
        a[c].push_back(i);
        raw[i] = c;
    }
    while(m--){
        int opt;
        read(opt);
        if(opt == 1){
            int l, r, c;
            read(l), read(r), read(c);
            int rl = find(l, c), rr = find(r, c);
            if(rl == a[c].size() || !a[c].size()){
                printf("0\n");
            }else {
                while (a[c][rl] < l) {
                    rl++;
                }
                if (rr == a[c].size()) {
                    rr--;
                }
                while (a[c][rr] > r) {
                    rr--;
                }
                printf("%d\n", rr - rl + 1);
            }
        }else if(opt == 2){
            int x;
            read(x);
            if(raw[x] == raw[x+1]){
                continue;
            }
            int u = find(x, raw[x]), v = find(x+1, raw[x+1]);
            a[raw[x]][u] = x+1;
            a[raw[x+1]][v] = x;
            swap(raw[x], raw[x+1]);
        }
    }
}

bool getType(int c){
    return c<'0'||'9'<c;
}

void read(int &x){
    int s = 0, w= 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c= getchar();
    }
    while(!getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

int find(int x, int c){
    int l = 0, r = a[c].size();
    while(l < r){
        int mid = (l+r)/2;
        if(x>a[c][mid]){
            l = mid+1;
        }else if(x < a[c][mid]){
            r = mid;
        }else{
            return mid;
        }
    }
    return l;
}