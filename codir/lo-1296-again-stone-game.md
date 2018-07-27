---
layout: default
---

# LightOJ 1296 - Again Stone Game
_Jul 27 2018 1218_

Two players are playing a game. There are some piles of stone. In each turn, a player can choose a pile and remove one or more stones from that pile but he can't remove more than half of the stones from that pile. The loser is the one who can't make a move.
[Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1296)

### Solution

Had only the number of stones in each pile less, we could've brute forced sprague-grundy solution. But in each pile, there can be at most 1e9 stones. So this is where pattern finding comes. You get the idea right? We first find the sprague-grundy value for each pile, then it's a basic nim game. Patterns arise in the grundy values. You can do one thing, find the grundy values of 1 to 100. That ought to help. Another hint: grundy values increments over a period.

My code:
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int grrr(int x) {
	if(x == 0 or x == 1) return 0;
	if(x % 2 == 0) return x/2;
	for(int i=1; i<31; ++i) {
		int cur = (1<<i), rem = (1<<(i-1))-1;
		if(x % cur == rem) {
			int pos = (x - rem) / cur;
			return pos;
		}
	}
	return 0;
}

int main() {
	int t, tc=0;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		int xorsum = 0;
		while(n--) {
			int x;
			scanf("%d", &x);
			xorsum ^= grrr(x);		
		}
		printf("Case %d: %s\n", ++tc, (xorsum ? "Alice" : "Bob"));
	}

	return 0;
}
```

If you're still stuck: 
```
Number of Stones - Grundy value
2 - 1
4 - 2
6 - 3
8 - 4
10 - 5
--
1 - 0
5 - 1
9 - 2
13 - 3
17 - 4
--
3 - 0
11 - 1
19 - 2
27 - 3
35 - 4
--
7 - 0
23 - 1
39 - 2
55 - 3
71 - 4
--
15 - 0
47 - 1
79 - 2
111 - 3
143 - 4
--
31 - 0
95 - 1
159 - 2
223 - 3
287 - 4
```

ps. I think that the even number of stones are useless. I submitted a code with grundy values of even number of stones = 0 and it passed. Dunno why tho. Any explanation would be appreciated. :D

***

{% include disqus.html %}
