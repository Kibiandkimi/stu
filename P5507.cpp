//
// Created by kibi on 2022/4/10.
//
//启发式搜索
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct node{
    int fx[13];//每个机关的状态
    int num, h;//num -> step步数， h -> 预测函数
    ll stand;//上一状态，回溯
    bool operator < (const node& b) const{
        return num+h > b.num+b.h;//评估函数
    }
};//表示状态
priority_queue<node> pq;
int inp[13][5];//联动机关
stack<int> ans;
int fa[70000000], flag[70000000];
bool vis[70000000];
void con(node& a){//计算预测函数
    int kk = 0;
    for(int i = 1; i <= 12; i++){
        if(a.fx[i] != 1){
            kk += 5 - a.fx[i];
        }
    }
    a.h = ((kk - 1) >> 1) + 1;
}
int nex(int x){
    return x==4 ? 1 : x+1;
}//计算机关的下一个状态·
int main(){
    node now;
    for(int i = 1; i <= 12; i++){
        scanf("%d", &now.fx[i]);
        for(int j = 1; j <= 4; j++){
            scanf("%d", &inp[i][j]);
        }
    }
    now.num = 0;
    con(now);
    pq.push(now);
    while(!pq.empty()){
        node from = pq.top();
        pq.pop();

        if(from.h == 0){
            printf("%d\n", from.num);
            ll noww = from.stand;//回溯起点
            for(int i = 1; i <= from.num; i++){
                ans.push(flag[noww]);
                noww = fa[noww];//回溯
            }
            for(int i = 1; i <= from.num; i++){
                printf("%d ", ans.top());
                ans.pop();
            }
            return 0;
        }
        for(int i = 1; i <= 12; i++){
            node to = from;
            //更新状态
            to.num++;
            to.fx[ inp[i][ to.fx[i] ] ] = nex(to.fx[ inp[i][ to.fx[i] ] ]);
            to.fx[i] = nex(to.fx[i]);
            //计算状态的哈希
            ll standd = 0;
            for(int j = 1; j <= 12; j++){
                standd = (standd<<2) + to.fx[j];
            }

            if(vis[standd]){
                continue;
            }
            vis[standd] = true;

            to.stand = standd;
            fa[standd] = from.stand;
            flag[standd] = i;

            con(to);
            pq.push(to);
        }
    }
    return 0;
}