//
// Created by kibi on 2022/9/4.
//
#include <bits/stdc++.h>
using namespace std;
int n, T;
long long a[1000005];
bool ans[1000005];

//bool getType(int c);
void read(int &x);
void read(long long &x);

bool f1(deque<long long> &q1, deque<long long> &q2, int pos);
int main(){
    read(T);
    while(T--){
        read(n);
        int n2 = 2 * n;
        for(int i = 1; i <= n2; i++){
            read(a[i]);
        }
        int pl = 0, pr = 0;
        for(int i = 2; i < n2; i++){
            if(a[i]==a[1]){
                pl = i;
            }
            if(a[i]==a[n2]){
                pr = i;
            }
            if(pl&&pr){
                break;
            }
        }
        if(a[1] == a[n2]){
            bool flag = true;
            for(int i = 1; i <= n2; i++){
                if(a[i] != a[n2 +1-i]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                for(int i = 1; i <= n2; i++) {
                    printf("L");
                }
            }else{
                printf("-1");
            }
            printf("\n");
            continue;
        }
        deque<long long> q1, q2;
        ans[1] = false;
        ans[n2] = false;
        for(int i = 2; i < pl; i++){
            q1.push_back(a[i]);
        }
        for(int i = pl+1; i <= n2; i++){
            q2.push_front(a[i]);
        }
        //        front...back|back...front
        int pos = 2;
        bool flag;
        flag = f1(q1, q2, pos);
        if(flag){
            for(int i = 1; i <= n2; i++){
                ans[i]?printf("R"):printf("L");
            }
        }else{
            q1.clear(), q2.clear();
            ans[1] = true;
            ans[n2] = false;
            for(int i = 1; i < pr; i++){
                q1.push_back(a[i]);
            }
            for(int i = pr+1; i < n2; i++){
                q2.push_front(a[i]);
            }
            pos = 2;
            flag = f1(q1, q2, pos);
            if(flag){
                for(int i = 1; i <= n2; i++){
                    ans[i]?printf("R"):printf("L");
                }
            }else{
                printf("-1");
            }
        }
        printf("\n");
    }
}
bool f1(deque<long long> &q1, deque<long long> &q2, int pos) {
    bool flag = true;
    while(!(q1.empty()&&q2.empty())){
        if(q1.size()>=2 && q1.front() == q1.back()){
            q1.pop_front();
            q1.pop_back();
            ans[pos] = false;
            ans[2*n-pos+1] = false;
            //                pos++;
        }else if(!q1.empty()&&!q2.empty() && q1.front() == q2.back()){
            q1.pop_front();
            q2.pop_back();
            ans[pos] = false;
            ans[2*n-pos+1] = true;
        }else if(!q1.empty()&&!q2.empty() && q2.front() == q1.back()){
            q2.pop_front(), q1.pop_back();
            ans[pos] = true;
            ans[2*n-pos+1] = false;
        }else if(q2.size()>=2 && q2.front() == q2.back()){
            q2.pop_front(), q2.pop_back();
            ans[pos] = true;
            ans[2*n-pos+1] = true;
        }else{
            flag = false;
            break;
        }
        pos++;
    }
    return flag;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
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

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
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