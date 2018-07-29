---
layout: default
---

# LightOJ 1229 - Treblecross
_Jul 29 2018 1037_

This is a good game! Read it [here](http://lightoj.com/volume_showproblem.php?problem=1229).

Did you read it clearly? Understood? Do you understand these test cases below?

Input
```
2
.....XX
.X.X.X.........X...
```
Output
```
Case 1: 5
Case 2: 3 5
```

### Solution

Quite frankly, I looked up the solution as I was just learning game theory and I am a noob as always. I think that nobody could explain better than the way explained [here](http://lbv-pc.blogspot.com/2012/07/treblecross.html).

My shitty implementation:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 207;
int sgn[N];
bool vis[N];

void grrr() {
	sgn[0] = 0;
	for(int i=1; i<N; ++i) {
		memset(vis, false, sizeof vis);
		for(int j=1; j<=i; ++j) {
			int flen = max(0, j-3);
			int slen = max(0, i-j-2);
			int val = sgn[flen] ^ sgn[slen];
			vis[val] = true;
		}
		int val = 0;
		while(vis[val]) ++val;
		sgn[i] = val;
	}
}

inline int check(string &s) {
	for(int i=3; i+3<(int) s.size(); ++i) {
		if(s[i] == 'X') continue;
		if(s[i-1] == 'X' and s[i-2] == 'X') return i;
		if(s[i-1] == 'X' and s[i+1] == 'X') return i;
		if(s[i+1] == 'X' and s[i+2] == 'X') return i;
	}
	return -1;
}

inline void printpositions(string &s) {
	for(int i=3; i+3<(int) s.size(); ++i) {
		if(s[i] == 'X') continue;
		if(s[i-1] == 'X' and s[i-2] == 'X') {
			cout << " " << i-2;
			continue;
		}
		if(s[i-1] == 'X' and s[i+1] == 'X') {
			cout << " " << i-2;
			continue;
		}
		if(s[i+1] == 'X' and s[i+2] == 'X') {
			cout << " " << i-2;
			continue;
		}
	}
	cout << '\n';
}

inline int fuck(string &s) {
	int past = -1, ret = 0;
	for(int i=0; i<(int) s.size(); ++i) {
		if(s[i] == 'X') {
			int len = max(0, i-1-past-4);
			ret ^= sgn[len];
			past = i;
		}
	}
	return ret;
}

int main() {
	grrr();

	int t, tc=0;
	cin >> t;
	while(t--) {
		string s;
		cin >> s;
		s = "X.." + s + "..X";
		int pos = check(s);
		if(pos != -1) {
			cout << "Case " << ++tc << ":";
			printpositions(s);
			continue;
		}
		if(fuck(s) == 0) {
			cout << "Case " << ++tc << ": " << 0 << "\n";
			continue;
		}
		cout << "Case " << ++tc << ":";
		for(int i=3; i+3<(int) s.size(); ++i) {
			if(s[i] == 'X') continue;
			s[i] = 'X';
			if(fuck(s) == 0 and check(s) == -1) cout << " " << i-2;
			s[i] = '.';
		}
		cout << "\n";
	}

	return 0;
}
```

***

{% include disqus.html %}
