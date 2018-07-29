---
layout: default
---

# LightOJ 1401 - No More Tic-tac-toe
_Jul 29 2018 2302_

[Here](http://lightoj.com/volume_showproblem.php?problem=1401)'s another beautiful game :D This is really beautiful and !boring like tic-tac-toe _-

### Solution

Okay, given a current state how do we reckon who's gonna be the winner! Um, that's kinda obvious if you solved loj 1229 :3 Tell me this. If you're given a blank board of some particular length, would you be able to find the winner? If you can, then I am gonna throw an almost blank board with the only `X` or `O` at the very last cell or the very first cell. Could you manage that? If that too is ok, then what about `X` or `O`s at both the ends?

Now to the main problem. Notice that we can only put `X` or `O` in the dotted cells. And those dotted cells form an interval of some particular length `len` let's say. And that length has some varying properties too! The adjacent cells! So, we keep 3 states for an interval, the length, the character at left, the character at right. Then we just find the grundy values and it's easy peasy. 

Do notice that you're not told who's move is now at the current state of the game. But you have to find whether Alice won or not.

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 107;
int sgn[N][3][3];	// length of chunk, left surrounding char, right surrounding char ( '.' = 0 )
bool vis[N+N];

void grrr() {
	for(int l=0; l<3; ++l) for(int r=0; r<3; ++r) sgn[0][l][r] = 0, sgn[1][l][r] = 1;
	sgn[1][1][2] = 0, sgn[1][2][1] = 0;
	for(int i=2; i<N; ++i) {
		for(int l=0; l<3; ++l) {
			for(int r=0; r<3; ++r) {
				memset(vis, false, sizeof vis);
				for(int j=2; j<i; ++j) {
					int flen = j-1, slen = i-j;
					int xval = sgn[flen][l][1] ^ sgn[slen][1][r];
					int oval = sgn[flen][l][2] ^ sgn[slen][2][r];
					vis[xval] = true, vis[oval] = true;
				}
				// for first place
				int xc1 = (l==0 ? 1 : 3-l), oc1 = (l==0 ? 2 : 3-l);
				int xval = sgn[0][l][xc1] ^ sgn[i-1][xc1][r];
				int oval = sgn[0][l][oc1] ^ sgn[i-1][oc1][r];
				vis[xval] = true, vis[oval] = true;
				// for last place
				int xc2 = (r==0 ? 1 : 3-r), oc2 = (r==0 ? 2 : 3-r);
				xval = sgn[i-1][l][xc2] ^ sgn[0][xc2][r];
				oval = sgn[i-1][l][oc2] ^ sgn[0][oc2][r];
				vis[xval] = true, vis[oval] = true;

				int val = 0;
				while(vis[val]) ++val;
				sgn[i][l][r] = val;
				// if(i < 5) cout << i << " " << l << " " << r << ": " << val << "\n";
			}
		}
	}
}

inline bool shakalakaboomboom(string &s) {
	int past = -1, pc = 0;
	int xorsum = 0, cnt = 0;
	for(int i=0; i<(int) s.size(); ++i) {
		if(s[i] == 'X') {
			int len = i-past-1;
			xorsum ^= sgn[len][pc][1];
			past = i;
			pc = 1;
			++cnt;
		}
		else if(s[i] == 'O') {
			int len = i-past-1;
			xorsum ^= sgn[len][pc][2];
			past = i;
			pc = 2;
			++cnt;
		}
	}
	int len = (int) s.size() - past-1;
	xorsum ^= sgn[len][pc][0];
	return (cnt % 2 ? !(xorsum) : (xorsum));
}

int main() {
	grrr();

	int t, tc=0;
	cin >> t;
	while(t--) {
		string s;
		cin >> s;
		cout << "Case " << ++tc << ": " << (shakalakaboomboom(s) ? "Yes" : "No") << "\n";
	}
	return 0;
}
```
By the way, do you read books? Did you read "To Kill A Mockingbird"? How much would you rate it out of 5?

***

{% include disqus.html %}
