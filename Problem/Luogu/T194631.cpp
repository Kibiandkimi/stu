//
// Created by kibi on 2021/8/16.
//
//#include <bits/stdc++.h>
//using namespace std;
//int n,m,tr[4000005];
//struct node{
//    int x,y,id,qs,ut;
//}t[4000005];
//int cnt, qy[4000005], ans[7000005];
//int cmp(node a, node b){
//    if(a.x==b.x){
//        if(a.y==b.y){
//            return a.qs <= b.qs;
//        }
//        return a.y < b.y;
//    }
//    return a.x < b.x;
//}
//int lowbit(int x){
//    return x & -x;
//}
//int find1(int x){
//    int l = 1,r = cnt;
//    while(l<r){
//        int mid = (l+r)/2;
//        if(qy[mid] < x){
//            l = mid+1;
//        }else{
//            r = mid-1;
//        }
//    }
//    return l;
//}
//void add(int id, int x, int y, int qs){
//    cnt++;
//    t[cnt].x = x;
//    t[cnt].y = y;
//    t[cnt].id = id;
//    t[cnt].qs = qs;
//    qy[cnt] = y;
//}
//void add_tree(int x, int s){
//    for(int i = x; i <= cnt; i+=lowbit(i)){
//        tr[i]+=s;
//    }
//}
//int find(int x){
//    int s = 0;
//    for(int i = x; i != 0; i-=lowbit(i)){
//        s += tr[i];
//    }
//    return s;
//}
//int main(){
//    cin >> n >> m;
//    for(int i = 1; i <= n; i++){
//        int x,y;
//        scanf("%d %d", &x, &y);
//        add(i, min(x,min(y,i)), max(x,max(y,i)), 0);
//    }
//    for(int i = 1; i <= m; i++){
////        int a,b,c,d;
////        scanf("%d %d %d %d", &a, &b, &c, &d);
//        int l,r;
//        scanf("%d %d", &l, &r);
//        add(i, a-1, b-1, 1);
//        add(i+m, c, d, 1);
//        add(i+m*2, a-1, d, 1);
//        add(i+m*3, c, b-1, 1);
//    }
//    sort(t+1, t+1+cnt, cmp);
//    sort(qy+1, qy+1+cnt);
//    for(int i = 1; i <= cnt; i++){
//        int tof = find1(t[i].y);
//        if(t[i].qs){
//            ans[t[i].id] += find(tof);
//        }else{
//            add_tree(tof, 1);
//        }
//    }
//    for(int i = 1; i <= m; i++){
//        printf("%d\n", ans[i]+ans[i+m]-ans[i+2*m]-ans[i+3*m]);
//    }
//    return 0;
//}
//
//#include <bits/stdc++.h>
//using namespace std;
//int n,m,tr[4000005];
//struct node{
//    int x,y;
//};
//node a[1000005];
//int cmp(node a, node b){
//    return a.x>b.x;
//}
//int main(){
//    cin >> n >> m;
//    for(int i = 1; i < n; i++){
//        int x,y;
//        scanf("%d %d", &x, &y);
//        a[i] = node({min(min(x,y),i), max(max(x,y),i)});
//    }
//    int sa = n-1;
//    sort(a+1,a+n,cmp);
//    for(int i = 1; i <= m; i++){
//        int l,r;
//        scanf("%d %d", &l, &r);
//        int s = 0;
//        for(int j = 1; a[j].x>=l&&j<=sa; j++){
//            if(a[j].y<=r){
//                s++;
//            }
//        }
//        s = r-l+1-s;
//        printf("%d\n", s);
//    }
//}
#include <bits/stdc++.h>
using namespace std;
int n,m,tr[5000005],qy[5000005],ans[5000005],cnt,qs[5000005][2];
struct node{
    int x,y,id,qs;
}t[5000005];
void add(int x, int y, int id, int qs){
    t[++cnt].x = x;
    t[cnt].y = y;
    t[cnt].id = id;
    t[cnt].qs = qs;
    qy[cnt] = y;
}
int cmp(node a, node b){
    if(a.x==b.x){
        if(a.y==b.y){
            return a.qs <= b.qs;
        }
        return a.y < b.y;
    }
    return a.x < b.x;
}
int find1(int x){
    int l = 1, r = cnt;
    while(l < r){
        int mid = (l+r)/2;
        if(qy[mid] < x){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }
    return l;
}
int lowbit(int x){
    return x & -x;
}
int find(int x){
    int s = 0;
    for(int i = x; i != 0; i-=lowbit(i)){
        s += tr[i];
    }
    return s;
}
void add_tree(int x){
    for(int i = x; i <= cnt; i+=lowbit(i)){
        tr[i]+=1;
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i < n; i++){
        int x,y;
        scanf("%d %d", &x, &y);
        add(min(min(x,y),i), max(max(x, y), i), i, 0);
    }
    for(int i = 1; i <= m; i++){
        int l,r;
        scanf("%d %d", &l, &r);
        add(1e9, r, i, 1);
        add(l-1, r, i+m, 1);
        //        add(1e9, r, i, 1);
        //        add(l, r, i+m, 1);
        qs[i][0] = l;
        qs[i][1] = r;
    }
    sort(t+1, t+1+cnt, cmp);
    sort(qy+1, qy+1+cnt);
    for(int i = 1; i <= cnt; i++){
        int tof = find1(t[i].y);
        if(t[i].qs){
            ans[t[i].id] += find(tof);
        }else{
            add_tree(tof);
        }
    }
    for(int i = 1; i <= m; i++){
        //r-l+1-s
        printf("%d\n", qs[i][1]-qs[i][0]+1-(ans[i]-ans[i+m]));
    }
}