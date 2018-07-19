---
layout: default
---

# HDU 4630 - No Pain No Game
_Jul 19 2018 1720_

Given a permutation of numbers from `1` to `N` and some queries. For each query `l-r` you have to calculate the maximum gcd for any two numbers `a[i]`, `a[j]` where `l<=i<j<=r`.

### Solution
First sort the queries on the ascending order of `r`. Also, precalculate the divisors of every number. Keep an array `last` where `last[p]` indicates the last position of the number that `p` was a divisor of, i.e. `p | a[last[p]]`. <br/>
Now for each `a[i]`, iterate over all the divisors and update them to their last position. Point update over a point `p` with `x` will be to keep the maximum of current value and `x`. After all the updates, see if any query ends in `i`. For those queries, query over `l-r` to get the maximum value in that range. That's the maximum gcd for the given query range.

My code:
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

const int N = 50000 + 7;
vector<int> dv[N];
int seg[N*4];
int a[N], last[N], res[N];
int n, q;

struct qdat {
	int l, r, i;
	qdat() { }
	qdat(int ll, int rr, int ii) { l=ll, r=rr, i=ii; }
	bool operator < (const qdat &p) const { return r < p.r; }
} qu[N];

void seive() {
	for(int i=1; i<N; ++i) {
		for(int j=i; j<N; j+=i) {
			dv[j].pb(i);
		}
	}
}

void build() {
	memset(seg, 0, sizeof seg);	// :p
	memset(last, 0, sizeof last);	// :P
}

// update x at position p
void update(int at, int l, int r, int p, int x) {
	if(l == r) {
		seg[at] = max(seg[at], x);
		return ;
	}
	int lc=at+at, rc=lc+1, mid=(l+r)/2;
	if(p <= mid) update(lc, l, mid, p, x);
	else update(rc, mid+1, r, p, x);
	seg[at] = max(seg[lc], seg[rc]);
}

int query(int at, int l, int r, int lo, int hi) {
	if(l > hi or r < lo) return 0;
	if(l >= lo and r <= hi) return seg[at];
	int lc=at+at, rc=lc+1, mid=(l+r)/2;
	return max(query(lc, l, mid, lo, hi), query(rc, mid+1, r, lo, hi));
}

void solve() {
	build();
	sort(qu, qu+q);
	for(int i=0, j=0; i<n; ++i) {
		for(auto v : dv[a[i]]) {
			if(last[v]) {
				update(1, 1, n, last[v], v);
			}
			last[v] = i+1;
		}
		while(j<q and qu[j].r == i+1) {
			if(qu[j].l == qu[j].r) res[qu[j].i] = 0;
			else res[qu[j].i] = query(1, 1, n, qu[j].l ,qu[j].r);
			++j;
		}
	}
}

int main() {
	FastIO;

	seive();
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i=0; i<n; ++i) cin >> a[i];
		cin >> q;
		for(int i=0; i<q; ++i) {
			cin >> qu[i].l >> qu[i].r;
			qu[i].i = i;
		}
		solve();
		for(int i=0; i<q; ++i) cout << res[i] << "\n";
	}

	return 0;
}
```

Thanks to Mottakin vai for explaining this to me. :D

***

{% include disqus.html %}
