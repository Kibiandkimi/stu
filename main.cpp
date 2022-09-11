#include<bits/stdc++.h>
using namespace std;
int n,m,root[8000000],cnt=0,aa[300100],bb[300100],ar[300100];
struct nb{
    int l,r,sum;
}tree[300005*60];
int len;
int bian(int x){
    return ar[x]?ar[x]:lower_bound(bb+1,bb+len+1,x)-bb;
}
void insert(int& now,int pre,int l,int r,int pos,int val){
    now=++cnt;
    tree[now]=tree[pre];
    if(l==r){
        tree[now].sum+=val;
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid){
        insert(tree[now].l,tree[pre].l,l,mid,pos,val);
    }
    else{
        insert(tree[now].r,tree[pre].r,mid+1,r,pos,val);
    }
}
int query(int x,int y,int l,int r,int pos){
    if(l==r){
        return tree[y].sum-tree[x].sum;
    }
    int mid=(l+r)>>1;
    if(pos<=mid){
        return query(tree[x].l,tree[y].l,l,mid,pos);
    }
    else{
        return query(tree[x].r,tree[y].r,mid+1,r,pos);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>aa[i];
        bb[i]=aa[i];
    }
    sort(bb+1,bb+n+1);
    len=unique(bb+1,bb+n+1)-bb-1;
    for(int i=1;i<=n;i++){
        int t = aa[i];
        aa[i]=bian(aa[i]);
        insert(root[i],root[i-1],1,len,aa[i],1);
        ar[t] = aa[i];
    }
    for(int i=1;i<=m;i++){
        int a,b,c,d;
        cin>>a;
        if(a==1){
            cin>>b>>c>>d;
            if(!ar[d]){
                cout << 0 << endl;
                continue ;
            }
            cout<<query(root[b-1],root[c],1,len,ar[d])<<endl;
        }
        else{
            cin>>b;
            if(aa[b] == aa[b+1]){
                continue ;
            }
            insert(root[b],root[b],1,len,aa[b],-1);
            insert(root[b],root[b],1,len,aa[b+1],1);
            swap(aa[b],aa[b+1]);
        }
    }
    return 0;
}