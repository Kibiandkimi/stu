//
// Created by kibi on 2021/7/12.
//
#include <bits/stdc++.h>
using namespace std;
int main(){
    string a,b;
    long long s = 0;
    cin >> a >> b;
    for(int i = 0; i < a.size(); i++){
        for(int j = 1; j < a.size(); j++){
            if(a[i]==b[j]&&a[i+1]==b[j-1]){
                s++;
            }
        }
    }
    cout << pow(2,s);
}
