//
// Created by kibi on 2021/8/12.
//
#include <bits/stdc++.h>
using namespace std;
long long n,t,s;
struct node{
    long long x,y1,y2,e;
};
struct node2{
    long long y1, y2;
};
node a[2005];
vector<node2> x;
bool cmp(node a, node b){
    return a.x<b.x;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        long long x1,x2,y1,y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        a[i*2-1].x = x1;a[i*2-1].y1 = y1;a[i*2-1].y2 = y2;a[i*2-1].e = 1;
        a[i*2].x = x2;a[i*2].y1 = y1;a[i*2].y2 = y2;a[i*2].e = -1;
    }
    sort(a+1, a+1+n*2, cmp);
    for(int i = 1; i <= 2*n; i++){
        if(a[i].e==1){
            x.push_back(node2({a[i].y1, a[i].y2}));
            vector<node2> tt;
            tt.push_back(node2({x[0].y1, x[0].y2}));
            for(int j = 1; j < x.size(); j++){
                if(tt.size()==1){
                    if(x[j].y1<tt[0].y2||x[j].y2>tt[0].y1){
                        tt.push_back(node2({x[j].y1, x[j].y2}));
                    }else{
                        tt[0].y1 = max(tt[0].y1, x[j].y1);
                        tt[0].y2 = min(tt[0].y2, x[j].y2);
                    }
                }else{
                    vector<int> v;
                    for(int k = 0; k < tt.size(); k++){
                        if(!(x[j].y1<tt[k].y2||x[j].y2>tt[k].y1)){
                            v.push_back(k);
                        }
                    }
                    long long mxx = x[j].y1, mnn = x[j].y2;
                    for(int k = 0; k < v.size(); k++){
                        mxx = max(mxx, tt[v[k]-k].y1);
                        mnn = min(mnn, tt[v[k]-k].y2);
                        tt.erase(tt.begin()+v[k]-k);
                    }
                    tt.push_back(node2({mxx,mnn}));
                }
            }
            long long ss = 0;
            for(int j = 0; j < tt.size(); j++){
                ss += tt[j].y1 - tt[j].y2;
            }
            t++;
            s+=(a[i+1].x-a[i].x)*ss;
        }else{
            //            long long mxx = -1e9,mnn = 1e9;
            //            bool f1 = false, f2 = false;
            for(int j = 0; j < x.size(); j++){
                if(x[j].y1==a[i].y1&&x[j].y2==a[i].y2){
                    x.erase(x.begin() + j);
                    j = x.size();
                }
            }
            t--;
            if(t){
                vector<node2> tt;
                tt.push_back(node2({x[0].y1, x[0].y2}));
                for(int j = 1; j < x.size(); j++){
                    if(tt.size()==1){
                        if(x[j].y1<tt[0].y2||x[j].y2>tt[0].y1){
                            tt.push_back(node2({x[j].y1, x[j].y2}));
                        }else{
                            tt[0].y1 = max(tt[0].y1, x[j].y1);
                            tt[0].y2 = min(tt[0].y2, x[j].y2);
                        }
                    }else{
                        vector<int> v;
                        for(int k = 0; k < tt.size(); k++){
                            if(!(x[j].y1<tt[k].y2||x[j].y2>tt[k].y1)){
                                v.push_back(k);
                            }
                        }
                        long long mxx = x[j].y1, mnn = x[j].y2;
                        for(int k = 0; k < v.size(); k++){
                            mxx = max(mxx, tt[v[k]-k].y1);
                            mnn = min(mnn, tt[v[k]-k].y2);
                            tt.erase(tt.begin()+v[k]-k);
                        }
                        tt.push_back(node2({mxx,mnn}));
                    }
                }
                long long ss = 0;
                for(int j = 0; j < tt.size(); j++){
                    ss += tt[j].y1 - tt[j].y2;
                }
                s+=(a[i+1].x-a[i].x)*ss;
            }
        }
    }
    cout << s;
}