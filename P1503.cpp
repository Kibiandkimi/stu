//
// Created by kibi on 22-8-9.
//
//AVL在上(28pts) fhq-treap在下(100pts)

/*
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, root = 1;
int val[50005], son[50005][2], fa[50005], dep[50005];
bool atk[50005];
stack<int> s;

int new_node(int x){
    val[++cnt] = x;
//    siz[cnt] = 1;
    return cnt;
}

//void update(int x){
//    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
//}

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

int LL_rotate(int pos){ //r_rotate
    int pa = fa[pos];
    int ch = son[pos][0];
    if(son[ch][1]){
        fa[son[ch][1]] = pos;
    }
    son[pos][0] = son[pos][1];
    update_dep(pos);
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
    update_dep(ch);
    return ch;

}

int RR_rotate(int pos){ //L_rotate
    int pa = fa[pos], ch = son[pos][1];
    if(son[ch][0]){
        fa[son[ch][0]] = pos;
    }
    son[pos][1] = son[pos][0];
    update_dep(pos);
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
    update_dep(ch);
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

int get_bala(int pos){
    if(!pos){
        return 0;
    }else{
        return dep[son[pos][0]] - dep[son[pos][1]];
    }
}

int re_balance(int pos){
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

void tr_insert(int x, int &pos){
    if(!root){
        root = new_node(x);
    }else if(x == val[pos]){
        return ;
    }else if(x < val[pos]){
        if(!son[pos][0]){
            son[pos][0] = new_node(x);
            dep[son[pos][0]] = 1;
//            dep[son[pos][0]] = dep[pos]+1;
            fa[son[pos][0]] = pos;
        }else{
            tr_insert(x, son[pos][0]);
        }
    }else{
        if(!son[pos][1]){
            son[pos][1] = new_node(x);
            dep[son[pos][1]] = 1;
//            dep[son[pos][1]] = dep[pos]+1;
            fa[son[pos][1]] = pos;
        }else{
            tr_insert(x, son[pos][1]);
        }
    }
    update_dep(pos);
    pos = re_balance(pos);
}

int delete_min(int &x){
    if(!son[x][0]){
        int u = x;
        x = son[x][1];
        return u;
    }else{
        int u = delete_min(son[x][0]);
//        siz[x] -= 1;
        return u;
    }
}

void tr_delete(int x, int &pos){
//    siz[pos]--;
    if(val[pos] == x){
        if(son[pos][1] && son[pos][0]){
            pos = delete_min(son[pos][1]);
        }else{
            pos = son[pos][0]+son[pos][1];
        }
    }else if(val[pos] > x){
        tr_delete(x, son[pos][0]);
    }else{
        tr_delete(x, son[pos][1]);
    }
    update_dep(pos);
    pos = re_balance(pos);
}

//int query_rnk(int v, int pos){
//    if(!pos){
//        return -1;
//    }
//    if(val[pos] == v){
//        return siz[son[pos][0]] + 1;
//    }else if(val[pos] > v){
//        return query_rnk(v, son[pos][0]);
//    }else if(val[pos] < v){
//        return query_rnk(v, son[pos][1]);
//    }
//    return -1;
//}

//int query_kth(int k, int pos){
//    if(siz[son[pos][0]] >= k){
//        return query_kth(k, son[pos][0]);
//    }else if(siz[son[pos][0]] + 1 == k){
//        return pos;
//    }else{
//        return query_kth(k - siz[son[pos][0]], son[pos][1]);
//    }
//}

int query_ans(int x, int pos){
//    if(query_rnk(x, pos) != -1){
//        return 0;
//    }
    if(atk[x]){
        return 0;
    }
    int l, r;
    while(true){
        if(val[pos] == x){
            return 0;
        }else if(val[pos] > x){
            r = val[pos];
            if(!son[pos][0]){
                return r-l-1;
            }else{
                pos = son[pos][0];
            }
        }else{
            l = val[pos];
            if(!son[pos][1]){
                return r-l-1;
            }else{
                pos = son[pos][1];
            }
        }
    }

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
            atk[x] = true;
            tr_insert(x, root);
        }else if(opt[0] == 'R'){
            tr_delete(s.top(), root);
            atk[s.top()] = false;
            s.pop();
        }else{
            int x;
            scanf("%d", &x);
//            int rnk = query_rnk(x, root);
//            int l = query_kth(rnk-1, root), r = query_rnk(rnk+1, root);
            printf("%d\n", query_ans(x, root));
        }
    }
}
 */

//fhq-treap
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, root;
int val[50005], siz[50005], rnk[50005], son[50005][2];
bool atk[50005];
stack<int> s;

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

int new_node(int x){
    val[++cnt] = x;
    siz[cnt] = 1;
    rnk[cnt] = rand();
    return cnt;
}

void split(int &x, int &y, int k, int pos){
    if(!pos){
        x = y = 0;
    }else {
        if (val[pos] <= k) {
            x = pos;
            split(son[pos][1], y, k, son[pos][1]);
            //            update(x);
        }else{
            y = pos;
            split(x, son[pos][0], k, son[pos][0]);
            //            update(y);
        }
        update(pos);
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else if(rnk[x] < rnk[y]){
        son[x][1] = merge(son[x][1], y);
        update(x);
        return x;
    }else{
        son[y][0] = merge(x, son[y][0]);
        update(y);
        return y;
    }
}

//int tr_insert(int x, int pos){
//
//}

int query_rnk(int k, int pos){
    while(true){
        if(siz[son[pos][0]] >= k){
            pos = son[pos][0];
        }else if(siz[son[pos][0]]+1 == k){
            return val[pos];
        }else{
            k -= siz[son[pos][0]]+1;
            pos = son[pos][1];
        }
    }
}

int query_ans(int x){
    if(atk[x]){
        return 0;
    }

    int fl, fr;
    int l, r;

    split(l, r, x-1, root);
    fl = query_rnk(siz[l], l);
    root = merge(l, r);

    split(l, r, x, root);
    fr = query_rnk(1, r);
    root = merge(l, r);

    return fr-fl-1;
}

int main(){
    srand((unsigned)time(nullptr));
    scanf("%d %d", &n, &m);
    root = new_node(0);
    root = merge(root, new_node(n+1));
    while(m--){
        char opt[5];
        scanf("%s", opt);
        char o = opt[0];
        if(o == 'D'){
            int x;
            scanf("%d", &x);
            s.push(x);
            atk[x] = true;
            int l, r;
            split(l, r, x, root);
            root = merge(merge(l, new_node(x)), r);
        }else if(o == 'R'){
            atk[s.top()] = false;
            int l, r, z;
            split(l, z, s.top(), root);
            split(l, r, s.top()-1, l);
            r = merge(son[r][0], son[r][1]);
            root = merge(merge(l, r), z);
            s.pop();
        }else if(o == 'Q'){
            int x;
            scanf("%d", &x);
            printf("%d\n", query_ans(x));
        }
    }
}