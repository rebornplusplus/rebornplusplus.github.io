---
layout: default
---

# LightOJ 1299 - Fantasy Cricket
_Aug 29 2018 0639_

You have a string of 'U', 'E' and 'D'. You have to output the number of such permutations of that string so that every 'U' has a position right to it's previous position, every 'E' is in their previous position and every 'D' has a position left to their previous positions. Note that, the 'U's are not identical, they are all different as well as 'E' and 'D'. You might as well number them as `U1 U2 U3..`, `E1 E2 E3..` and `D1 D2 D3..`. [Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1299)

### Solution

This problem can be solved with DP. We keep the states where we are and how many position we have made empty as we have come here. Let `p` be the position and `u` the number of empty positions in `0..p-1`. Note that as we come from left, the empty positions will be used only to put 'D's there. Also, the number of empty positions is as same as the number of 'U's we haven't put yet.

The base case is, `p = n`. For `u = 0` the result should be 1, 0 elsewise. The transitions are:
```
str[p] == 'E'
    dp[p][u] = dp[p+1][u];  ( we just ignore it )
str[p] == 'U'
    dp[p][u] += dp[p+1][u+1];   ( we empty this place )
    dp[p][u] += u * dp[p+1][u]; ( we put an 'U' here from the u possible 'U's. 'U's in hand: u-1+1 )
str[p] == 'D'
    dp[p][u] += u * dp[p+1][u]; ( we empty this place but put the current 'D' in one of u empty places )
    dp[p][u] += u * u * dp[p+1][u-1];   ( we put an 'U' here and put this 'D' in one of u empty places )
```

My code:
```cpp
const ll MOD = 1000000007;
const int N = 1000+7;
char s[N];
int dp[N][N];	// position, ups used
int n;

int fun(int pos, int ups) {
	if(pos >= n) return !ups;
	int &r = dp[pos][ups];
	if(r != -1) return r;

	ll ret = 0;
	if(s[pos] == 'E') ret = fun(pos+1, ups);	// just ignore 'E'
	else if(s[pos] == 'U') {
		// just empty this place for 'D' s.
		ret += fun(pos+1, ups+1);
		if(ret >= MOD) ret -= MOD;
		// or put an 'U' here. ups-1 + 1 (current 'U')
		ret += ((ll) ups * (ll) fun(pos+1, ups)) % MOD;
		if(ret >= MOD) ret -= MOD;
	}
	else {
		// empty this place but place 'D' above
		ret += ((ll) ups * (ll) fun(pos+1, ups)) % MOD;
		if(ret >= MOD) ret -= MOD;
		// put an 'U' here and place 'D' above
		ret += ((ll) ups * (ll) ups * (ll) fun(pos+1, ups-1)) % MOD;
		if(ret >= MOD) ret -= MOD;
	}
	return r = ret;
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		scanf("%s", s);
		n = strlen(s);

		memset(dp, -1, sizeof dp);
		int res = fun(0, 0);
		printf("Case %d: %d\n", ++tc, res);
	}

	return 0;
}
```

***

{% include disqus.html %}
