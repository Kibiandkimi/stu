#include <bits/stdc++.h>
using namespace std;
int n;
struct node{
    int s;
    bool type;
    int nxt;
    int pre;
    int l,r;
    int snxt,spre;
    int sl,sr;
}a[200005];
int tp = 1, s = 1, head = 1;
int main(){
    scanf("%d", &n);
    scanf("%d", &a[1].type);
    a[1].s = 1;
    a[1].snxt = 0;
    a[1].spre = 0;
    a[1].nxt = 0;
    a[1].pre = 0;
    a[1].l = 1;
    a[1].r = 1;
    a[1].sl = 1;
    a[1].sr = 1;
    for(int i = 2; i <= n; i++){
        bool t;
        scanf("%d", &t);
        if(t == a[s].type){
            a[s].s++;
        }else{
            a[++s].type = t;
            a[s].s = 1;
            a[s].pre = s-1;
            a[s].nxt = 0;
            a[s].l = i;
            a[s-1].nxt = s;
            a[s].spre = a[s].snxt = 0;
            a[s].sl = a[s].sr = s;
        }
    }
    while(true){
        int li[200005];
        int sum = 0;
        int t = -1;
        for(int i = head; i != 0; i = a[i].nxt){
            if(t != a[i].type){
                t = a[i].type;
                a[i].s--;
                if(a[i].s<0){
                    return 0;
                }
                li[++sum] = a[i].l++;
                if(a[i].s==0){
                    if(a[i].spre!=0){
                        if(a[i].pre==0){
                            head = a[i].spre;
                        }
                        a[a[i].spre].nxt = a[a[i].sr].nxt;
                        a[a[i].snxt].snxt = a[i].snxt;
                        
                    }else if(a[i].pre==0){
                        if(a[i].snxt==0){
                            head = a[i].nxt;
                            a[a[i].nxt].pre = 0;
                        }else{
                            head = a[i].snxt;
                            a[a[i].snxt].pre = 0;
                            a[a[i].snxt].sl = a[i].snxt;
                            a[a[a[i].snxt].sr].sl = a[i].snxt;
                            a[a[i].nxt].pre = a[i].snxt;
                        }
                        // a[a[i].nxt].pre = 0;
                        // a[a[i].snxt].spre = 0;
                    }else if(a[i].nxt==0){
                        a[a[i].pre].nxt = 0;
                    }else if(a[i].snxt == 0){
                        // a[a[i].pre].nxt = a[i].nxt;
                        // a[a[i].nxt].pre = a[i].pre;

                        a[a[a[i].pre].sr].snxt = a[i].nxt;
                        a[a[a[i].nxt].sl].spre = a[i].pre;
                        a[a[a[i].pre].sl].sr = a[a[i].nxt].sr;
                        a[a[a[i].nxt].sr].sl = a[a[i].pre].sl;
                        a[a[a[i].pre].sl].nxt = a[a[i].nxt].nxt;
                        a[a[a[i].nxt].sr].pre = a[a[i].pre].pre;
                    }else{
                        a[a[a[i].pre].sl].nxt = a[i].snxt;
                        a[a[a[i].nxt].sr].pre = a[i].snxt;
                        a[a[i].snxt].pre = a[a[i].pre].sl;
                        a[a[i].snxt].spre = 0;
                        a[a[i].snxt].pre = a[i].pre;
                        a[a[i].snxt].sl = a[a[a[i].snxt].sr].sl = a[i].snxt;
                    }
                }
            }
        }
        if(sum==0){
            break;
        }
        for(int i = 1; i <= sum; i++){
            printf("%d ", li[i]);
        }
        printf("\n");
    }
    return 0;
}
