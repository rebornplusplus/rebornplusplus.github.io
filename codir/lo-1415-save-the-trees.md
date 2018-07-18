---
layout: default
---

# LightOJ 1415 - Save the Trees!

Do read the [statement](http://lightoj.com/volume_showproblem.php?problem=1415) first!

### My solution

Just pasting my code for this while.

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

const int N = 200000 + 7;
int c[N], h[N];	// color and height
int pre[N];	// last valid position from i
int last[N];	// last index of color c[i];
int desc[N];	// last max height
pll seg[N*4];
ll dp[N];	// dp[i] = result for 1..i
int n;

void precal() {
	memset(last, 0, sizeof last);
	for(int i=1; i<=n; ++i) {
		pre[i] = max(last[c[i]]+1, pre[i-1]);
		last[c[i]] = i;
	}
}

inline void propagate(int at) {
	int lc = at+at, rc = lc+1;
	seg[lc].ss += seg[at].ss;
	seg[rc].ss += seg[at].ss;
	seg[at].ss = 0;
}

inline ll getval(pll &r) {
	return r.ff + r.ss;
}

void build(int at, int l, int r) {
	if(l == r) {
		seg[at] = mp(0, 0);
		return ;
	}
	int lc = at+at, rc = lc+1, mid = (l+r)/2;
	build(lc, l, mid);
	build(rc, mid+1, r);
	seg[at].ff = getval(seg[lc]) + getval(seg[rc]);
	seg[at].ss = 0;
}

// add x to lo-hi
void update(int at, int l, int r, int lo, int hi, ll x) {
	if(l>hi or r<lo) return;
	if(l>=lo and r<=hi) {
		seg[at].ss += x;
		return ;
	}
	propagate(at);
	int lc=at+at, rc=lc+1, mid=(l+r)/2;
	update(lc, l, mid, lo, hi, x);
	update(rc, mid+1, r, lo, hi, x);
	seg[at].ff = min(getval(seg[lc]), getval(seg[rc]));
}

// minimum in lo-hi
ll query(int at, int l, int r, int lo, int hi) {
	if(l>hi or r<lo) return LLONG_MAX;
	if(l>=lo and r<=hi) return getval(seg[at]);
	propagate(at);
	int lc=at+at, rc=lc+1, mid=(l+r)/2;
	ll ret = min(query(lc, l, mid, lo, hi), query(rc, mid+1, r, lo, hi));
	seg[at].ff = min(getval(seg[lc]), getval(seg[rc]));
	return ret;
}

int main() {
	int t, tc=0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i=1; i<=n; ++i) scanf("%d %d", c+i, h+i);

		precal();
		build(1, 1, n);
		h[0] = INF;
		desc[0] = 0;
		int cur = 1;
		for(int i=1; i<=n; ++i) {
			// subtracting the previously added hights
			while(h[desc[cur-1]] <= h[i]) {
				update(1, 1, n, desc[cur-2]+1, desc[cur-1], -h[desc[cur-1]]);
				--cur;
			}
			// current height is the new descendant
			desc[cur++] = i;
			update(1, 1, n, desc[cur-2]+1, desc[cur-1], h[i]);
			// calculate dp and update for the next place
			dp[i] = query(1, 1, n, pre[i], i);
			update(1, 1, n, i+1, i+1, dp[i]);
		}

		printf("Case %d: %lld\n", ++tc, dp[n]);
	}
	
	return 0;
}
```

***
{% include disqus.html %}
