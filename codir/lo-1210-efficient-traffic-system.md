---
layout: default
---

# LightOJ 1210 - Efficient Traffic System
_July 25 2018 0437_

You are given a graph of unidirectional edges. You have to calculate the minimum number of edges required to add to the graph so that any of the nodes can be reached from any other. [Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1210)

### Solution
Okay, let's start reducing this problem. There is a observation that if there's already a strongly connected component(scc) in the graph, then you don't need to add an edge between two nodes from that scc. So we can just ignore all the sccs. So convert the sccs to nodes. The graph will be now DAG.

Now we are faced with this problem: Given a DAG, the minimum number of edges to make a cycle consisting of every node on that DAG. Here's the clever part. To make a cycle, there should be at least one edge coming out from every node and at least one edge going in that node. So, count the number of nodes that have indegree = 0. Also the nodes with outdegree = 0. Answer is the maximum of these two counts.

There is a corner when number of nodes in the DAG is 1.

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define ub upper_bound
#define lb lower_bound
#define all(x) (x).begin(), (x).end()
#define dbg(x) cout << " -- dbg: " << (x) << "\n"
#define FastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const long long INF = 2000000000LL;

/*////////////////////
adj[] is the main graph
trans[] strores tranpose graph
ind[u] will store the component number where u belongs to
////////////////////*/
const int maxn = 20000 + 10; 	// 1e5
vector<int> adj[maxn], trans[maxn]; 
int ind[maxn], vis[maxn], idx = 0; 
stack<int> st; 

void dfs(int u) {
	vis[u] = 1;
	for(int i=0; i<(int) adj[u].size(); ++i) {
		int v = adj[u][i];
		if(!vis[v]) dfs(v);
	}
	st.push(u);
}
void dfs2(int u) {
	ind[u] = idx;
	for(int i=0; i<(int) trans[u].size(); ++i) {
		int v = trans[u][i];
		if(!ind[v]) dfs2(v);
	}
}
int scc(int n) {
	memset(vis, false, sizeof vis);
	while(!st.empty()) st.pop();
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) dfs(i);
	}
	for(int u = 1; u <= n; u++) {
		for(int i=0; i<(int) adj[u].size(); ++i) {
			int v = adj[u][i];
			trans[v].push_back(u);
		}
	}
	idx = 0;
	memset(ind, 0, sizeof ind);
	while(!st.empty()) {
		int u = st.top(); st.pop();
		if(ind[u]) continue; 
		idx++; dfs2(u); 
	}
	return idx;
}

bool in[maxn], out[maxn];

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for(int i=1; i<=n; ++i) adj[i].clear(), trans[i].clear();
		while(m--) {
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
		}
		
		int nn = scc(n);
		if(nn == 1) {
			printf("Case %d: 0\n", ++tc);
			continue;
		}
		memset(in, false, sizeof in);
		memset(out, false, sizeof out);
		for(int i=1; i<=n; ++i) {
			for(int j=0; j<(int) adj[i].size(); ++j) {
				int v = adj[i][j];
				if(ind[i] != ind[v]) {
					out[ind[i]] = true;
					in[ind[v]] = true;
				}
			}
		}
		int rin = 0, rout = 0;
		for(int i=1; i<=nn; ++i) rin += !in[i], rout += !out[i];
		int res = max(rin, rout);
		printf("Case %d: %d\n", ++tc, res);
	}

	return 0;
}
```
Happy Birthday, Timu :)
