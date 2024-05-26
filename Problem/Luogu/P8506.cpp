//
// Created by kibi on 22-9-4.
//
//
// Created by kibi on 22-9-4.
//
//Solved 0pts because of no '/n' in last line, fix it (60pts, same problem?)
//add c != EOF
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
        while(c != '\n' && c != EOF){
            if(!a && c != '#' && c != ' '){
                break;
            }else if(!a && c == '#'){
                a = true;
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
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
        if(f){
            ans++;
        }
    }
    printf("%d\n", ans);
}