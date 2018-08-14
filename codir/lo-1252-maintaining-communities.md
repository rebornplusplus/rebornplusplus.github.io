---
layout: default
---

# LightOJ 1252 - Maintaining Communities
_Aug 15 2018 0341_

Given a weighted tree of maximum 100 nodes. You have to divide it into minimum number of components such that no component has the edge weight summation more than `K` where `K <= 100`. [Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1252)

### Solution

We keep a table where `dp[i][j]` which is the minimum number of components in the subtree of `i` with a maximum allowance of edge weight equals `j`. Initially for all `j`, `dp[i][j] = 1` (the node itself). Then for each child we iterate over values of `j` and for each such `j`, we can take that child in the same component or not. If we take that child `v`, we set a maximum allowance for it, consider it `l`, `dp[i][j]` will be the minimum of `dp[i][j-cost[i][v]-l] + dp[v][l] - 1`. If we don't take `v`, we add the minimum of `dp[v][l]` for all `l = 0..k` to `dp[i][j]`. The basic idea is to whether take a child or not, that's about it. Answer is the minimum of `dp[1][j]` for every `j = 0..k`.

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 107;
vector<int> g[N], c[N];
int dp[N][N];
int n, k;

void dfs(int u, int p) {
	for(int i=0; i<=k; ++i) dp[u][i] = 1;
	for(int i=0; i<(int) g[u].size(); ++i) {
		int v = g[u][i], w = c[u][i];
		if(v == p) continue;
		dfs(v, u);

		for(int j=k; j>=0; --j) {
			int sep = INF;
			for(int _=0; _<=k; ++_) sep = min(sep, dp[v][_]);
			dp[u][j] += sep;
			for(int _=0; _<=j-w; ++_) {
				dp[u][j] = min(dp[u][j], (dp[u][j-w-_] + dp[v][_] - 1));
			}
		}
	}
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		scanf("%d %d", &n, &k);
		for(int i=1; i<=n; ++i) g[i].clear(), c[i].clear();
		for(int i=1; i<n; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			g[u].push_back(v);
			c[u].push_back(w);
			g[v].push_back(u);
			c[v].push_back(w);
		}

		dfs(1, 0);
		int res = n;
		for(int i=0; i<=k; ++i) res = min(res, dp[1][i]);
		printf("Case %d: %d\n", ++tc, res);
	}

	return 0;
}
```

***

{% include disqus.html %}
