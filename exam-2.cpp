//
// Created by kibi on 2021/6/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,m;
struct node{
    double v,c;
    string n;

};
node a[24];
int cmp(node a1, node a2){
    return a1.v/a1.c > a2.v/a2.c;
}
int cmp2(node a1, node a2){
    return a1.v > a2.v;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a[i].n >> a[i].v >> a[i].c;

    }
    sort(a,a+n,cmp);
    cout << a[0].n <<" "<< int(a[0].v) <<" "<< int(a[0].c)<<endl;
    a[0].v = -1;
    m-=a[0].c;
    sort(a,a+n,cmp2);
    for(int i = 0; i < n; i++){
        if(int(a[i].c) <= m){
            cout << a[i].n <<" "<< int(a[i].v) <<" "<< int(a[i].c)<<endl;
            break;
        }
    }
}