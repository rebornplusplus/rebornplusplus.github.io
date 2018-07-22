---
layout: default
---

# LightOJ 1364 - Expected Cards
_Jul 22 2018 0736_

The problem goes like this: <br/>
"Taha has got a standard deck of cards with him. In addition to the 52 regular ones, there are 2 joker cards. Every regular card has a rank and a suit. The ranks in ascending order are: A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q and K. The suit of a card can be clubs, diamonds, hearts or spades. That means there are 13 clubs, 13 diamonds, 13 hearts and 13 spades - which adds up to 52. The joker cards have no ranks or suits.

One day, Sara gave Taha a challenge. First she randomly shuffles the 54 cards and starts placing one card after another, face-up, on a table. What is the expected number of cards Sara has to place so that there are at least C clubs, D diamonds, H hearts and S spades on the table? Whenever a joker card is encountered, Taha has to assign it to some suit so that the expected number of cards to reach the goal is minimized. The decision of assigning the joker card to some suit has to be made instantly (i.e. before Sara puts the next card on the table). Note that the assignments of the two joker cards don't necessarily need to be the same." <br/>
[Full Statement](http://lightoj.com/volume_showproblem.php?problem=1364)

### Solution

It's not complicated to notice that the problem can be solved with dp. States should be how many cards of each type has been used. Only exception is at the jokers. Here you have to store which type does the joker represent. So I kept 4 parameters which represent the number of cards used in the corresponding type. And also 2 another parameter to represent what the first joker is of which type and the second joker is of which.

I think I couldn't make you understand. I am bad at this I know. :3 See the code for now. I think, you'll get confused more less.

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long INF = 2000000000LL;

int cc, dd, hh, ss;
// used amount of c, d, h, s; first joker used to, second joker used to. joker val = 0 means not used
double dp[14][14][14][14][5][5];
bool vis[14][14][14][14][5][5];

double fun(int c, int d, int h, int s, int jok, int joc) {
	int _c = c + (jok == 1) + (joc == 1);
	int _d = d + (jok == 2) + (joc == 2);
	int _h = h + (jok == 3) + (joc == 3);
	int _s = s + (jok == 4) + (joc == 4);
	if(_c >= cc and _d >= dd and _h >= hh and _s >= ss) return 0;
	if(_c + _d + _h + _s == 54) return INF;
	double &ret = dp[c][d][h][s][jok][joc];
	if(vis[c][d][h][s][jok][joc]) return ret;

	ret = 0;
	vis[c][d][h][s][jok][joc] = true;
	int left = 54 - (c+d+h+s + (jok>0) + (joc>0));
	if(c < 13) {
		double p = (double) (13-c) / (double) left;
		ret += p * ( 1 + fun(c+1, d, h, s, jok, joc) );
	}
	if(d < 13) {
		double p = (double) (13-d) / (double) left;
		ret += p * ( 1 + fun(c, d+1, h, s, jok, joc) );
	}
	if(h < 13) {
		double p = (double) (13-h) / (double) left;
		ret += p * ( 1 + fun(c, d, h+1, s, jok, joc) );
	}
	if(s < 13) {
		double p = (double) (13-s) / (double) left;
		ret += p * ( 1 + fun(c, d, h, s+1, jok, joc) );
	}
	if(!jok) {
		double p = (double) ((!jok) + (!joc)) / (double) left;
		double temp = INF;
		temp = min(temp, fun(c, d, h, s, 1, joc));
		temp = min(temp, fun(c, d, h, s, 2, joc));
		temp = min(temp, fun(c, d, h, s, 3, joc));
		temp = min(temp, fun(c, d, h, s, 4, joc));
		ret += p * (1 + temp);
	}
	else if(!joc) {
		double p = (double) ((!jok) + (!joc)) / (double) left;
		double temp = INF;
		temp = min(temp, fun(c, d, h, s, jok, 1));
		temp = min(temp, fun(c, d, h, s, jok, 2));
		temp = min(temp, fun(c, d, h, s, jok, 3));
		temp = min(temp, fun(c, d, h, s, jok, 4));
		ret += p * (1 + temp);
	}
	return ret;
}

bool isvalid() {
	int extra = 0;
	if(cc > 13) extra += cc-13;
	if(dd > 13) extra += dd-13;
	if(hh > 13) extra += hh-13;
	if(ss > 13) extra += ss-13;
	return (extra <= 2);
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		scanf("%d %d %d %d", &cc, &dd, &hh, &ss);
		printf("Case %d: ", ++tc);
		if(!isvalid()) {
			printf("-1\n");
			continue;
		}

		memset(vis, false, sizeof vis);
		double res = 0;
		res += fun(0, 0, 0, 0, 0, 0);
		printf("%.10lf\n", res);
	}

	return 0;
}
```

This was one hell of a painful implementation. `_-` I messed up while coding this thing that resulted in bugs. :( 

***

{% include disqus.html %}
