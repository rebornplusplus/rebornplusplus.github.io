---
layout: default
---

# LightOJ 1329 - Playing Cards
_Aug 28 2018 1132_

In a regular card set there are 52 cards, each card has two parts, the value and the suit. The values are one of 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A and the suit is one of H, S, D, C. Cards are represented first by their value and then by their suit. For example, 7H, 2C, JD etc are some cards.

Now from the regular card set, you removed some of the cards (probably 0). Your task is to find the number of ways you can place the cards in a line such that no two adjacent cards have the same value. You have to use all the cards (of course the remaining cards).

For example, 2H, 3C, 5C is a valid solution, but 5H, 5C, 7S is not. [Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1329)

### Solution

Thanks to this blog: [https://tipofmind.wordpress.com/2016/01/15/lightoj-1329-playing-cards/](https://tipofmind.wordpress.com/2016/01/15/lightoj-1329-playing-cards/).

```cpp
typedef unsigned long long dat;
const int N = 14;
dat dp[N][N][N][N][5];
// number of cards with same values 4 times, 3 times, 2 times, 1 time
// and last card taken from which frequency
bool vis[N][N][N][N][5];
int freq[N], cnt[5];

dat fun(int four, int thr, int two, int one, int pre) {
	if(four+thr+two+one == 0) return 1;
	dat &r = dp[four][thr][two][one][pre];
	bool &v = vis[four][thr][two][one][pre];
	if(v) return r;

	v = true, r = 0;
	dat mul;
	if(four) {
		mul = four * 4;
		r += mul * fun(four-1, thr+1, two, one, 4);
	}
	if(thr) {
		mul = (pre == 4 ? (thr-1) : thr) * 3;
		r += mul * fun(four, thr-1, two+1, one, 3);
	}
	if(two) {
		mul = (pre == 3 ? (two-1) : two) * 2;
		r += mul * fun(four, thr, two-1, one+1, 2);
	}
	if(one) {
		mul = (pre == 2 ? (one-1) : one);
		r += mul * fun(four, thr, two, one-1, 1);
	}
	return r;
}

string vals = "23456789TJQKA";
inline int ctoi(char c) {
	return vals.find(c);
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	memset(vis, false, sizeof vis);
	while(t--) {
		int n;
		scanf("%d", &n);
		memset(freq, 0, sizeof freq);
		memset(cnt, 0, sizeof cnt);
		char s[5];
		while(n--) {
			scanf("%s", s);
			++freq[ctoi(s[0])];
		}
		for(int i=0; i<13; ++i) ++cnt[freq[i]];

		dat res = fun(cnt[4], cnt[3], cnt[2], cnt[1], 0);
		printf("Case %d: %llu\n", ++tc, res);
	}

	return 0;
}
```
I tried writing on my own. But turned out that blog explained it better. :D

***

{% include disqus.html %}
