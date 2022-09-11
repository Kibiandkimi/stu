#include<bits/stdc++.h>
using namespace std;
int n,m,root[400000*7],cnt=0,aa[300100],bb[300100];
struct nb{
    int l,r,sum;
}tree[400000*8];
void build(int& x,int l,int r){
    x=++cnt;
    if(l==r){
        tree[x].l=tree[x].r=l;
        tree[x].sum=0;
        return ;
    }
    int mid=(l+r)>>1;
    build(tree[x].l,l,mid);
    build(tree[x].r,mid+1,r);
}
int len;
int bian(int x){
    return lower_bound(bb+1,bb+len+1,x)-bb;
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
//void change(int x,int l,int r,int pos,int val){
//	if(l==r){
//		tree[x].sum+=val;
//		return ;
//	}
//	int mid=(l+r)>>1;
//	if(pos<=mid){
//		change(tree[x].l,l,mid,pos,val);
//	}
//	else{
//		change(tree[x].r,mid+1,r,pos,val);
//	}
//}
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
    build(root[0],1,len);
    for(int i=1;i<=n;i++){
        aa[i]=bian(aa[i]);
        insert(root[i],root[i-1],1,len,aa[i],1);
    }
    for(int i=1;i<=m;i++){
        int a,b,c,d;
        cin>>a;
        if(a==1){
            cin>>b>>c>>d;
            cout<<query(root[b-1],root[c],1,len,bian(d))<<endl;
        }
        else{
            cin>>b;
            //			change(root[b],1,len,aa[b],-1);
            //			change(root[b],1,len,aa[b+1],1);
            insert(root[b],root[b],1,len,aa[b],-1);
            insert(root[b],root[b],1,len,aa[b+1],1);
            swap(aa[b],aa[b+1]);
        }
    }
    return 0;
}