---
layout: default
---

# LightOJ 1342 - Aladdin and the Magical Sticks
_Sept 01 2018_

[Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1342)

> The task was that, there were n sticks, each had a particular weight. Two types of sticks were there, one kind of sticks had distinguishable rough patterns that can be identified by just touching. Other types of sticks were indistinguishable. Each time Aladdin had to pick a stick from all sticks and put it into a magical box. If all the sticks are put into the box at least once, Aladdin will be free; otherwise the stick he just put will be put with the other sticks.
> 
> So, Aladdin planned that each time he will pick a new stick randomly and put it into the magical box. So, once he put a distinguishable stick into the box, he will not put it again though it's mixed with other sticks, since he can remember the roughness of every distinguishable stick. But for indistinguishable sticks he had no option. So, each time he put a stick that looked new to him, but that might not be a new one. And each time the probability of picking a new (to Aladdin of course!) stick is equal. Now your task is to find the expected summation of weights of sticks Aladdin had to put into the box before he was free.

### Solution

Had the weights been same, we could just calculate the expected number of moves to pick up each stick at least once. Then multiply the weight with the result. _A move means picking up a stick._ But the weights are all possibly different. But we can do this in the same manner. This time, we take the average weight of both type of sticks.

Let `n1, n2` be the number of indistinguishable and distinguishable sticks, `avg1, avg2` their average weight respectively. `dp[i][j]` be the expected weight when we've already picked up `i` indistinguishable and `j` distinguishable sticks. Also, `rest = n-j`, the number of sticks from which we'll pick up another stick.

`dp[i][j] += (n1-i)/rest * dp[i+1][j]`, picked up a new indistinguishable stick<br/>
`dp[i][j] += (n2-j)/rest * dp[i][j+1]`, picked up a new distinguishable stick<br/>
`dp[i][j] += i/rest * dp[i][j]`, picked up an old indistinguishable stick<br/>
Obviously, `dp[n1][n2] = 0`.

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5007;
double dp[2][N];
// dp[i][j] - i indistinguishable taken, j distinguishable taken
// dp[i][j] = (n1-i)/rest * (dp[i+1][j]+avg1) + (n2-j)/rest * (dp[i][j+1]+avg2) + i/rest * (dp[i][j]+avg1)
// dp[i][j] * (1-i/rest) = (n1-i)/rest * dp[i+1][j] + (n2-j)/rest * (dp[i][j+1]+avg2) + n1/rest*avg1
// dp[i][j] * (rest-i) = (n1-i) * dp[i+1][j] + (n2-j) * (dp[i][j+1]+avg2) + n1*avg

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		int n;
		scanf("%d", &n);
		int n1 = 0, n2 = 0;
		int sum1 = 0, sum2 = 0;
		for(int i=0; i<n; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			if(b == 2) sum1 += a, ++n1;
			else sum2 += a, ++n2;
		}
		double avg2 = 0;
		if(n2 > 0) avg2 = (double) sum2 / (double) n2;

		dp[n1&1][n2] = 0;
		for(int i=n1; i>=0; --i) {
			for(int j=n2-(i==n1); j>=0; --j) {
				int rest = n-j;
				dp[i&1][j] = (double) (n1-i) * dp[(i+1)&1][j] + (double) (n2-j) * (dp[i&1][(j+1)]+avg2) + (double) sum1;
				dp[i&1][j] /= (rest-i);
			}
		}
		double res = dp[0][0];
		printf("Case %d: %.10lf\n", ++tc, res);
	}

	return 0;
}
```

There's another approach to this problem. One like the "[Coupon Collector's Problem](https://en.wikipedia.org/wiki/Coupon_collector%27s_problem)" with Harmonic Numbers. Read it here [:D](http://lbv-pc.blogspot.com/2012/09/aladdin-and-magical-sticks.html)

***

{% include disqus.html %}
