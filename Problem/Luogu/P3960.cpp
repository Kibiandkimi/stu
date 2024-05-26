//
// Created by kibi on 23-8-9.
//

// TODO 树状数组写法
// not understand

/*
#include <bits/stdc++.h>
using namespace std;

int main(){

	const int Q = 300000;

	class Tools{
	public:
		static void read(int &x);
	};

	class Question{
	public:
		int id, x, y, ans;
		static bool cmp(Question a, Question b){
			return a.x == b.x ? a.id < b.id : a.x < b.x;
		}
	};

	class SegTree{
		int data[4 * Q + 5]{};
		const int n;
	public:

		explicit SegTree(int n):n(n){}

		void add(int x, int v = 1){
			while(x <= n){

			}
		}
	};

    auto read = Tools::read;

	int n, m, q;
	static Question question[Q + 5];

	read(n), read(m), read(q);

	for(int i = 1; i <= q; i++){
		int x, y;
		Tools::read(x), Tools::read(y);
		question[i] = {i, x, y};
	}

	sort(question+1, question+1+q, Question::cmp);



}

 */

// TODO 平衡树写法
// a lot problem
// not finish

/*

#include <bits/stdc++.h>
using namespace std;

int main(){

    const int FhqTreapSize = 300000;

    class Tools{
    public:
        void read(int &x){
            int s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c){
                if(c == '-'){
                    w = -1;
                }
                c = getchar();
            }
            while('0' <= c && c <= '9'){
                s = s * 10 + c - '0';
                c = getchar();
            }
            x = s * w;
        }
    };

    class FhqTreap{
        mt19937 rnd(random_device{}());

        class Node{
            int siz, ls, rs, l, r;
            unsigned int rnk;
        };

        Node node[FhqTreapSize + 5];

        int cnt;

        void update(int x){
            node[x].siz = node[node[x].ls].siz + node[node[x].rs].siz + 1;
        }

    public:
        int newNode(int l, int r){
            cnt++;
            node[cnt] = {r-l+1, 0, 0, l, r, rnd()};
            return cnt;
        }

        void split(int &x, int &y, const int k, int pos){
            if(!pos){
                x = y = 0;
                return;
            }

            if(node[node[pos].ls].siz < k){
                x = pos;
                split(node[pos].rs, y, k-(node[node[pos].ls].siz+1), node[pos].rs);
            }else{
                y = pos;
                split(x, node[pos].ls, k, node[pos].ls);
            }

            update(pos);
        }

        void split_last(int &x, int &y, int pos){
            if(!pos){
                x = y = 0;
                return;
            }
            if(node[pos].rs){
                x = pos;
                split_last(node[pos].rs, y, node[pos].rs);
            }else{
                x = node[pos].ls;
                y = pos;
            }
            update(pos);
        }

        int merge(int x, int y){
            if(!(x&&y)){
                return x+y;
            }
            if(rnk[x] < rnk[y]){
                node[x].rs = merge(node[x].rs, y);
                update(x);
                return x;
            }else{
                node[y].ls = merge(x, node[y].ls);
                update(y);
                return y;
            }
        }

        void del(int x, int k, int &res, int &del){
            if(node[x].siz == 1){
                res = 0;
                del = x;
                return;
            }
            int raw_cnt = cnt;
            if(k > node[x].l){
                node[++cnt] = {k-node[x].l, 0, 0, node[x].l, k-1, rnk()};
            }
            if(k < node[x].r){
                node[++cnt] = {node[x].r-k, 0, 0, k+1, node[x].r, rnk()};
            }
            if(cnt - raw_cnt > 1){
                res = merge(cnt-1, cnt);
            }else{
                res = cnt;
            }
            node[x] = {1, 0, 0, k, k, rnk()}; // break of fhq
            del = x;
        }

        void get(int x){
            return node[x].l;
        }
    };

    auto read = Tools::read;

    int n, m, q;

    read(n), read(m), read(q);

    static FhqTreap treap;

    int rt = 0;
    int cnt = 1;

    for(int i = 1; i <= n; i++){
        rt = treap.merge(rt, treap.newNode(cnt, cnt+m-1));
        cnt += m-1;
    }

    rt = treap.merge(rt, treap.newNode(cnt, cnt+n));

    cnt += n;

    for(int i = 1; i <= q; i++){
        int x, y;
        read(x), read(y);
        treap.split()

    }

}

 * */