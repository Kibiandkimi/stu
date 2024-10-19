### KMP

字符串匹配算法，在txt中寻找pat。

```c++
template<typename T>
class KMP {
	vector<T> pat;
	vector<uint> pi;

	void init() {
		for (uint i = 1; i < pi.size(); i++) {
			uint j = pi[i - 1];
			while (j != 0 && pat[j] != pat[i]) {
				j = pi[j - 1];
			}
			pi[i] = j + (pat[i] == pat[j]);
		}
	}

public:
	explicit KMP(vector<T> &pat) : pat(move(pat)), pi(pat.size()) {init();}
	explicit KMP(const vector<T> &pat) : pat(pat), pi(pat.size()) {init();}

	vector<uint> match(const vector<T> &txt) {
		vector<uint> res;
		uint j = 0;
		for (auto i = txt.begin(); i != txt.end(); ++i) {
			while (j != 0 && pat[j] != *i) {
				j = pi[j - 1];
			}
			pat[j] == *i ? ++j : j;
			j == pat.size() ? static_cast<void>(res.emplace_back(i - txt.begin()), j = pi[j - 1]) : static_cast<void>(0);
		}
		return res;
	}

};
```



重点在nxt数组的构造，pre是具有与当前状态相同后缀的位置（以前看文章上写前缀，就半天没懂）。

当前的nxt通过pre转移，pre也通过pre转移。由于具有相同后缀，所以nxt可以通过pre转移。

不知道怎么写note
