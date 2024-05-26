//
// Created by kibi on 22-8-30.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<int> a[300005];
int raw[300005];

bool getType(int c);
void read(int &x);
int find(int x, int c);

int main(){
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        int c;
        read(c);
        a[c].push_back(i);
        raw[i] = c;
    }
    while(m--){
        int opt;
        read(opt);
        if(opt == 1){
            int l, r, c;
            read(l), read(r), read(c);
            int rl = find(l, c), rr = find(r, c);
            if(rl == a[c].size() || !a[c].size()){
                printf("0\n");
            }else {
                while (a[c][rl] < l) {
                    rl++;
                }
                if (rr == a[c].size()) {
                    rr--;
                }
                while (a[c][rr] > r) {
                    rr--;
                }
                printf("%d\n", rr - rl + 1);
            }
        }else if(opt == 2){
            int x;
            read(x);
            if(raw[x] == raw[x+1]){
                continue;
            }
            int u = find(x, raw[x]), v = find(x+1, raw[x+1]);
            a[raw[x]][u] = x+1;
            a[raw[x+1]][v] = x;
            swap(raw[x], raw[x+1]);
        }
    }
}

bool getType(int c){
    return c<'0'||'9'<c;
}

void read(int &x){
    int s = 0, w= 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c= getchar();
    }
    while(!getType(c)){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

int find(int x, int c){
    int l = 0, r = a[c].size();
    while(l < r){
        int mid = (l+r)/2;
        if(x>a[c][mid]){
            l = mid+1;
        }else if(x < a[c][mid]){
            r = mid;
        }else{
            return mid;
        }
    }
    return l;
}
/*
 * 别人的代码
 * 75pts, 主席树, 要卡常才行
 * #include<bits/stdc++.h>
using namespace std;
int n,m,root[8000000],cnt=0,aa[300100],bb[300100],ar[300100];
struct nb{
    int l,r,sum;
}tree[300005*60];
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
//    build(root[0],1,len);
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
            //			change(root[b],1,len,aa[b],-1);
            //			change(root[b],1,len,aa[b+1],1);
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
 */
/*
 * fread卡过了就很神奇
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
*/