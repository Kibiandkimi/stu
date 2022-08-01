//
// Created by kibi on 2021/10/10.
//
#include <bits/stdc++.h>
using namespace std;
int n,m;
double pd = 1e-6;
int vis[805];
vector<int> d[805];
// int x[1005], y[1005];
struct node{
    int x, y;
}a[805];
double ans;
bool cmp(node a, node b){
    return a.x==b.x?a.y<b.y:a.x<b.x;
}
bool f(int x){
    if(x==801){
        return true;
    }
    int sa = d[x].size();
    if(!sa){
        return false;
    }
    for(int i = 0; i < sa; i++){
        if(!vis[d[x][i]]){
            vis[d[x][i]] = 1;
            if(f(d[x][i])){
                return true;
            }
        }
    }
    return false;
}
bool check(int x){
    // for(int i = 1; i <= m; i++){
    //     bcj[i] = i;
    // }

    for(int i = 0; i <= 801; i++){
        d[i].clear();
        vis[i] = 0;
    }
    for(int i = 1; i <= m; i++){
        if(a[i].x<=(double(x))/1000+pd){
            d[0].push_back(i);
            d[i].push_back(0);
        }
        if(n-a[i].x<=(double(x))/1000+pd){
            d[801].push_back(i);
            d[i].push_back(801);
        }
        for(int j = i; j <= m; j++){
            if(sqrt(double((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y)))<=(double(x))/500+pd){
                //                if(x==3905){
                ////                    printf("%lf %lf\n\n\n", sqrt(double((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y))), (double(x))/50+pd);
                //                    cout << sqrt(double((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y))) << " " << (double(x))/50+pd << endl;
                //                }
                d[i].push_back(j);
                d[j].push_back(i);
            }
            //            if(x==3905){
            //                //                    printf("%lf %lf\n\n\n", sqrt(double((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y))), (double(x))/50+pd);
            //                cout << sqrt(double((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y))) << " " << (double(x))/50+pd << endl;
            //            }
        }
    }
    return f(0);
}
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        scanf("%d %d", &a[i].x, &a[i].y);
        // scanf("")
    }
    sort(a+1, a+1+m, cmp);
    int l = 0, r = 600000;
    while(l<r){
        int mid = (l+r)/2;
        if(check(mid)){
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    // double ru = 0;
    // if(r%10>=5){
    //     ru = 0.01;
    // }
    printf("%.2lf", double(r)/1000);
}