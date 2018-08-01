---
layout: default
---

# CodeChef - Spanning Tree
_Aug 01 2018 1212_

This is an interactive problem. You're given the number of vertices in an undirected connected graph. You can make some queries to the judge. You can give two disjoint sets of vertices to the judge and it'll return the minimum weighted edge between those two sets. Specifically, if you give two sets A and B, the judge will give you an edge u v w where u belongs to A, v belongs to B. In case, there's no edge between those set, it will give you -1 -1 -1.

Now there's a cost for each query. It's the cardinality of the first set. You have 10^4 coins and a maximum of 10^3 nodes. You have to find out the mst cost for this graph making those queries. [Problem Statement](https://www.codechef.com/problems/SPANTREE)

### Solution

You can just read the editorial from [here](https://discuss.codechef.com/questions/121140/spantree-editorial). I liked this trick. What they did was first take a single node in set A and all others in B. Thus you get an edge from that node and it's guranteed to be in mst. Suppose you got u v w. So, u and v are connected. We keep u, v in the same set. Then we do this for other nodes. Soon, instead of having 1 size for the set A, we get two sized A. Doing this, we get 4, 8, .. . Note that we make this thing log n times at best each time making n queries. So n lg n coins are needed maximum!

Kode:
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
const long double EPS = 1e-9;

const int N = 1000+7;
int par[N], rep[N];

int Find(int r) {
	return (r == par[r]) ? r : (par[r] = Find(par[r]));
}

int main() {
	int n;
	scanf("%d", &n);

	set< pii > st;
	for(int i=1; i<=n; ++i) {
		par[i] = i, rep[i] = 1;
		st.insert(mp(1, i));
	}
	int res = 0;
	while(st.size() > 1) {
		auto top = *st.begin();
		int tu = top.ss;
		vector<int> a, b;
		for(int i=1; i<=n; ++i) {
			if(Find(i) == tu) a.pb(i);
			else b.pb(i);
		}

		printf("1 %d %d\n", a.size(), b.size());
		fflush(stdout);
		for(int x : a) printf("%d ", x);
		printf("\n"); fflush(stdout);
		for(int x : b) printf("%d ", x);
		printf("\n"); fflush(stdout);
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		assert(u != -1);

		res += w;
		st.erase(st.find(top));
		int tv = Find(v);
		st.erase(st.find(mp(rep[tv], tv)));
		if(rep[tv] > rep[tu]) swap(tu, tv);
		par[tv] = tu;
		rep[tu] += rep[tv];
		st.insert(mp(rep[tu], tu));
	}
	printf("2 %d\n", res);
	fflush(stdout);

	return 0;
}
```

I wasn't printing the "1 " in the queries. That resulted in TLE multiple times. _- 

***

{% include disqus.html %}
