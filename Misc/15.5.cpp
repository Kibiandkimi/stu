//
// Created by kibi on 2021/6/20.
//
#include <bits/stdc++.h>
using namespace std;
struct node{
    double x,y,r;

};
struct node2{
    int x,y;
};
int m;
node2 b[1000005];
node a[1005];
int cmp(node2 a1, node2 a2){
    if(a1.x!=a2.x)return a1.x<a2.x;
    return a1.y<a2.y;
}
int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        double x,y,r;
        cin >> x >> y >> r;
        a[i].r = r;
        a[i].x = x;
        a[i].y = y;
    }
    for(int i = 1; i <= n; i++){
        for(int j = i+1; j <= n; j++){
            //cout << "   " << sqrt(pow(max(a[i].x,a[j].x)-min(a[i].x,a[j].x),2.0)+pow(max(a[i].y,a[j].y)-min(a[i].y,a[j].y),2.0)) << "   " << (a[i].r+a[j].r) << endl;
            if(sqrt(pow(max(a[i].x,a[j].x)-min(a[i].x,a[j].x),2.0)+pow(max(a[i].y,a[j].y)-min(a[i].y,a[j].y),2.0))>(a[i].r+a[j].r)){

            }else{
                m++;
                b[m-1].x = i;
                b[m-1].y = j;
            }
        }
    }
    sort(b,b+m,cmp);
    cout << m<<endl;
    for(int i = 0; i < m; i++){
        printf("%d %d\n", b[i].x,b[i].y);
    }
}

