//
// Created by kibi on 2021/7/3.
//
#include <bits/stdc++.h>
using namespace std;
int mp1[55][55],mp2[55][55],dis[55][55][4],n,m,sx,sy,ex,ey,d;
struct node{
    int x,y,step,d;
};
bool pd(int x, int y, int d){
    return x>0&&x<n&&y>0&&y<m&&(dis[x][y][d]==0);
}
bool pd2(int sx,int sy,int ex,int ey){
    if(sx == ex){
        int mmin = min(sy,ey);
        int mmax = max(sy,ey);
        for(int i = mmin+1; i < mmax; i++){
            if(dis[sx][i][0]==-1){
                return 0;
            }
        }
        return  1;
    }
    if(sy == ey){
        int mmin = min(sx,ex);
        int mmax = max(sx,ex);
        for(int i = mmin+1; i < mmax; i++){
            if(dis[i][sy][0]==-1){
                return 0;
            }
        }
        return  1;
    }
}
int o1(int d){
    return d<4&&d>=0?d:d==-1?3:0;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin>>mp1[i][j];
        }
    }
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            mp2[i][j] = mp1[i][j] || mp1[i+1][j] || mp1[i][j+1] || mp1[i+1][j+1];
            dis[i][j][0]=dis[i][j][1]=dis[i][j][2]=dis[i][j][3]=mp2[i][j]==1?-1:0;
        }
    }
    char t;
    cin >> sx >> sy >> ex >> ey >> t;
    d = t=='N'?0:t=='E'?1:t=='S'?2:3;
    //    cout << d << endl;
    node now,to;
    now.x=sx;
    now.y=sy;
    now.step=0;
    now.d=d;
    queue<node> q;
    q.push(now);
    while(!q.empty()){
        now = q.front();
        to = now;
        int x = to.x, y = to.y;
        if(x == ex && y == ey){
            cout << to.step << endl;
            /*
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++){
                    for(int k = 0; k < 4; k++){
                        cout << dis[i][j][k] << " ";
                    }
                    cout << "   ";
                }
                cout << endl;
            }
            */
            return 0;
        }
        to.d++;
        to.d=o1(to.d);
        if(pd(to.x,to.y,to.d)){
            dis[x][y][to.d] = to.step+1;
            to.step++;
            q.push(to);
        }
        to = now;
        to.d--;
        to.d=o1(to.d);
        if(pd(to.x,to.y,to.d)){
            dis[x][y][to.d] = to.step+1;
            to.step++;
            q.push(to);
        }
        to=now;
        switch(to.d){
            case 0:{
                for(int i = 1; i <= 3; i++){
                    to.x-=i;
                    if(pd(to.x,y,to.d)&&pd2(now.x,now.y,to.x,to.y)){
                        dis[to.x][y][to.d] = to.step+1;
                        to.step++;
                        q.push(to);
                    }
                    to = now;
                }
                break;
            }case 1:{
                for(int i = 1; i <= 3; i++){
                    to.y+=i;
                    if(pd(x,to.y,to.d)&&pd2(now.x,now.y,to.x,to.y)){
                        dis[x][to.y][to.d] = to.step+1;
                        to.step++;
                        q.push(to);
                    }
                    to = now;
                }
                break;
            }case 2:{
                for(int i = 1; i <= 3; i++){
                    to.x+=i;
                    if(pd(to.x,y,to.d)&&pd2(now.x,now.y,to.x,to.y)){
                        dis[to.x][y][to.d] = to.step+1;
                        to.step++;
                        q.push(to);
                    }
                    to = now;
                }
                break;
            }case 3:{
                for(int i = 1; i <= 3; i++){
                    to.y-=i;
                    if(pd(x,to.y,to.d)&&pd2(now.x,now.y,to.x,to.y)){
                        dis[x][to.y][to.d] = to.step+1;
                        to.step++;
                        q.push(to);
                    }
                    to = now;
                }
                break;
            }
        }
        q.pop();
    }
    cout << -1;
}