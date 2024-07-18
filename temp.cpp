#include <bits/stdc++.h>
#define max(a,b) (a>b?a:b)
using namespace std;
int n,m;
unsigned int c[21][7],d[21][7],p[21][7];
unsigned long long maxlast[21];
long long ans=-1;
unordered_map<long long,long long>mp;
vector<pair<long long,long long>>v;
signed main(){

	static auto dfs = [](int day, long long vic, long long dmg, auto &&dfs){
		if(day>(n/2))[[unlikely]]{
			mp[dmg] = (mp[dmg] > vic) ? mp[dmg] : vic;
			// mp[dmg]=max(mp[dmg],vic);
			return;
		}
		for(int i=1;i<=m;i++){
			dfs(day+1,vic+p[day][i],dmg+c[day][i]-d[day][i], dfs);
		}
	};

	static auto dfs1 = [](int day, long long vic, long long dmg, auto &&dfs1){
		static auto find = [](int val){
			int l=0,r=v.size()-1,mid;
			while(l<r){
				mid=(l+r)>>1;
				if(v[mid].first==val)[[unlikely]]{
					return mid;
				}else if(v[mid].first>val){
					r=mid;
				}else{
					l=mid+1;
				}
			}
			return l;
		};
		if(day>n)[[unlikely]]{
			static auto tmp=find(-dmg);
			tmp=find(-dmg)
			if(v[tmp].first==-dmg)[[unlikely]]{
				// ans=max(ans,vic+v[tmp].second);
				ans = ans > vic+v[tmp].second ? ans : vic+v[tmp].second;
			}
			return;
		}
		for(int i=1;i<=m;i++){
			dfs1(day+1,vic+p[day][i],dmg+c[day][i]-d[day][i],dfs1);
		}
	};

	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>d[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>p[i][j];
		}
	}
	for(int i=n;i>0;i--){
		for(int j=1;j<=m;j++){
			maxlast[i]=max(maxlast[i],maxlast[i+1]+p[i][j]);
		}
	}
	dfs(1,0,0,dfs);
	for(auto i:mp){
		v.emplace_back(i);
	}
	sort(v.begin(),v.end());
	dfs1(n/2+1,0,0,dfs1);
	cout<<ans;
}