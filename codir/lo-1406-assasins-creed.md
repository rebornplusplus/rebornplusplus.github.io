---
layout: default
---

# LightOJ 1406 - Assassin`s Creed
_Jul 24 2018 0800_

While this problem has a juicy statement, quite simply, it gives you a graph of maximum 15 nodes and unidirectional edges and tells you to partition the nodes in minimum number of sets such that no node belongs to more than one set and within a set every node can be traversed choosing some initial node in that set. You have to calculate the minimum number of such partitions you can make.<br/>
[Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1406)

### Solution
Um, its pretty much obvious bitmask dp. We can precalculate which nodes can be visited at one traversal. Then its just straight forward bitmask dp. The only confusion arises with the cycles when precalculating. In that case and also to traverse, we need to know which node we are at currently along with the mask.

My code:
```cpp
// LightOJ 1406 - Assasin's Creed
// rebornplusplus
// July 24 2018 0752

#include <bits/stdc++.h>
using namespace std;

const long long INF = 2000000000LL;

const int N = 15;
vector<int> g[N];
bool appears[(1 << N)];
bool vis[N][(1<<N)];
int dp[(1<<N)];

void dfs(int u, int taken) {
	vis[u][taken] = true;
	appears[taken] = true;
	for(int i=0; i<g[u].size(); ++i) {
		int v = g[u][i];
		if(!vis[v][(taken | (1<<v))]) {
			dfs(v, (taken | (1<<v)));
		}
	}
}

int fun(int available) {
	if(available == 0) return 0;
	int &r = dp[available];
	if(r != -1) return r;

	r = INF;
	for(int i=available; i>0; i = (available & (i-1))) {
		if(appears[i]) {
			r = min(r, 1 + fun(available ^ i));
		}
	}
	return r;
}

int main() {
	int t, tc=0;
	scanf("%d", &t);
	
	while(t--) {
		for(int i=0; i<N; ++i) g[i].clear();
		memset(vis, false, sizeof vis);
		memset(appears, false, sizeof appears);
		memset(dp, -1, sizeof dp);
		
		int n, m;
		scanf("%d %d", &n, &m);
		while(m--) {
			int u, v;
			scanf("%d %d", &u, &v);
			--u, --v;
			g[u].push_back(v);
		}
		for(int i=0; i<n; ++i) {
			if(!vis[i][(1<<i)]) dfs(i, (1<<i));
		}
		int res = fun((1<<n) - 1);
		printf("Case %d: %d\n", ++tc, res);
	}

	return 0;
}
```
