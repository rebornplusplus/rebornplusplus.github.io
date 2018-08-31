---
layout: default
---

# LightOJ 1345 - Aladdin and the Happy Garden
_Aug 31 2018 0856_

You're given `n` distinct numbers and a number `k`. You have to calculate the number of permutations of those numbers such that there are at least a `k` consecutive numbers forming an increasing sequence. There can be many such consecutive increasing sequence of lengths upto `k`. But they must not exceed `k` and there has to be at least one `k` length. [Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1345)

### Solution

This is the solution of the author(Iqram Mahmud) of this problem:
> My solution had states of [smaller][greater][number of consecutive increasing number considering the last number][ have i seen k increasing sequence already or not]. Smaller is the count of numbers smaller than the lastly placed number, greater is count of numbers greater than lastly placed number. In each step, I will pick a new number from this pool of numbers (smaller+greater), put it there and get result for the next state.
> 
> This solution is a bit slow for a large number of test cases. Since it's O(N^4), the total running time would be number_of_cases *O(N^4). There are three ways to handle it. One is adding one extra parameter for k. Another is noticing that for the same k, we can just calculate it once, and retrieve all the results from there. So we take all the input, sort them according to K, process each input with same k together, update an answer array. And finally print the answer array.
> 
> And obviously the third way is precalculating the answers for all possible N and K.
> 
> Hope it helps.

Code:
```cpp
const ll MOD = 1000000000+7;
const int N = 53;
int dp[N][N][N][2];
int res[N][N];

void prep() {
	for(int k=1; k<N; ++k) {
		for(int i=0; i<=k; ++i) {
			dp[0][0][i][0] = 0;
			dp[0][0][i][1] = 1;
		}
		for(int tot=2; tot<N; ++tot) {
			for(int s=0; s<tot; ++s) {
				int g = tot-1 - s;
				for(int c=0; c<=k; ++c) {
					for(int f=0; f<2; ++f) {
						int &r = dp[s][g][c][f];
						r = 0;
						for(int i=1; i<=s; ++i) {
							r += dp[i-1][g+s-i][1][f];
							if(r >= MOD) r -= MOD;
						}
						if(c == k) continue;
						int ff = (f | (c+1 == k));
						for(int i=1; i<=g; ++i) {
							r += dp[s+i-1][g-i][c+1][ff];
							if(r >= MOD) r -= MOD;
						}
					}
				}
			}
		}
		for(int n=1; n+1<N; ++n) res[n][k] = dp[0][n][0][0];
	}
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	prep();
	while(t--) {
		int n, k;
		scanf("%d %d", &n, &k);
		// int res = dp[0][n][0][0][k];
		printf("Case %d: %d\n", ++tc, res[n][k]);
	}

	return 0;
}
```

***

{% include disqus.html %}
