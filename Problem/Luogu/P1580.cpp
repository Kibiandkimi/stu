//
// Created by kibi on 23-7-5.
//
// TODO not done yet
// maybe got hole line and judge

#include <bits/stdc++.h>
using namespace std;
int name[1005];
int pd();
int main(){
    int c;
    c = getchar();
    while(c != ':'){
        c = getchar();
    }
    while(c != '@'){
        c = getchar();
    }
    while(c != ' '){
        c = getchar();
    }
    c = getchar();
    while(c != ' '){
        c = getchar();
    }
    c = getchar();
    while(c != ' '){
        static int i = 1;
        name[i++] = c;
        c = getchar();
    }
    while(true){

    }
}

int pd(){
    int c;
    c = getchar();
    while(c < 'a' || 'z' < c){
        c = getchar();
    }
    bool flag = true;
    while(c != ':'){
        static int i = 1;
        if(name[i++] != c){
            flag = false;
        }
        c = getchar();
    }
    if(flag){
        return 1;
    }
    while(c != '@'){
        c = getchar();
    }
    while(c != ' '){
        c = getchar();
    }
    c = getchar();
    while(c != ' '){
        c = getchar();
    }
    c = getchar();
    while(c != ' '){
        static int i = 1;
        if(name[i++] != c){
            return 2;
        }
        c = getchar();
    }
    return 3;
}