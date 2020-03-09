namespace TreeGenerator {
	vector<int> dsu;
	vector< vector<int> > g;
	
	void makeSet(int n) {
		dsu.resize(n+1);
		g.resize(n+1);
		for(int i=0; i<=n; ++i) {
			dsu[i] = i;
			g[i].clear();
		}
	}

	int findPar(int r) {
		return dsu[r] == r ? r : dsu[r] = findPar(dsu[r]);
	}

	bool unite(int u, int v) {
		int pu = findPar(u), pv = findPar(v);
		if(pu == pv) return false;
		dsu[pv] = pu;
		return true;
	}

	void dfs(int u, int p, int *par) {
		par[u] = p;
		for(int v : g[u]) if(v != p) dfs(v, u, par);
	}
	
	void getTree(int n, int *par, int root = 1) {
		makeSet(n);

		int cnt = 0;
		while(cnt < n - 1) {
			int u = rand(1, n), v = rand(1, n);
			if(unite(u, v)) {
				g[u].push_back(v);
				g[v].push_back(u);
				++cnt;
			}
		}

		dfs(root, -1, par);
	}
};
