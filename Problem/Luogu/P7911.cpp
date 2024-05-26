#include <bits/stdc++.h>
using namespace std;
struct node{
    int a, b, c, d, e,id;
};
int a,b,c,d,e;
int n, s;
node ap[1005];
bool check1(char *p){
    bool ttt = false;
    bool f = false;
    int tnum = 0;
    int ds = 0;
    for(int i = 0; i <= 25&&p[i]!=0; i++){
        if(p[i]>='0'&&p[i]<='9'){
            ttt = true;
            tnum = tnum*10+p[i]-'0';
            if((tnum>255&&(!f))||tnum>65535){
            //  printf("err1\n%d\n", tnum);
                return false;
            }
        }else if(p[i] == '.'){
            ds++;
            tnum = 0;
            if(ds>3){
                //printf("err2\n");
                return false;
            }
            if(!ttt){
                return false;
            }
            ttt = false;
            if(f){
                return false;
            }
        }else if(p[i] == ':'){
            tnum = 0;
            if(f){
            //  printf("err3\n");
                return false;
            }
            f = true;
            if(!ttt){
                return false;
            }
            ttt = false;
        }
    }
    if (!ttt){
        return false;
    }
    if (f == false||ds!=3){
    //  printf("err5\n");
        return false;
    }
    bool fl = false;
    for(int i = 0; i<25&&p[i+2]!=0; i++){
        if((p[i]=='.'||p[i]==':')&&(p[i+2]!='.'&&p[i+2]!=':')&&p[i+1]=='0'){
        //  printf("err6\n");
            return false;
        }
        
    }
    if(p[1]!='.' && p[0]=='0'){
    //  printf("err7\n");
        return false;
    }
    if(p[0]=='.'||p[0]==':'){
        return false;
    } 
    return true;
}
int check2(char *p){
//  int a = 0, b = 0, c = 0, d = 0, e = 0;
    a = b = c = d = e = 0;
    int t = 1;
    for(int i = 0; i<25&&p[i] != 0; i++){
        if(p[i]>='0'&&p[i]<='9'){
            switch(t){
                case 1: a = a*10+p[i]-'0';break;
                case 2: b = b*10+p[i]-'0';break;
                case 3: c = c*10+p[i]-'0';break;
                case 4: d = d*10+p[i]-'0';break;
                case 5: e = e*10+p[i]-'0';break;
            }
        }else{
            t++;
        }
    }
    for(int i = 1; i <= s; i++){
        if(a==ap[i].a&&b==ap[i].b&&c==ap[i].c&&d==ap[i].d&&e==ap[i].e){
            return ap[i].id;
        }       
    }
    return false;
}
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        char op[6];
        scanf("%s", op);
        if(op[0]=='S'){
            char ip[25] = "";
            scanf("%s", ip);
            if(!check1(ip)){
                printf("ERR\n");    
            }else if(check2(ip)){
                printf("FAIL\n");
            }else{
                printf("OK\n");
                ap[++s] = node({a, b, c, d, e,i});  
            }
        }else{
            int id;
            char ip[25] = "";
            scanf("%s", ip);
            if(!check1(ip)){
                printf("ERR\n");
            }else if(!(id = check2(ip))){
                printf("FAIL\n");
            }else{
                printf("%d\n", id);
            }

        }

    }
    return 0;
}