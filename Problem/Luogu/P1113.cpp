#include <bits/stdc++.h>
using namespace std;

const int N = 10000, Pre = 100;

void read(int&);

int main(){

	class Graph{
    	int head[N + 5], nxt[Pre * N + 5], to[Pre * N + 5], cnt;
    public:
    	void add_edge(int u, int v){
    		to[++cnt] = v;
    		nxt[cnt] = head[u];
    		head[u] = cnt;
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
    };

	class Work{
        int len{}, pre[Pre+5]{};
	public:

        Graph *graph{};
        int sum_pre{}, end_time{};
		
		Work(int id, int len, const int *pre, Graph *graph){
            this->len = len;
            this->graph = graph;
			sum_pre = 0;
			end_time = len;
			for(int i = 1; pre[i]!=0; i++){
				this->pre[i] = pre[i];
                graph -> add_edge(pre[i], id);
				sum_pre++;
			}
		}
        
        Work()= default;

        void update_end_time(int time){
        	end_time = max(end_time, len + time);
        }
    };

    static Graph graph;
	static Work work[N + 5];
	int n;

	read(n);
	for(int i = 1; i <= n; i++){
		static int id, len, pre[Pre+5];
		read(id), read(len);
		for(int j = 1, t = 1; t; j++){
			read(t);
			pre[j] = t;
		}
		work[i] = Work{id, len, pre, &graph};
	}

	int ans = work[1].end_time;

	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int u = q.front();
		q.pop();

        for(int i = graph.begin(u); i; i = graph.next(i)){
        	int v = graph.get(i);
        	work[v].sum_pre--;
        	work[v].update_end_time(work[u].end_time);
        	ans = max(ans, work[v].end_time);
        	if(work[v].sum_pre == 0){
        		q.push(v);
        	}
        }

	}

	printf("%d\n", ans);
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