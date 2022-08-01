//
// Created by kibi on 2021/7/5.
//
#include<bits/stdc++.h>
using namespace std;
int a[50][50],r,c;
class node{
public:
    int x,y,step;
};
int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
int main(){
    cin >> r >> c;
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            char t;
            cin >> t;
            a[i][j]=t;
            //cout <<a[i][j];
        }
    }
    queue<node> q;
    node s,t;
    s.x = 1;
    s.y = 1;
    s.step = 0;
    a[1][1]='#';
    q.push(s);
    while(!q.empty()){
        t = s = q.front();
        if(t.x==r&&t.y==c){
            cout << t.step+1;
            return 0;
        }
        for(int i = 0; i < 4; i++){
            t=s;
            t.x+=dir[i][0];
            t.y+=dir[i][1];
            t.step++;
            if(t.x>0&&t.x<=r&&t.y>0&&t.y<=c&&a[t.x][t.y]!='#'){
                q.push(t);
                if(a[t.x][t.y]=='$'){
                    for(int i = 1; i <= r; i++){
                        for(int j = 1; j <= c; j++){
                            if(a[i][j]=='$'&&(i!=t.x||j!=t.y)){
                                node tt = t;
                                tt.x = i;
                                tt.y = j;
                                q.push(tt);
                                a[i][j]='#';
                            }
                        }
                    }
                }
                a[t.x][t.y]='#';
            }
        }
        a[s.x][s.y]='#';
        q.pop();
    }
    cout << -1;
}