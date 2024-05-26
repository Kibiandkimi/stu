//
// Created by kibi on 2021/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
string a;
int sstep(){
    bool t = a[0] != '1';
    int step = 0;
    for (int i = 0; i < n; i++) {
        if (t == (a[i] == '1')) {
            continue;
        } else {
            step += n - i;
            t = a[i] == '1';
        }
    }
    return step;
}
int o1(int v) {
    for (int i = 1; i <= v; i++) {
        //        bool flag = false;
        int ii = -1;
        for (int j = n - 1; j >= 0; j--) {
            if (a[j] == '0') {
                a[j] = '1';
                ii = j + 1;
                //                flag = true;
                break;
            }
        }
    }
    return 0;
}
int o2(int v) {
    for (int i = 1; i <= v; i++) {
        //        bool flag = false;
        int ii = 0;
        for (int j = n - 1; j > 0; j--) {
            if (a[j] == '1') {
                a[j] = '0';
                ii = j + 1;
                //                flag = true;
                break;
            }
        }
    }
    return 0;
}
int f(int v) {
    if (v > 0) {
        o1(v);
    } else {
        o2(fabs(v));
    }
    return 0;
}
int main() {
    cin >> n >> m;
    cin >> a;
    for (int i = 1; i <= m; i++) {
        int t;
        scanf("%d", &t);
        f(t);
        printf("%d\n" ,sstep());
    }
}


//

//
// Created by kibi on 2021/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,step;
string s;
stack<int> a,b;
int main(){
    cin >> n >> m;
    cin >> s;
    char ls = '2';
    for(int i = 0; i < s.size(); i++){
        if(s[i] != ls){
            a.push(1);
            ls = s[i]-'0';
            b.push(ls);
            step += s.size()-i;
        }else{
            int t = a.top();
            a.pop();
            a.push(t+1);
        }
    }
    for(int i = 1; i <= m; i++){
        int o;
        scanf("%d", &o);
        bool t = o>0;
        o = o > 0 ? o : -o;
        while(o--) {
            if (t) {
                if (b.top() == 1) {
                    int t1 = a.top();
                    a.pop();
                    int t2 = a.top();
                    a.pop();
                    t2--;
                    t1++;
                    if (t2) {
                        a.push(t2);
                        a.push(t1);
                        step++;
                    } else {
                        t2 = a.top();
                        a.pop();
                        b.pop();
                        b.pop();
                        step -= t1 * 2 - 1;
                        a.push(t1 + t2);
                    }

                } else {
                    int t1 = a.top();
                    a.pop();
                    t1--;
                    if (t1) {
                        a.push(t1);
                        a.push(1);
                        b.push(1);
                        step++;
                    } else {
                        b.pop();
                        t1 = a.top();
                        a.pop();
                        a.push(t1 + 1);
                        //                        b.push(1);
                        step--;
                    }
                }
            } else {
                if (b.top() == 0) {
                    int t1 = a.top();
                    a.pop();
                    int t2 = a.top();
                    a.pop();
                    t2--;
                    t1++;
                    if (t2) {
                        a.push(t2);
                        a.push(t1);
                        step++;
                    } else {
                        b.pop();
                        b.pop();
                        t2 = a.top();
                        a.pop();
                        step -= t1 * 2 - 1;
                        a.push(t2 + t1);
                    }
                } else {
                    int t1 = a.top();
                    a.pop();
                    t1--;
                    if (t1) {
                        a.push(t1);
                        a.push(1);
                        b.push(0);
                        step++;
                    } else {
                        t1 = a.top();
                        t1++;
                        a.pop();
                        b.pop();
                        a.push(t1);
                    }
                }
            }
        }
        printf("%d\n", step);
    }
}