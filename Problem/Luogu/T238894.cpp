//
// Created by kibi on 2022/8/6.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, x, y;
vector<int> v[1005][1005];
int ans[1005][1005];
char c[1005];

int main(){
    //    scanf("%d %d %d %d %s", &n, &m, &x, &y, c+1);
    cin >> n >> m >> y >> x;
    cin >> c;
    v[x][y].push_back(1);
    for(int i = 0; i < m-1; i++){
        char s = c[i];
        if(s == 'N'){
            x++;
        }else if(s == 'S'){
            x--;
        }else if(s == 'W'){
            y--;
        }else if(s == 'E'){
            y++;
        }
        v[x][y].push_back(i+2);
    }
    for(int i = n; i >= 1; i--){
        for(int j = 1; j <= n; j++){
            int sv = v[i][j].size();
            int st = 1;
            for(int k = 0; k < sv; k++){
                int t1 = 1, tn = v[i][j][k]-st;
                ans[i][j] += (t1+tn)*tn/2;
                st = v[i][j][k]+1;
            }
            ans[i][j] += (1+m+1-st)*(m+1-st)/2;
            //            printf("%d ", ans[i][j]);
            cout << ans[i][j] << " ";
        }
        if(i == 1){
            return 0;
        }
        //        printf("\n");
        cout << endl;
    }
}