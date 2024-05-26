#### A

将 `A` 视为 $+1$，`B` 视为 $-1$，则小 A 和小 B 票数之差的绝对值不超过 $k$，等价于任意两个前缀（后缀）和的差不超过 $k$。

注意到 $2^j > \sum_{i=1}^{j-1} 2^i$，因此从后往前贪心，不到万不得已不要产生花费，时间复杂度 $\mathcal O(n)$。

```cpp
// Author: xht
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, k;
	string s;
	cin >> n >> k >> s;
	const int P = 1e9 + 7;
	vector<int> c(n);
	c[0] = 2;
	for (int i = 1; i < n; i++) c[i] = c[i-1] * 2 % P;
	vector<int> a(n + 1);
	int ans = 0;
	for (int i = n - 1, w = 0; ~i; i--) {
		a[i] = a[i+1] + (s[i] == 'A' ? 1 : -1);
		if (a[i] + k < w) {
			ans = (ans + c[i]) % P;
			a[i] += 2;
		}
		w = max(w, a[i]);
	}
	cout << ans << endl;
	return 0;
}
```

#### B

依次计算 $c_i$。

每次取出 $\lfloor \frac ij \rfloor$ 相等的一段，根据数论分块只有 $\mathcal O(\sqrt n)$ 段。

可以发现这一段中 $i \bmod j$ 的值是一个公差为 $\lfloor \frac ij \rfloor$ 的等差数列。

考虑根号分治：

- 若 $j \le \sqrt n$，直接暴力算，时间复杂度 $\mathcal O(\sqrt n)$。
- 若 $j > \sqrt n$，数论分块，预处理公差 $d \le \sqrt n$ 的等差数列下标的前缀和，每次 $\mathcal O(1)$ 查询，时间复杂度 $\mathcal O(\sqrt n)$。

总时间复杂度 $\mathcal O(n \sqrt n)$。

```cpp
// Author: xht
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n;
	cin >> n;
	int m = sqrt(n);
	vector<int> a(n + 1), b(n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	vector<vector<int>> f(n, vector<int>(m + 1));
	const int P = 1e9 + 7;
	for (int i = 1; i <= m; i++)
		for (int j = 0; j < i; j++) {
			f[j][i] = b[j];
			for (int k = j + i; k < n; k += i)
				f[k][i] = (f[k-i][i] + b[k]) % P;
		}
	for (int i = 1; i <= n; i++) {
		int x = 0;
		for (int j = 1; j <= min(i, m); j++)
			x = (x + 1ll * a[i/j] * b[i%j]) % P;
		for (int l = min(i, m) + 1, r; l <= i; l = r + 1) {
			r = i / (i / l);
			x = (x + 1ll * a[i/l] * f[i%l][i/l]) % P;
		}
		cout << x << endl;
	}
	return 0;
}
```

#### C

先排序，使组长一定在组员后面。

设 $f[i][a][b]$ 表示前 $i$ 个人中，已经配好了 $a$ 组，还有 $b$ 组只有组员。

然后 dp，状态转移时，考虑每个人什么都不当、当组员、当组长三种情况即可。

特判 $2k > n$ 的情况（直接输出 `-1`），时间复杂度为 $\mathcal O(n \log n + nk^2)$。

```cpp
// Author: xht
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	if (2 * m > n) return cout << -1 << endl, 0;
	struct A {
		int w, s, p;
		A() {
			cin >> w >> s >> p;
			if (!--p) p = 3;
		}
	};
	vector<A> a(n);
	sort(a.begin(), a.end(), [&](A x, A y) {
		return x.w < y.w || x.w == y.w && x.p < y.p;
	});
	using ll = long long;
	const ll inf = 1e18;
	vector<vector<ll>> f(m + 1, vector<ll>(m + 1, inf));
	f[0][0] = 0;
	for (int i = 0; i < n; i++) {
		vector<vector<ll>> g = f;
		if (a[i].p != 3)
			for (int j = 0; j <= m; j++)
				for (int k = 0; k < m; k++)
					g[j][k+1] = min(g[j][k+1], f[j][k] + a[i].s);
		if (a[i].p != 1)
			for (int j = 0; j < m; j++)
				for (int k = 1; k <= m; k++)
					g[j+1][k-1] = min(g[j+1][k-1], f[j][k] + a[i].s);
		f = g;
	}
	if (f[m][0] == inf) cout << -1 << endl;
	else cout << f[m][0] << endl;
	return 0;
}
```

#### D

首先考虑长短不同的情况，那就是要求出本质不同的子序列的数量。

令 $f[i][j]$ 表示以第 $i$ 个数结尾的长度为 $j$ 的子序列个数。

令 $p[i]$ 表示第 $i$ 个数之前最后一个 $a[i]$ 的位置，如果没有则为 $0$。

则有：

$$
f[k][j+1]=\sum_{i=p[k]}^{k-1} f[i][j]
$$

可以前缀和优化，时间复杂度为 $\mathcal O(nm)$。

接下来考虑长度相同的情况。

设 $f[i][j]$ 为 $a$ 序列中以第 $i$ 个数结尾，$b$ 序列中以第 $j$ 个数结尾的本质相同的子序列个数。

则有当 $a_i = b_j$ 时:

$$
f[i][j]=\sum_{i_{1}=p_{a}[i]}^{i-1} \sum_{j_{1}=p_{b}[j]}^{j-1} f[i_{1}][j_{1}]
$$

设 $g[i][j]$ 为 $a$ 序列中以第 $i$ 个数结尾，$b$ 序列中以第 $j$ 个数结尾，在结尾之前本质相同但 $a_i > b_j$ 的子序列个数。

则有当 $a_i > b_j$ 时：

$$
g[i][j]=\sum_{i_{1}=p_{a}[i]}^{i-1} \sum_{j_{1}=p_{b}[j]}^{j-1} f[i_{1}][j_{1}]
$$

设 $h[i][j]$ 为 $a$ 序列中以第 $i$ 个数结尾，$b$ 序列中以第 $j$ 个数结尾，前者字典序大于后者字典序的子序列个数。

则有：

$$
h[i][j] = g[i][j] + \sum_{i_{1}=p_{a}[i]}^{i-1} \sum_{j_{1}=p_{b}[j]}^{j-1} h[i_{1}][j_{1}]
$$

那么答案就是 $\sum_{i=1}^n \sum_{j=1}^m h[i][j]$。

上面三种转移同样可以前缀和优化，只不过这里是二维的，总时间复杂度仍然为 $\mathcal O(nm)$。

```cpp
// Author: xht
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	using vi = vector<int>;
	vi a(n + 1), pa(n + 1), b(m + 1), pb(m + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		pa[i] = i;
		while (--pa[i] && a[pa[i]] != a[i]);
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
		pb[i] = i;
		while (--pb[i] && b[pb[i]] != b[i]);
	}
	const int P = 998244353;
	int ans = 0;
	auto calc = [&](int n, vi &a, vi &p) {
		vector<vi> f(n + 1, vi(n + 1));
		for (int i = 1, t = 0; i <= n; i++) f[i][1] = p[i] ? t : ++t;
		for (int j = 1; j < n; j++)
			for (int k = j + 1; k <= n; k++) {
				if (p[k]) f[k][j+1] = (f[k-1][j] - f[p[k]-1][j] + P) % P;
				else f[k][j+1] = f[k-1][j];
				f[k][j+1] = (f[k][j+1] + f[k-1][j+1]) % P;
			}
		return f;
	};
	auto fa = calc(n, a, pa), fb = calc(m, b, pb);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= min(i - 1, m); j++)
			ans = (ans + 1ll * fa[n][i] * fb[m][j]) % P;
	auto get = [&](vector<vi> &a, int x, int X, int y, int Y) -> int {
		if (!x && !y) return a[X][Y];
		if (!x) return (a[X][Y] - a[X][y-1] + P) % P;
		if (!y) return (a[X][Y] - a[x-1][Y] + P) % P;
		return ((1ll * a[X][Y] - a[x-1][Y] - a[X][y-1] + a[x-1][y-1]) % P + P) % P;
	};
	vector<vi> f(n + 1, vi(m + 1)), g(n + 1, vi(m + 1)), h(n + 1, vi(m + 1));
	for (int i = 0; i <= n; i++) f[i][0] = 1;
	for (int i = 0; i <= m; i++) f[0][i] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (a[i] == b[j]) f[i][j] = (f[i][j] + get(f, pa[i], i - 1, pb[j], j - 1)) % P;
			if (a[i] > b[j]) g[i][j] = get(f, pa[i], i - 1, pb[j], j - 1);
			h[i][j] = (g[i][j] + get(h, pa[i], i - 1, pb[j], j - 1)) % P;
			f[i][j] = ((1ll * f[i][j] + f[i-1][j] + f[i][j-1] - f[i-1][j-1]) % P + P) % P;
			g[i][j] = ((1ll * g[i][j] + g[i-1][j] + g[i][j-1] - g[i-1][j-1]) % P + P) % P;
			h[i][j] = ((1ll * h[i][j] + h[i-1][j] + h[i][j-1] - h[i-1][j-1]) % P + P) % P;
		}
	ans = (ans + h[n][m]) % P;
	cout << ans << endl;
	return 0;
}
```

