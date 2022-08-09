//AVL
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, root = 1;
int val[50005], siz[50005], son[50005][2], fa[50005], dep[50005];
stack<int> s;

int new_node(int x){
    val[++cnt] = x;
    siz[cnt] = 1;
    return cnt;
}

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

int LL_rotate(int pos){ //r_rotate
    int pa = fa[pos];
    int ch = son[pos][0];
    if(son[ch][1]){
        fa[son[ch][1]] = pos;
    }
    son[pos][0] = son[pos][1];
    update(pos);
    son[ch][1] = pos;
    fa[ch] = pa;
    if(pa){
        if(son[pa][0] == pos){
            son[pa][0] = ch;
        }else{
            son[pa][1] = ch;
        }
    }
    fa[pos] = ch;
    update(ch);
    return ch;

}

int RR_rotate(int pos){ //L_rotate
    int pa = fa[pos], ch = son[pos][1];
    if(son[ch][0]){
        fa[son[ch][0]] = pos;
    }
    son[pos][1] = son[pos][0];
    update(pos);
    son[ch][0] = pos;
    fa[ch] = pa;
    if(pa){
        if(son[pa][0] == pos){
            son[pa][0] = ch;
        }else{
            son[pa][1] = ch;
        }
    }
    fa[pos] = ch;
    update(ch);
    return ch;
}

int LR_rotate(int pos){
    RR_rotate(son[pos][0]);
    return LL_rotate(pos);
}

int RL_rotate(int pos){
    LL_rotate(son[pos][1]);
    return RR_rotate(pos);
}

int get_dep(int pos){
    if(!pos){
        return 0;
    }else{
        return dep[pos];
    }
}

void update_dep(int pos){
    if(!pos){
        return;
    }else{
        int dep_l = get_dep(son[pos][0]);
        int dep_r = get_dep(son[pos][1]);
        dep[pos] = max(dep_l, dep_r) + 1;
    }
}

int get_bala(int pos){
    if(!pos){
        return 0;
    }else{
        return dep[son[pos][0]] = dep[son[pos][1]];
    }
}

int re_bala(int pos){
    int fac = get_bala(pos);
    if(fac > 1 && get_bala(son[pos][0])){
        return LL_rotate(pos);
    }else if(fac > 1 && get_bala(son[pos][0]) <= 0){
        return LR_rotate(pos);
    }else if(fac < -1 && get_bala(son[pos][1]) <= 0){
        return RR_rotate(pos);
    }else if(fac < -1 && get_bala(son[pos][1]) > 0){
        return RL_rotate(pos);
    }else{
        return pos;
    }
}

void tr_insert(int x, int pos){
    if(!root){
        root = new_node(x);
    }else if(x == val[pos]){
        return ;
    }else if(x < val[pos]){
        if(!son[pos][0]){
            son[pos][0] = new_node(x);
//            dep[son[pos][0]] = dep[pos]+1;
            fa[son[pos][0]] = pos;
        }else{
            tr_insert(x, son[pos][0]);
        }
    }else{
        if(!son[pos][1]){
            son[pos][1] = new_node(x);
//            dep[son[pos][1]] = dep[pos]+1;
            fa[son[pos][1]] = pos;
        }else{
            tr_insert(x, son[pos][1]);
        }
    }
    re_bala(pos);
}

void tr_delete(int x, int pos){

}

int main(){
    scanf("%d %d", &n, &m);
//    tr_insert(0, root);
    new_node(0);
    tr_insert(n+1, root);
    while(m--){
        char opt[2];
        scanf("%s", opt);
        if(opt[0] == 'D'){
            int x;
            scanf("%d", &x);
            s.push(x);
            tr_insert(x, root);
        }
    }
}