---
layout: default
---

## CSE 208

__First lab__

Given a dag. Find the maximum number of edges that could be added so that the graph remains a dag. Print those edges.

Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 107;  // MAX V
vector< int > g[N];
int ind[N];

vector<int> topSort(int n) {
    queue< int > q;
    for(int i=1; i<=n; ++i) if(!ind[i]) q.push(i);

    vector< int > ts;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        ts.push_back(u);

        for(int v : g[u]) {
            --ind[v];
            if(!ind[v]) q.push(v);
        }
    }
    return ts;
}

int main() {
    freopen("in.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    for(int i=1; i<=n; ++i) g[i].clear(), ind[i] = 0;

    for(int i=1; i<=m; ++i) {
        int u, v;
        cin >> u >> v;
        ++ind[v];
        g[u].push_back(v);
    }

    vector<int> ts = topSort(n);
    for(int i=1; i<=n; ++i) sort(g[i].begin(), g[i].end());

//    int cnt_e = ((n-1) * n) / 2;
//    cnt_e -= m;
//    cout << " just testing: " << cnt_e << "\n";

    vector< pair<int, int> > edg;
    for(int i=0; i<(int) ts.size(); ++i) {
        int u = ts[i];
        for(int j=i+1; j<(int) ts.size(); ++j) {
            int v = ts[j];
            if(find(g[u].begin(), g[u].end(), v) == g[u].end()) {
                edg.push_back(make_pair(u, v));
            }
        }
    }

    cout << edg.size() << "\n";
    for(auto e : edg) {
        cout << e.first << " " << e.second << "\n";
    }

    return 0;
}
```

I guess I will re-format this.
