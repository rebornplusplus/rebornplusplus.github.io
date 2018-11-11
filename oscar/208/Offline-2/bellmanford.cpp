
#include <cstdio>
#include <malloc.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

template <class T>
class Vector {
	static const int initial_sz = 2;
	T *a;
	int sz, len;

	void balance() {
		if(sz == 0) {
			a = (T*) malloc(initial_sz * sizeof(T));
			len = initial_sz;
		}
		else if(sz == len) {
			int nlen = len<<1;
			T *temp = (T*) malloc(nlen * sizeof(T));
			for(int i=0; i<sz; ++i) temp[i] = a[i];
			free(a);
			a = temp;
			len = nlen;
		}
		else if(sz+sz < len/2) {
			int nlen = len>>1;
			if(nlen < initial_sz) nlen = initial_sz;
			T *temp = (T*) malloc(nlen * sizeof(T));
			for(int i=0; i<sz; ++i) temp[i] = a[i];
			free(a);
			a = temp;
			len = nlen;
		}
	}

public:
	Vector() {
		sz = 0, len = 0;
	}

	Vector(const Vector &p) {
		sz = 0, len = 0;
		while(sz < p.sz) {
			balance();
			a[sz] = p.a[sz];
			++sz;
		}
	}

	void push_back(T key) {
		balance();
		a[sz] = key;
		++sz;
	}

	void pop_back() {
		--sz;
		balance();
	}

	int size() {
		return sz;
	}

	bool empty() {
		return sz == 0;
	}

	T front() {
		return a[0];
	}

	T back() {
		return a[sz-1];
	}

	void clear() {
		sz = 0, len = 0;
		free(a);
		a = NULL;
	}

	T operator [] (int pos) {
		return a[pos];
	}

	Vector operator = (Vector p) {
		sz = 0, len = 0;
		while(sz < p.sz) {
			balance();
			a[sz] = p.a[sz];
			++sz;
		}
		return *this;
	}

	~Vector() {
		sz = 0, len = 0;
		free(a);
	}
};

//const int INF = 1000000000;
const int INF = 0x3f3f3f3f;
const int N = 1007; // Max number of nodes
Vector< int > g[N], c[N];   // adjacency list, weight function
int dis[N]; // stores the distance from source

bool bellmanford(int n, int src = 1) {
    for(int i=1; i<=n; ++i) {
        dis[i] = INF;
    }
    dis[src] = 0;

    for(int i=1; i<=n; ++i) {
        for(int u=1; u<=n; ++u) {
            for(int j=0; j<(int) g[u].size(); ++j) {
                int v = g[u][j];
                if(dis[v] > dis[u] + c[u][j]) {
                    dis[v] = dis[u] + c[u][j];
                    if(i == n) return false;
                }
            }
        }
    }

    return true;
}

int main() {
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    for(int i=1; i<=n; ++i) {
        g[i].clear();
        c[i].clear();
    }

    for(int i=1; i<=m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(v);
        c[u].push_back(w);
    }

    int src;
    cin >> src;
    if(bellmanford(n, src)) {
        for(int i=1; i<=n; ++i) {
            cout << "Distance from " << src << " to " << i << ": " << dis[i] << "\n";
        }
    }
    else {
        cout << "Negative cycle detected!\n";
    }

    return 0;
}
