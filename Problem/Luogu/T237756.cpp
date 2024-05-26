//
// Created by kibi on 22-8-20.
//
#include <bits/stdc++.h>

using namespace std;
int n, q, a[1100005], m;
int b[105], c[105], ans[105];

//int find_q(int l, int r, int x, int t){
//    int mid = (l+r)/2;
//    if(l==r){
//        return l;
//    }
//    while(l < r){
//        mid = (l+r)/2;
//        if(c[mid]<x){
//            l = mid+1;
//        }else{
//            r = mid;
//        }
//    }
//    return c[mid]==x?mid:mid+t;
//}

//int cnt;
//void get(int l,int r, int ql, int qr)
//{
////    if(l==r) return l;
////    cnt++;
////    int w=rand()%2;
////    int mid=(l+r+w)/2;
////    if(num[mid]-w<x) return get(num,x,mid+!w,r);
////    else return get(num,x,l,mid-w);
//
//    if(l==r){
////        for(int i = ql; i <= qr; i++){
////            ans[i] = min(ans[i], cnt);
////        }
//        ans[ql] = min(ans[ql], cnt);
////        cnt--;
//        return ;
////        return l;
//    }
//    ++cnt;
//    if((l+r)%2!=0){
//        int mid = (l+r)/2;
//        if(c[ql]<=a[mid]){
//            get(l, mid, ql, find_q(ql, qr, a[mid], 0));
//        }
//        if(c[qr]>a[mid]){
//            get(mid+1, r, find_q(ql, qr, a[mid+1], 1), qr);
//        }
//    }else{
//        int mid = (l+r)/2;
//        if(c[ql]<=a[mid]){
//            get(l, mid, ql, find_q(ql, qr, a[mid], 0));
//        }
//        if(c[qr]>a[mid]){
//            get(mid+1, r, find_q(ql, qr, a[mid+1], 1), qr);
//        }
//        mid = (l+r)/2-1;
//        if(c[ql]<=a[mid]){
//            get(l, mid, ql, find_q(ql, qr, a[mid], 0));
//        }
//        if(c[qr]>a[mid]){
//            get(mid+1, r, find_q(ql, qr, a[mid+1], 1), qr);
//        }
//    }
//    --cnt;
//
//}

//int find_q(int x){
//    int l = 1, r = m, mid = (l+r)/2;
//    while(l < r){
//        mid = (l+r)/2;
//        if(c[mid]<x){
//            l=mid+1;
//        }else{
//            r = mid;
//        }
//    }
//    mid = (l+r)/2;
//    return c[mid]==x?mid:103;
//}
//
//int cnt;
//void get(int l, int r) {
////    if(l==r) return l;
////    cnt++;
////    int w=rand()%2;
////    int mid=(l+r+w)/2;
////    if(num[mid]-w<x) return get(num,x,mid+!w,r);
////    else return get(num,x,l,mid-w);
//
//    if (l == r) {
//        int loc = find_q(a[l]);
//        ans[loc] = min(ans[loc], cnt);
//        return;
//
//    }
//    ++cnt;
//    if ((l + r) % 2 != 0) {
//        int mid = (l + r) / 2;
//        get(l, mid);
//        get(mid + 1, r);
//    } else {
//        int mid = (l + r) / 2;
//        get(l, mid);
//        get(mid + 1, r);
//
//        mid = (l + r) / 2 - 1;
//        get(l, mid);
//        get(mid + 1, r);
//    }
//    --cnt;
//}

//void find(int *num,int x,int len)
//{
//    cnt=0;
//    get(1,len, 1, m);
//}

int find_w(int x) {
    for (int i = 1; i <= m; i++) {
        if (c[i] == x) {
            return ans[i];
        }
    }
}

int find_q(int x){
    int l = 1, r = m, mid = (l+r)/2;
    while(l < r){
        mid = (l+r)/2;
        if(c[mid]<x){
            l=mid+1;
        }else{
            r = mid;
        }
    }
    mid = (l+r)/2;
    return c[mid]==x?mid:103;
}

int cnt;
void get(int *num,int x,int l,int r)
{
    if(l==r) {
        int loc = find_q(num[l]);
        ans[loc] = min(ans[loc], cnt);
        return ;
    }
    cnt++;
    if((l+r)%2!=0){
        int w=0;
        int mid=(l+r+w)/2;
        if(num[mid]-w<x) get(num,x,mid+!w,r);
        else get(num,x,l,mid-w);
    }else {
        int w = 1;
        int mid = (l + r + w) / 2;
        if (num[mid] - w < x) get(num, x, mid + !w, r);
        else get(num, x, l, mid - w);
        w=0;
        mid=(l+r+w)/2;
        if(num[mid]-w<x) get(num,x,mid+!w,r);
        else get(num,x,l,mid-w);
    }
    cnt--;
}
void find(int *num,int x,int len)
{
    cnt=0;
    get(num,x,1,len);
}

int main() {
    memset(ans, 0x3f, sizeof ans);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d", &b[i]);
        c[i] = b[i];
    }
    m = unique(c + 1, c + 1 + q) - c - 1;
    sort(c + 1, c + 1 + m);
//    get(1, n);
    for(int i = 1; i <= m; i++){
        find(a, c[i], n);
//        ans[i] = cnt;
    }
    for (int i = 1; i <= q; i++) {
        printf("%d\n", find_w(b[i]));
    }
}