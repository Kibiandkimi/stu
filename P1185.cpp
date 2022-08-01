//
// Created by kibi on 2021/7/17.
//
#include <bits/stdc++.h>
using namespace std;
vector<int> a[15];
int n,m;
void o(int l){
    for(int j = 1; j <= l; j++){
        cout << " ";
    }
    return;
}
int s[13][620];
int f(int x, int y){
    if(x > m){
        return 0;
    }
    s[x][y] = 0;
    f(x+1,y*2-1);
    f(x+1,y*2);
}
int main(){
    cin >> m >> n;
    for(int i = 1; i <= n; i++){
        int t,t2;
        cin >> t;
        cin >> t2;
        a[t].push_back(t2);
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= pow(2,i-1); j++){
            s[i][j] = 1;
        }
    }
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < a[i].size(); j++){
            f(i,a[i][j]);
        }
    }
    int rl;
    int l = rl = pow(2,m-2)*6-1;
    l = (l-1)/2;
    for(int i = 1; i < m; i++){
        o(l);
        for(int j = 1; j < pow(2,i-1); j++){
            if(s[i][j]){
                cout<<"o";
            }else{
                cout<<" ";
            }
            o(l);o(l);cout<<" ";
        }
        int t = pow(2,i-1);
        if(s[i][t]){
            cout << "o";
        }else{
            cout << " ";
        }
        o(l);
        cout << endl;
        if(i!=m){
            int ll = (l-1)/2;
            ll+=(i==m-1);
            for(int j = 1; j <= ll; j++){
                int zg = 1, yg = 1;
                for(int k = 1; k <= pow(2,i-1); k++){
                    o(l-j);
                    if(s[i][zg]&&s[i+1][zg+yg-1]){
                        cout << "/";

                    }else{
                        cout << " ";
                    }
                    zg++;
                    o(1+(j-1)*2);
                    if(s[i][yg]&&s[i+1][yg*2]){
                        cout << "\\";

                    }else{
                        cout << " ";
                    }

                    yg++;
                    o(l-j+1);
                }
                cout << endl;
            }
        }
        l = (l-1)/2;
    }
    for(int i = 1; i <= pow(2,m-1)/2; i++){
        if(s[m][i*2-1]){
            cout << "o";
        }else{
            cout << " ";
        }
        o(3);
        if(s[m][i*2]){
            cout << "o";
        }else{
            cout << " ";
        }
        cout << " ";
    }
}