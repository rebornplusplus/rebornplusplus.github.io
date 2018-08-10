---
layout: default
---

# UVaLive 7305 - Jumping Joey
_Aug 11 2018 0313_

Joey, the frog, is trying to cross a pond. There are some lilypads in a straight line from the left end of the pond to the right end. Also the lilypads are tied with ropes of different lengths. When on a lilypad, Joey can swim to the next one. Or he can jump to the next one if the distance between is maximum D. He can also pull the ropes so that the next pads come closer. He wants to know the minimum number of times he has to wet himself i.e. he has to swim :p. Note that he can't just swim from the left end to the right end. He has to visit every lilypad. [Problem Statement](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5317)

### Solution

I think the dp solution is sensible. What about the states? We can keep the index of the current lilypad and the number of times Joey had to wet himself (:p) to get here. So what do we keep in the value? We keep the minimum amount we need to move lilypad `i` in order to reach `i` wetting `j` times. In the end, we see for which minimum value of `j`, the `n+1 th` lilypad needs to be moved by Zero amount.<br/>
About the dp transition, let's say we're at lilypad `i`. Now we can only come to `i` having `j` times wet if we can reach `i-1` in `j` times wet or `j-1`. In the first case, we need to jump from `i-1` to `i`. Now let's find the distance between `i-1` and `i`. We know that the `i-1 th` has been moved `dp[i-1][j]` amount to the left in the first case. So the distance would be `p[i] - p[i-1] + dp[i-1][j]`. Now to jump, distance needs to be less or equal to `D`. If it's already that, we don't need to move the `i th` pad. If not we need to move it by `distance - d` amount. The second case can be calculated likewise. The rope values come in when the distance is bigger than the rope length. Then you have to move `i` by `distance - rope length` at first. Assign rope length to distance and do the same thing stated above.

See the code for a better standing:

```cpp
// Mahathir vai beshi boss :hearts:

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define FastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const long long INF = 2000000000000000000LL;

const int N = 1000+7;
int p[N], r[N];
ll dp[N][N];	// dp[i][j] is the minimum amount that i needs to be moved with j times wet

int main() {
	FastIO;

	int t, tc=0;
	cin >> t;

	while(t--) {
		int n, d;
		cin >> n >> d;
		++n;
		for(int i=0; i<=n; ++i) cin >> p[i];
		for(int i=1; i<=n; ++i) cin >> r[i];

		for(int i=0; i<=n; ++i) for(int j=0; j<=n; ++j) dp[i][j] = INF;
		dp[0][0] = 0;
		for(int i=1; i<=n; ++i) {
			for(int j=0; j<i; ++j) {
				if(dp[i-1][j] == INF) continue;
				ll dis = p[i] - p[i-1] + dp[i-1][j];
				ll move = 0;
				if(dis > r[i]) move = dis-r[i], dis = r[i];
				if(dis <= d) {
					dp[i][j] = min(dp[i][j], move);
				}
				else {
					dp[i][j] = min(dp[i][j], move + dis-d);
				}
				dp[i][j+1] = min(dp[i][j+1], move);
			}
		}

		int res = n;
		for(int i=0; i<=n; ++i) if(dp[n][i] == 0) {
			res = i;
			break;
		}
		cout << "Case " << ++tc << ": " << res << "\n";
	}

	return 0;
}
```

Thanks to Mahathir vai for the solution. He writes good codes. ^_^

***

{% include disqus.html %}
