#include<bits/stdc++.h>
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<1000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
//template<int>
inline void read(register int &x){
    x=0;register int f=1;register char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=f;
}
static char cc[20];
//template<int>
inline void print(register int x){
    register int len=0;
    if(x<0)x=-x,putchar('-');
    while(x)cc[len++]=x%10+'0',x/=10;
    while(len--)putchar(cc[len]);
}
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
     read(n), read(m);
//    scanf("%d %d", &n, &m);
    //    cin>>n>>m;
    for(int i=1;i<=n;i++){
         read(aa[i]);
//        scanf("%d", &aa[i]);
        //        cin>>aa[i];
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
//        scanf("%d", &a);
        read(a);
        //        cin>>a;
        if(a==1){
//            scanf("%d %d %d", &b, &c, &d);
             read(b), read(c), read(d);
            //            cin>>b>>c>>d;
            if(!ar[d]){
//                print(0);
//                putchar('\n');
                //                cout << 0 << endl;
                printf("0\n");
                continue ;
            }
//            print(query(root[b-1],root[c],1,len,ar[d]));
//            putchar('\n');
            printf("%d\n", query(root[b-1],root[c],1,len,ar[d]));
            //            cout<<query(root[b-1],root[c],1,len,ar[d])<<endl;
        }
        else{
//            scanf("%d", &b);
             read(b);
            //            cin>>b;
            if(aa[b] == aa[b+1]){
                continue ;
            }
            insert(root[b],root[b],1,len,aa[b],-1);
            insert(root[b],root[b],1,len,aa[b+1],1);
            swap(aa[b],aa[b+1]);
        }
    }
//    fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}