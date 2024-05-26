//
// Created by kibi on 2021/6/27.
//
#include <bits/stdc++.h>
using namespace std;
int a[105];
struct node{
    int s;
    struct node *next;
};
node c[105];
int main(){
    int i = 0;
    int t = 0;
    while(true){
        cin >> t;
        if(a[t]!=0){
            c[i-1].next = &c[a[t]];
            break;
        }
        a[t] = i;
        c[i].s = t;
        if(i != 0){
            c[i-1].next = &c[i];
        }
        i++;
    }
    node *a1,*a2;
    a1 = &c[1];
    a2 = &c[2];
    while(a1->s!=a2->s){
        a1 = a1->next;
        a2 = a2->next;
        a2 = a2->next;
    }
    cout << a1->s;
}