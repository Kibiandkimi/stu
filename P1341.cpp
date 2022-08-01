//
// Created by kibi on 2022/5/14.
//
//? can't work (100pts在下面，t1=-1可是被坑了好久...)
//#include <bits/stdc++.h>
//using namespace std;
//int n;
//vector<int> g[2005];
//int u, v;
//int mn = 200;
////bool vis[205];
//int ans[2005];
//int tot;
//bool gg[2005][2005];
//
//bool cmp(int a, int b){
//    return a<b;
//}
//
//void f(int _u){
//    int sa = g[_u].size();
//
//    for(int i = 0; i < sa; i++){
//        if(!gg[_u][g[_u][i]]){
//            continue;
//        }
//        gg[_u][g[_u][i]] = gg[g[_u][i]][_u] = false;
//        f(g[_u][i]);
//    }
//
//    ans[tot++] = _u;
//}
//
//int main(){
//    scanf("%d", &n);
//    for(int i = 1; i <= n; i++){
//        int _u, _v;
//        scanf("%1s %1s", &_u, &_v);
//        //        printf("%d %d", _u, _v);
//        g[_u].push_back(_v);
//        g[_v].push_back(_u);
//
//        gg[_u][_v] = gg[_v][_u] = true;
//
//        mn = min(mn, _u);
//        mn = min(mn, _v);
//    }
//
//    for(int j = 0; j <= 200; j++){
//        if(g[j].size()%2){
//            if(!u){
//                u = j;
//            }else if(!v){
//                v = j;
//            }else{
//                printf("No Solution");
//                return 0;
//            }
//        }
//        sort(g[j].begin(), g[j].end(), cmp);
//    }
//
//    if(u&&!v){
//        printf("No Solution");
//        return 0;
//    }else if(!u){
//        u = mn;
//    }
//
//    f(u);
//
//    if(tot-1 != n){
//        printf("No Solution");
//        return 0;
//    }
//
//    for(int i = tot-1; i >= 0; i--){
//        printf("%c", (char)ans[i]);
//        //        cout << (char)ans[i];
//    }
//
//    return 0;
//}

#include <bits/stdc++.h>
using namespace std;
int n;
bool g[105][105];
bool vis[105][105];
bool vis2[105];
int s[105];
int t1, t2, t3;
int t;
stack<int> st;
vector<int> li, l1, l2;
bool f(int u){
    //    if(u == to){
    //        st.push(u);
    //        return;
    //    }
    t++;
    if(t == n+1){
        st.push(u);
        return true;
    }
    bool flag = false;
    for(int i = 0; i <= 'z'-65; i++){
        if((!vis[u][i])&&(g[u][i])){
            vis[u][i] = vis[i][u] = true;
            if(f(i)){
                flag = true;
                vis[u][i] = vis[i][u] = false;
                break;
            }
            vis[u][i] = vis[i][u] = false;
            //            break;
        }
    }
    if(flag) {
        st.push(u);
    }
    t--;
    return flag;
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        char tt[2];
        char a, b;
        scanf("%s", tt);
        a = tt[0], b = tt[1];
        a -= 65;
        b -= 65;
        g[a][b] = g[b][a] = true;
        vis2[a] = vis2[b] = true;
        s[a]++;
        s[b]++;
        //        if()
    }
    t1 = -1;
    //    t2 = -1;
    for(int i = 0; i <= 'z'-65; i++){
        if(s[i]%2){
            if(t1 == -1){
                t1 = i;
            }else{
                t2 = i;
            }
            t3++;
        }
    }
    if(t3>2||t3==1){
        printf("No Solution");
        return 0;
    }else if(t3 == 2){
        //        to = t2;
        if(f(t1)){
            while(!st.empty()){
                printf("%c", st.top()+65);
                st.pop();
            }
            return 0;
        }else{
            while(!st.empty()){
                st.pop();
            }
        }

        //        to = t1;


        //        t = 0;
        //        if(f(t2)){
        //            while(!st.empty()){
        //                printf("%c", st.top()+65);
        //                st.pop();
        //            }
        //        }else{
        //            printf("No Solution");
        //        }


        //        while (!st.empty()){
        //            l2.push_back(st.top());
        //            st.pop();
        //        }
        //        if(l1.size()!=(n+1)){
        //            if(l2.size()!=n+1){
        //                printf("No Solution");
        //            }else{
        //                for(int i = 0; i <= n; i++){
        //                    printf("%c", (char)l2[i]);
        //                }
        //            }
        //        }else if(l2.size()!=n+1){
        //            for(int i = 0; i <= n; i++){
        //                printf("%c", (char)l1[i]);
        //            }
        //        }
        printf("No Solution");
        return 0;
    }

    //    for(int i = 0; i <= n; i++){
    //        li.push_back(200);
    //    }
    for(int i = 0; i <= 'z'-65; i++){
        if(vis2[i]){
            t = 0;
            if(f(i)){
                for(int j = 0; j <= n; j++){
                    printf("%c", st.top()+65);
                    st.pop();
                }
                return 0;
            }else{
                while(!st.empty()){
                    st.pop();
                }
            }
            break;
            //            if(st.size()==n+1){
            //                bool flag = false;
            //                int j = 0;
            //                while(!st.empty()){
            //                    char u = st.top();
            //                    if(u > li[j] && !flag){
            //                        break;
            //                    }else if (u < li[j] && li[j] != 200){
            //                        flag = true;
            //                    }
            //                    li[j++] = u;
            //                }
            //            }
        }
    }
    printf("No Solution");

}