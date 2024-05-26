//
// Created by kibi on 22-9-4.
//
#include <bits/stdc++.h>
using namespace std;
int n;

int main(){
    scanf("%d", &n);
    getchar();
    bool a, b, f;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        a = false, b = false, f = false;
        int c = getchar();
        while(c != '\n'){
            if(!a && c != '#' && c != ' '){
                break;
            }
            if(!a && c == '#'){
                a = true;
                //                continue;
            }else if(!a){

            }else if(!b && c != ' '){
                break;
            }else if(!b){
                b = true;
            }else if(c != ' '){
                f = true;
                //                break;
            }
            c = getchar();
        }
        if(n != i) {
            while (c != '\n') {
                c = getchar();
            }
        }
        if(f){
            ans++;
        }
    }
    printf("%d\n", ans);
}