---
layout: default
---

# LightOJ Random Problem Extractor
_Aug 14 2018 0006_

Made somewhat of a `random to-solve teller` for LightOJ. It tells you to solve a problem given the range of solution count you prefer. Run this code:

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 2000000000LL;
vector< pair<int, int> > v;

void read() {
	ifstream in("to-solve");
	if(!in) {
		cerr << "Error reading data\n";
		exit(1);
	}
	
	v.clear();
	int who, cnt;
	while(in >> who >> cnt) {
		v.push_back(make_pair(cnt, who));
	}
	sort(v.begin(), v.end());
	in.close();
}

void write() {
	ofstream out("to-solve");
	if(!out) {
		cerr << "Error writing data\n";
		exit(1);
	}

	for(int i=0; i<(int) v.size(); ++i) swap(v[i].first, v[i].second);
	sort(v.begin(), v.end());
	for(auto x : v) out << x.first << " " << x.second << "\n";
	out.close();
}

void update(int pid) {
	for(auto it=v.begin(); it!=v.end(); it++) {
		if(it->second == pid) {
			v.erase(it);
			return ;
		}
	}
}

void print() {
	cout << "\n";
	cout << "LiteOJ Random Problem Extractor" << "\n";
	cout << "For a particular solution range" << "\n";
	cout << "\n";
	cout << "  select_range  update_solved  " << "\n";
}

int getrand(int l, int r) {
	int lpt = (int) (lower_bound(v.begin(), v.end(), make_pair(l, 0)) - v.begin());
	int rpt = (int) (upper_bound(v.begin(), v.end(), make_pair(r, INF)) - v.begin()) - 1;
	int len = rpt - lpt + 1;
	int who = (rand() % len) + lpt;
	int ret = v[who].second;
	return ret;
}

int main() {
	read();
	srand(time(NULL));

	print();
	string s;
	cin >> s;
	if(s == "select_range") {
		int l, r;
		cin >> l >> r;
		int pid = getrand(l, r);
		cout << "Solve LiteOJ " << pid << "\n";
		cout << "http://lightoj.com/volume_showproblem.php?problem=" << pid << "\n";
	}
	else if(s == "update_solved") {
		int pid;
		cin >> pid;
		update(pid);
	}
	
	write();
	return 0;
}
```

Make sure that you have a file named `to-solve` where are the data for problems and their solution count. In each row there are two integers. First one is the problem id, second is the count of unique accepted solutions. My `to-solve` file looks like this:

```
1073 200
1084 298
1086 318
1092 198
1106 139
1126 262
1147 244
1158 305
1173 244
1180 129
1193 188
1194 128
1223 134
1228 134
1230 127
1246 171
1252 113
1264 117
1270 99
1277 135
1295 119
1298 227
1299 134
1302 98
1312 48
1316 219
1329 69
1335 45
1342 92
1345 64
1351 47
1352 77
1360 199
1362 10
1365 42
1376 8
1381 64
1394 97
1399 46
1416 38
1420 137
1431 0
```

Hope it helps!
