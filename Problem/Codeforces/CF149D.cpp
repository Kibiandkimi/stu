#include <bits/stdc++.h>
using namespace std;

const int Mod = 1000000007, S = 700;

// void read(bool&);

int main(){
	
	class Work
	{
		int cnt, match[S+5], f[S+5][S+5][3][3];
		bool s[S+5];

		void read(){
			int c = getchar();
			while(c != '(' && c != ')'){
				c = getchar();
			}
			while(c == '(' || c == ')'){
				s[++cnt] = (c == '(');
				c = getchar();
			}
		}

		void pre(){
			static stack<int> st;
			for (int i = 1; i <= cnt; ++i)
			{
				if(s[i]){
					st.push(i);
				}else{
					match[st.top()] = i;
					match[i] = st.top();
					st.pop();
				}
			}
		}

		void dfs(int l, int r){
			if(l + 1 == r){
				f[l][r][0][1] = f[l][r][0][2] = f[l][r][1][0] = f[l][r][2][0] = 1;
			}else if(match[l] == r){
				
				dfs(l+1, r-1);
				for(int i = 0; i <= 2; i++){
					for(int j = 0; j <= 2; j++){
						if(j != 1){
							f[l][r][0][1] = (f[l][r][0][1] + f[l+1][r-1][i][j]) % Mod;
						}
						if(j != 2){
							f[l][r][0][2] = (f[l][r][0][2] + f[l+1][r-1][i][j]) % Mod;
						}
						if(i != 1){
							f[l][r][1][0] = (f[l][r][1][0] + f[l+1][r-1][i][j]) % Mod;
						}
						if(i != 2){
							f[l][r][2][0] = (f[l][r][2][0] + f[l+1][r-1][i][j]) % Mod;
						}
					}
				}

			}else{
				dfs(l, match[l]);
				dfs(match[l]+1, r);
				for(int i = 0; i <= 2; i++){
					for(int j = 0; j <= 2; j++){
						for(int p = 0; p <= 2; p++){
							for(int q = 0; q <= 2; q++){
								if (j==1&&p==1 || j==2&&p==2){
									continue;
								}
								int &raw = f[l][r][i][q], 
								_l = f[l][match[l]][i][j], 
								_r = f[match[l]+1][r][p][q];
								raw = (int)((raw + (long long)_l * _r % Mod) % Mod);

							}
						}
					}
				}
			}
		}

		int get_res(){
			int ans = 0;
			for(int i = 0; i <= 2; i++){
				for(int j = 0; j <= 2; j++){
					ans = (ans + f[1][cnt][i][j]) % Mod;
				}
			}
			return ans;
		}
	public:
		
		int start(){
			read();
			pre();
			dfs(1, cnt);
			return get_res();
		}
		
	};

	static Work work;

	int ans = work.start();

	printf("%d\n", ans);

}