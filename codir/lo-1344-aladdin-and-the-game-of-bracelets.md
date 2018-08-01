---
layout: default
---

# LightOJ 1344 - Aladdin and the Game of Bracelets
_Aug 01 2018 2110_

Aladdin have some bracelets each having some pearls of different value. In a move he or the Genie can remove a pearl from a non-empty braelet. Automatically, the pearls in that bracelets that have values greater or equal to the value of the pearl removed will be removed. This way, instead of the previous bracelet, many new bracelets will emerge. A player loses if he can't give a move. Aladdin starts the game. [Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1344)

### Solution

This is pretty obvious sprague-grundy problem. For a bracelet, we find its grundy value. Then it's a nim game. About the winning moves for Aladdin, iterate over every pearl of every bracelet and see if after removing it the new xorsum equals to zero or not. On how to calculate the grundy value, you can dp it with states left and right pointer for a bracelet.

Kode:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int dp[N][N][N];	// idx, left, right
int a[N][N], sz[N];

int fun(int i, int l, int r) {
	if(l > r) return 0;
	int &ret = dp[i][l][r];
	if(ret != -1) return ret;

	bool vis[N];
	memset(vis, false, sizeof vis);
	for(int j=l; j<=r; ++j) {
		int temp = a[i][j];
		int past = l, k = l;
		int tval = 0;
		for(k=l; k<=r; ++k) {
			if(a[i][k] >= temp) {
				tval ^= fun(i, past, k-1);
				past = k+1;
			}
		}
		tval ^= fun(i, past, k-1);
		vis[tval] = true;
	}
	ret = 0;
	while(vis[ret]) ++ret;
	return ret;
}

void print(int n, int xorsum) {
	for(int i=0; i<n; ++i) {
		set<int> res;
		int txor = (xorsum ^ fun(i, 0, sz[i]-1));
		for(int j=0; j<sz[i]; ++j) {
			int temp = a[i][j];
			int past = 0, k = 0;
			int tval = txor;
			for(k=0; k<sz[i]; ++k) {
				if(a[i][k] >= temp) {
					tval ^= fun(i, past, k-1);
					past = k+1;
				}
			}
			tval ^= fun(i, past, k-1);
			if(!tval) res.insert(temp);
		}
		set<int>::iterator it = res.begin();
		while(it != res.end()) {
			printf("(%d %d)", i+1, *it);
			it++;
		}
	}
	printf("\n");
}

int main() {
	int t, tc=0;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		for(int i=0; i<n; ++i) {
			scanf("%d", sz+i);
			for(int j=0; j<sz[i]; ++j) scanf("%d", &a[i][j]);
		}

		memset(dp, -1, sizeof dp);
		int xorsum = 0;
		for(int i=0; i<n; ++i) xorsum ^= fun(i, 0, sz[i]-1);
		printf("Case %d: %s\n", ++tc, (xorsum ? "Aladdin" : "Genie"));
		if(xorsum) print(n, xorsum);
	}

	return 0;
}
```
I sometimes wish to slap me so hard _-
