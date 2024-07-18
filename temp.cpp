// xxhash64.hpp

#ifndef XXHASH64_HPP
#define XXHASH64_HPP

#include<bits/stdc++.h>
#include <cstdint>

namespace xxhash {


    const uint64_t PRIME64_1 = 11400714785074694791ULL;
    const uint64_t PRIME64_2 = 14029467366897019727ULL;
    const uint64_t PRIME64_3 = 1609587929392839161ULL;
    const uint64_t PRIME64_4 = 9650029242287828579ULL;
    const uint64_t PRIME64_5 = 2870177450012600261ULL;

    inline uint64_t XXH64_rotl(uint64_t x, int32_t r) {
        return (x << r) | (x >> (64 - r));
    }

    inline uint64_t XXH64_readLE(const uint8_t* p) {
        uint64_t val;
        memcpy(&val, p, sizeof(uint64_t));
        return val;
    }

    inline uint64_t XXH64_round(uint64_t acc, uint64_t input) {
        acc += input * PRIME64_2;
        acc = XXH64_rotl(acc, 31);
        acc *= PRIME64_1;
        return acc;
    }

    inline uint64_t XXH64_mergeRound(uint64_t acc, uint64_t val) {
        val ^= acc;
        val *= PRIME64_1;
        val += PRIME64_4;
        return val;
    }
    // 定义 XXH64 的实现
    uint64_t XXH64(const void* input, size_t length, uint64_t seed = 0) {

        const uint8_t* p = reinterpret_cast<const uint8_t*>(input);
        const uint8_t* const end = p + length;
        uint64_t h64;

        if (length >= 32) {
            const uint8_t* const limit = end - 32;
            uint64_t v1 = seed + PRIME64_1 + PRIME64_2;
            uint64_t v2 = seed + PRIME64_2;
            uint64_t v3 = seed + 0;
            uint64_t v4 = seed - PRIME64_1;

            do {
                v1 = XXH64_round(v1, XXH64_readLE(p)); p += 8;
                v2 = XXH64_round(v2, XXH64_readLE(p)); p += 8;
                v3 = XXH64_round(v3, XXH64_readLE(p)); p += 8;
                v4 = XXH64_round(v4, XXH64_readLE(p)); p += 8;
            } while (p <= limit);

            h64 = XXH64_rotl(v1, 1) + XXH64_rotl(v2, 7) + XXH64_rotl(v3, 12) + XXH64_rotl(v4, 18);
            h64 = XXH64_mergeRound(h64, v1);
            h64 = XXH64_mergeRound(h64, v2);
            h64 = XXH64_mergeRound(h64, v3);
            h64 = XXH64_mergeRound(h64, v4);

        } else {
            h64  = seed + PRIME64_5;
        }

        h64 += static_cast<uint64_t>(length);

        while (p + 8 <= end) {
            uint64_t const k1 = XXH64_readLE(p);
            h64 ^= XXH64_round(0, k1);
            h64  = XXH64_rotl(h64, 27) * PRIME64_1 + PRIME64_4;
            p += 8;
        }

        if (p + 4 <= end) {
            h64 ^= static_cast<uint64_t>(XXH64_readLE(p)) * PRIME64_1;
            h64  = XXH64_rotl(h64, 23) * PRIME64_2 + PRIME64_3;
            p += 4;
        }

        while (p < end) {
            h64 ^= (*p) * PRIME64_5;
            h64  = XXH64_rotl(h64, 11) * PRIME64_1;
            p++;
        }

        h64 ^= h64 >> 33;
        h64 *= PRIME64_2;
        h64 ^= h64 >> 29;
        h64 *= PRIME64_3;
        h64 ^= h64 >> 32;

        return h64;
    }

// private:

} // namespace xxhash

#endif // XXHASH64_HPP


struct XXHash {
    size_t operator()(const long long& key) const {
        // 使用 xxhash 计算哈希值
        return xxhash::	XXH64(reinterpret_cast<const void*>(&key), sizeof(key), 0);
    }
};

#define max(a,b) (a>b?a:b)
using namespace std;
int n,m;
int c[25][10],d[25][10],p[25][10];
long long maxlast[25];
long long ans=-1;
unordered_map<long long,long long>mp;
vector<pair<long long,long long>>v;
// int find(int val){
// 	int l=0,r=v.size()-1,mid;
// 	while(l<r){
// 		mid=(l+r)>>1;
// 		if(v[mid].first==val)[[unlikely]]{
// 			return mid;
// 		}else if(v[mid].first>val){
// 			r=mid;
// 		}else{
// 			l=mid+1;
// 		}
// 	}
// 	return l;
// }
// void dfs(int day,long long vic,long long dmg){
// 	if(day>(n/2)){
// 		mp[dmg] = (mp[dmg] > vic) ? mp[dmg] : vic;
// 		// mp[dmg]=max(mp[dmg],vic);
// 		return;
// 	}
// 	for(int i=1;i<=m;i++){
// 		dfs(day+1,vic+p[day][i],dmg+c[day][i]-d[day][i]);
// 	}
// }
// void dfs1(int day,long long vic,long long dmg){
// 	if(day>n){
// 		auto tmp=find(-dmg);
// 		if(v[tmp].first==-dmg){
// 			// ans=max(ans,vic+v[tmp].second);
// 			ans = ans > vic+v[tmp].second ? ans : vic+v[tmp].second;
// 		}
// 		return;
// 	}
// 	for(int i=1;i<=m;i++){
// 		dfs1(day+1,vic+p[day][i],dmg+c[day][i]-d[day][i]);
// 	}
// }
signed main(){

	auto dfs = [](int day, long long vic, long long dmg, auto &&dfs){
		if(day>(n/2)){
			mp[dmg] = (mp[dmg] > vic) ? mp[dmg] : vic;
			// mp[dmg]=max(mp[dmg],vic);
			return;
		}
		for(int i=1;i<=m;i++){
			dfs(day+1,vic+p[day][i],dmg+c[day][i]-d[day][i], dfs);
		}
	};

	auto dfs1 = [](int day, long long vic, long long dmg, auto &&dfs1){
		auto find = [](int val){
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
		if(day>n){
			auto tmp=find(-dmg);
			if(v[tmp].first==-dmg){
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