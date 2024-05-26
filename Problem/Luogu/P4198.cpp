#include <bits/stdc++.h>
using namespace std;

const int N = 100000, M = 100000;

void read(int&);

int main(){

	class SegTree{

		class Node{
		public:
			double mx;
			int len;
			Node():mx(0), len(0){}
		};

		int l[4 * N + 5], r[4 * N + 5], ls[4 * N + 5], rs[4 * N + 5];
		Node node[4 * N + 5];
		double *data;

		void build(int u, int l, int r){
			this -> l[u] = l, this -> r[u] = r;
			if(l == r){
				return;
			}
			int mid = (l+r)/2;
			ls[u] = u*2, rs[u] = u*2+1;
			build(ls[u], l, mid);
			build(rs[u], mid+1, r);
		}

		void update(int u){
			// update mx
			node[u].mx = max(node[ls[u]].mx, node[rs[u]].mx);

			// update len
			int raw_u = u;
			int res = node[ls[u]].len, l = this -> l[rs[u]], r = this -> r[rs[u]];
			double lx = node[ls[u]].mx;
			u = u*2+1;
			while(true){
				if(node[u].mx <= lx){
					break;
				}else if(data[l] > lx){
					res += node[u].len;
					break;
				}else if(l == r){
					res += (data[l] > lx) ? 1 : 0;
					break;
				}
				if(node[ls[u]].mx <= lx){
					l = this -> l[rs[u]];
					u = rs[u];
				}else{
					res += node[u].len - node[ls[u]].len;
					r = this -> r[ls[u]];
					u = ls[u];
				}
			}
			node[raw_u].len = res;
		}

	public:

		SegTree(int n, double *data):data(data){
			build(1, 1, n);
		}

		void change(int pos, double v){
			int l = this -> l[1], r = this -> r[1], u = 1;
			while(l != r){
				int mid = (l+r)/2;
				if(pos <= mid){
					r = mid;
					u = u*2;
				}else{
					l = mid+1;
					u = u*2+1;
				}
			}

			node[u].mx = v;
			node[u].len = 1;

			while(u != 1){
				u >>= 1;
				update(u);
			}
		}

		int _query(){
			return node[1].len;
		}

	};

	int n, m;
	read(n), read(m);

	static double data[M + 5];

	static SegTree tree(n, data);

	for(int i = 1; i <= m; i++){
		int y, x;
		read(x), read(y);
		double slope = (double)y/x;
		data[x] = slope;
		tree.change(x, slope);
		printf("%d\n", tree._query());
	}
}

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