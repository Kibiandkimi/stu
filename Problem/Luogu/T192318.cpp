//
// Created by kibi on 2021/8/8.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,sa;
vector<string> a;
//queue<int> q;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        string t;
        cin >> t;
        a.push_back(t);
    }
    sa = a.size();
    for(int i = 1; i <= m; i++){
        int s = 0;
        string t;
        cin >> t;
        int fr,ba,size = t.size();
        for(int j = 0; j < size; j++){
            if(t[j] == '*'){
                fr = j - 1;
                ba = size - j - 1;
                j = size;
            }
        }
        for(int j = 0; j < sa; j++){
            int tba = ba;
            bool f = true;
            for(int k = 0; k <= fr; k++){
                if(a[j][k] != t[k]){
                    f = false;
                    k = fr+1;
                }
            }
            if(f){
                for(int k = a[j].size()-1, kk = t.size()-1; tba>0; k--,tba--,kk--){
                    if(a[j][k] != t[kk]){
                        f = false;
                        tba = 0;
                    }
                }
                s += f;
            }
        }
        printf("%d\n", s);
    }
}