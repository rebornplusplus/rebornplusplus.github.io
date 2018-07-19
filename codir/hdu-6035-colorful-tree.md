---
layout: default
---

# HDU 6035 - Colorful Tree
_Jul 20 2018 0230_

Given a tree of `n` nodes, each node having a color to it. The value of a path from node `u` to node `v` is the number of unique colors appearing in it. We have to calculate the summation of values of all the `n(n-1)/2` paths. [Problem Statement](http://acm.hdu.edu.cn/showproblem.php?pid=6035)

### Solution
I feel so lazy to type :3
![Idea](/hdu-6035-01.jpg)

### Code
```cpp
// HDU 6035 - Colorful Tree
// rebornplusplus
// July 20 2018 0224

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 200000 + 7;
vector<int> g[N];
int subsz[N];	// subgraph size of node i
int sum[N];	// sum of nodes under color i
int c[N];	// color of node i
ll res;

int dfs(int u, int p) {
	subsz[u] = 1;
	for(int v : g[u]) {
		if(v == p) continue;
		int prev = sum[c[u]];
		subsz[u] += dfs(v, u);
		int same = sum[c[u]] - prev;
		ll others = subsz[v] - same;
		// the number of paths in the subgraph of v not containing c[u]
		res -= (others * (others-1)) / 2;
		// adding this number as to further calculation
		sum[c[u]] += others;
	}
	++sum[c[u]];
	return subsz[u];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	ll n, tc=0;
	while(cin >> n) {
		for(int i=1; i<=n; ++i) {
			g[i].clear();
			sum[i] = 0;
		}
		for(int i=1; i<=n; ++i) cin >> c[i];
		for(int i=1; i<n; ++i) {
			int u, v;
			cin >> u >> v;
			g[u].push_back(v);
			g[v].push_back(u);
		}

		res = n * ((n*(n-1))/2);
		dfs(1, 0);
		for(int i=1; i<=n; ++i) {
			ll rest = n-sum[i];
			res -= (rest*(rest-1))/2;
		}
		cout << "Case #" << ++tc << ": " << res << "\n";
	}

	return 0;
}
```

Thanks to [this blog](http://www.cnblogs.com/chen9510/p/7258453.html) for the code. Although I had to simulate and understand! I couldn't quite catch what they were trying to say in chinese. :/

***

{% include disqus.html %}
