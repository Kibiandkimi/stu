//
// Created by kibi on 2021/6/27.
//
#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin >> s;
    int m;
    cin >> m;
    for(int i = 1; i <= m; i++){
        string sub;
        cin >> sub;
        int idx = 0;
        int cnt = 0;
        while ((idx = s.find(sub, idx)) != s.npos){
            idx++;
            cnt++;
        }
        cout << cnt << endl;
    }
}


