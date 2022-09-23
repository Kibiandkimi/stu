//100pts在下

#include<bits/stdc++.h>
using namespace std;
char a[305][305];
int n,m,vis[305][305],cs[150][2];//cs,0-x,1-y
class node{
public:
    int x,y,step;
};
int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
node s,to,now,t;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
            if(a[i][j]=='#'){
                vis[i][j]=-1;
            }else if(a[i][j]=='@'){
                s.x=i;
                s.y=j;
            }else if(a[i][j]=='='){
                to.x=i;
                to.y=j;
            }else if(a[i][j]>='A'&&a[i][j]<='Z'){
                cs[a[i][j]][0]+=i;
                cs[a[i][j]][1]+=j;
            }
        }
    }
    s.step = 0;
    queue<node> q;
    q.push(s);
    long long tem = 0;
    while(!q.empty()){
        //        if(tem%10000==0){
        //            for(int i = 1; i <= n; i++){
        //                for(int j = 1; j <= m; j++){
        //                    cout << ((vis[i][j]==-1)?9:vis[i][j]) << " ";
        //                }
        //                cout << endl;
        //            }
        //            cout << endl << endl;
        //        }
        t = now = q.front();
        if(now.x==to.x&&now.y==to.y){
            cout << now.step;
            return 0;
        }
        if(a[t.x][t.y]>='A'&&a[t.x][t.y]<='Z'){
            now.x = cs[a[t.x][t.y]][0]-now.x;
            now.y = cs[a[t.x][t.y]][1]-now.y;
            for(int i = 0; i < 4; i++){
                t=now;
                t.x+=dir[i][0];
                t.y+=dir[i][1];
                if(t.x>0&&t.x<=n&&t.y>0&&t.y<=m&&vis[t.x][t.y]==0){
                    t.step++;
                    q.push(t);
                }
            }
            now.x = cs[a[t.x][t.y]][0]-now.x;
            now.y = cs[a[t.x][t.y]][1]-now.y;
        }else{
            for(int i = 0; i < 4; i++){
                t=now;
                t.x+=dir[i][0];
                t.y+=dir[i][1];
                if(t.x>0&&t.x<=n&&t.y>0&&t.y<=m&&vis[t.x][t.y]==0){
                    t.step++;
                    q.push(t);
                }
            }
        }
        vis[now.x][now.y]=1;
        q.pop();
    }
}

namespace pts100 {
    #include<bits/stdc++.h>
    using namespace std;
    char a[305][305];
    int n,m,vis[305][305],cs[150][2], fix1[305][305], mem[305][305];//cs,0-x,1-y
    struct node{
        //public:
        int x,y,step;
    };
    int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
    node s,to;

    void read(int &x){
        int s = 0, w = 1, c = getchar();
        while(c < '0' || '9' < c){
            if(c == '-'){
                w *= -1;
            }
            c = getchar();
        }
        while('0'<=c&&c<='9'){
            s = s*10+c-'0';
            c = getchar();
        }
        x = s*w;
    }
    void read(char &x){
        int c = getchar();
        while((c<'A'||'Z'<c)&&c!='#'&&c!='@'&&c!='='&&c!='.'){
            c = getchar();
        }
        x = (char)c;
    }



    int main() {
        //    cin >> n >> m;
        read(n), read(m);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                //            cin >> a[i][j];
                read(a[i][j]);
                //            cin >> a[i][j];
                if (a[i][j] == '#') {
                    vis[i][j] = -1;
                } else if (a[i][j] == '@') {
                    s.x = i;
                    s.y = j;
                } else if (a[i][j] == '=') {
                    to.x = i;
                    to.y = j;
                } else if (a[i][j] >= 'A' && a[i][j] <= 'Z') {
                    cs[a[i][j]][0] += i;
                    cs[a[i][j]][1] += j;
                }
            }
        }
        s.step = 0;
        memset(mem, 0x3f, sizeof mem);
        mem[s.x][s.y] = 0;
        queue<node> q;
        q.push(s);
        while (!q.empty()) {
            node t{}, now = q.front();
            t = now;
            q.pop();
            if (now.x == to.x && now.y == to.y) {
                printf("%d", now.step);
                return 0;
            }
            if (a[t.x][t.y] >= 'A' && a[t.x][t.y] <= 'Z') {
                now.x = cs[a[t.x][t.y]][0] - now.x;
                now.y = cs[a[t.x][t.y]][1] - now.y;
                for (auto &i : dir) {
                    t = now;
                    t.x += i[0];
                    t.y += i[1];
                    if (t.x > 0 && t.x <= n && t.y > 0 && t.y <= m && vis[t.x][t.y] == 0) {
                        t.step++;
                        if (t.step < mem[t.x][t.y]) {
                            mem[t.x][t.y] = t.step;
                            q.push(t);
                        }
                    }
                }
                //            fix1[now.x][now.y]++;
            } else {
                vis[now.x][now.y] = 1;
                for (auto &i : dir) {
                    t = now;
                    t.x += i[0];
                    t.y += i[1];
                    if (t.x > 0 && t.x <= n && t.y > 0 && t.y <= m && vis[t.x][t.y] == 0) {
                        t.step++;
                        if (t.step < mem[t.x][t.y]) {
                            mem[t.x][t.y] = t.step;
                            q.push(t);
                        }
                    }
                }
            }
        }
    }
}