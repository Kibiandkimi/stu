//
// Created by kibi on 22-9-12.
//
#include <bits/stdc++.h>
using namespace std;
const int MXX = 100005, MXC = 3000010;
int s[1000005], x[100005], Q, n, ss, cnt, rawAns;
bool flag[100005];
//vector<int> g[100005];

void read(int &x);
void reads();
void pre();
//bool getValue();

int main(){
    reads();
    read(n);
    for (int i = 1; i <= n; ++i) {
        read(x[i]);
    }
    pre();
    read(Q);
    while(Q--){
        int p;
        read(p);
        //        x[p] = !x[p];
        printf("%d\n", flag[p] == !rawAns);
        //        x[p] = !x[p];
    }
}

void reads(){
    int c = getchar(), p = 1;
    while(c != '\n'){
        if('0'<=c&&c<='9'){
            s[p] = s[p]*10 + c-'0';
        }else if(c == ' '){
            p++;
        }else if(c != 'x'){
            s[p] = c+MXX;
        }
        c = getchar();
    }
    ss = s[p]?p:p-1;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

//bool getValue(){
//    static int stk[100005];
//    int r = -1;
//    for(int i = 1; i <= ss; i++){
//        if(s[i] > MXX){
//            int opt = s[i] - MXX;
//            if(opt != '!'){
//                int o1 = stk[r], o2;
//                r--;
//                o2 = stk[r];
//                r--;
//                stk[++r] = (opt == '&' ? o1&o2 : o1|o2);
//            }else{
//                int o = stk[r];
//                r--;
//                stk[++r] = !o;
//            }
//        }else{
//            stk[++r] = x[s[i]];
//        }
//    }
//    return stk[r];
//}
int stk[100005], id[100005];
int in[3000005][2];
bool fl[3000005];
void pre(){
    int r = -1;
    //    memset(fl, 1, sizeof fl);
    for(int i = 1; i <= ss; i++){
        if(s[i] > MXX){
            int opt = s[i] - MXX;
            if(opt != '!'){
                int o1 = stk[r], o2, id1 = id[r], id2;
                r--;
                o2 = stk[r];
                id2 = id[r];
                r--;
                if(opt == '&'){
                    if(o1&o2){
                        fl[id1] = fl[id2] = true;
                    }else if(!(o1|o2)){
                        fl[id1] = fl[id2] = false;
                    }else if(!o1){
                        fl[id2] = false, fl[id1] = true;
                    }else if(!o2){
                        fl[id2] = true, fl[id1] = false;
                    }
                    stk[++r] = o1&o2;
                    id[r] = ++cnt;
                    in[cnt][0] = id1, in[cnt][1] = id2;
                }else{
                    if(!(o1|o2)){
                        fl[id1] = fl[id2] = true;
                    }else if(o1&o2){
                        fl[id1] = fl[id2] = false;
                    }else if(o1){
                        fl[id2] = false, fl[id1] = true;
                    }else if(o2){
                        fl[id2] = true, fl[id1] = false;
                    }
                    stk[++r] = o1|o2;
                    id[r] = ++cnt;
                    in[cnt][0] = id1, in[cnt][1] = id2;
                }
            }else{
                stk[r] = !stk[r];
            }
        }else{
            stk[++r] = x[s[i]];
            id[r] = ++cnt;
            in[cnt][0] = s[i]+MXC;
            in[cnt][1] = 0;
            //            fl[cnt] = true;
        }
    }
    rawAns = stk[r];
    queue<pair<int, bool> > q;
    q.emplace(id[r], true);
    while(!q.empty()){
        pair<int, bool> u = q.front();
        q.pop();
        int v = u.first;
        if(v > MXC){
            flag[v - MXC] = u.second;
        }else{
            if(in[v][0]){
                if(in[v][0] > MXC){
                    q.emplace(in[v][0], u.second);
                }else {
                    q.emplace(in[v][0], fl[in[v][0]] & u.second);
                }
            }
            if(in[v][1]){
                if(in[v][1] > MXC){
                    q.emplace(in[v][1], u.second);
                }else {
                    q.emplace(in[v][1], fl[in[v][1]] & u.second);
                }
            }
        }
    }
}