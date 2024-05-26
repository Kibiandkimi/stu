//
// Created by kibi on 2021/7/31.
//
#include <bits/stdc++.h>
using namespace std;
struct node2{
    int ax,ay,bx,by;
};
node2 a[50005];
//int ax[50005],ay[50005],bx[50005],by[50005];
int n;
struct node{
    long long py;
    int q;
};
int cmp(node2 a, node2 b){
    double t1 = (a.ay-a.by)/(double)(a.ax-a.bx), t2 =  (b.ay-b.by)/(double)(b.ax-b.bx);
    if(t1 < 0){
        if(t2 < 0){
            return t1 > t2;
        }else{
            return t1 < t2;
        }
    }else{
        if(t2 < 0){
            return t1 < t2;
        }else{
            return t1 > t2;
        }
    }

}
node Intersect(int i, int j) {
    // long long px = (long long)(ay[j] * bx[j] - ax[j] * by[j]) * (ax[i] - bx[i]) - (long long)(ay[i] * bx[i] - ax[i] * by[i]) * (ax[j] - bx[j]);
    long long py = (long long)(a[i].ax * a[i].by - a[i].ay * a[i].bx) * (a[j].ay - a[j].by) - (long long)(a[j].ax * a[j].by - a[j].ay * a[j].bx) * (a[i].ay - a[i].by);
    int q = (a[i].ax - a[i].bx) * (a[j].ay - a[j].by) - (a[j].ax - a[j].bx) * (a[i].ay - a[i].by);
    if (q < 0) py *= -1, q *= -1;
    //    printf("(%lld / %d, %lld / %d)\n", px, q, py, q);
    //    printf("(%.8f, %.8f)\n", px / (double)q, py / (double)q);
    return (node){py,q};
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d %d %d %d", &a[i].ax, &a[i].ay, &a[i].bx, &a[i].by);
    }
    sort(a+1,a+1+n,cmp);
    double pxq = -1e9;
    for(int i = 1; i < n; i++){
        node t = Intersect(i,i+1);
        pxq = max(pxq, t.py / (double)t.q);
    }
    printf("%.8lf", pxq);
}

