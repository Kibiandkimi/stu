#include <bits/stdc++.h>
using namespace std;

const int N = 10000, M = 500000;

void read(int&);

int main(){
	
	class Graph{
		int head[N+5], nxt[M+5], to[M+5], w[M+5], cnt;

	public:
		void add_edge(int u, int v, int w){
			to[++cnt] = v;
			nxt[cnt] = head[u];
			head[u] = cnt;
			this->w[cnt] = w;
		}

		int begin(int x){
			return head[x];
		}
		int next(int x){
			return nxt[x];
		}
		int get(int x){
			return to[x];
		}
		int get_w(int x){
			return w[x];
		}
	};

	static Graph graph;

	int n, m, s;
	read(n), read(m), read(s);

	for(int i = 1; i <= m; i++){
		static int u, v, w;
		read(u), read(v), read(w);
		graph.add_edge(u, v, w);
	}

	static int f[N+5];
	static bool vis[N+5];

	for(int i = 1; i <= n; i++){
		f[i] = 2147483647;
	}

	// TODO why can not memset
	// memset(f, 0x7fffffff, sizeof f); 
	f[s] = 0;

	queue<int> q;
	q.push(s);
	vis[s] = true;

	while(!q.empty()){
		static int u;
		u = q.front();
		q.pop();
		vis[u] = false;
		for(int i = graph.begin(u); i; i = graph.next(i)){
			static int v, w;
			v = graph.get(i), w = graph.get_w(i);
			if(f[v] > f[u] + w){
				f[v] = f[u]+w;
				if(!vis[v]){
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}

	for(int i = 1; i <= n; i++){
		printf("%d ", f[i]);
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