---
layout: default
---

# LightOJ 1180 - Software Company
_Aug 14 2018 1654_

A software company is given two projects. Both of them needs to be handed over at the same time. The company has `n` employees. And both the projects are divided into `m` sub-projects. For each employee the time needed to complete a sub-project of both projects are given. Goal is to calculate the minimum time needed to complete both the projects. [Problem Statement](http://lightoj.com/volume_showproblem.php?problem=1180)

# Solution

Run a binary search fixing the time needed to complete both the projects. Now you know for each employee, the doable max amount of sub-projects of `A` fixing the amount of sub-projects to do of type `B`. Keep a `dp[i][j]` which means the maximum number of sub-projects of `B` that can be done while `j` sub-projects of `A` are still to be done and we're currently at employee `i`. If `dp[0][m] >= m` then the time fixed is ok. Answer is the minimum such time.

Code:

```cpp
const int N = 107;
int dp[N][N];
int n, m;
int x[N], y[N];

bool ok(int tym) {
    for(int i=1; i<=m; ++i) dp[n][i] = -INF;
    dp[n][0] = 0;
    for(int i=n-1; i>=0; --i) {
        for(int j=0; j<=m; ++j) {
            dp[i][j] = -INF;
            int max_a = tym / x[i];
            max_a = min(j, max_a);
            for(int k=0; k<=max_a; ++k) {
                int max_b = (tym-k*x[i]) / y[i];
                dp[i][j] = max(dp[i][j], max_b + dp[i+1][j-k]);
            }
        }
    }
    return (dp[0][m] >= m);
}

int main() {
    int t, tc=0;
    scanf("%d", &t);

    while(t--) {
        scanf("%d %d", &n, &m);
        for(int i=0; i<n; ++i) scanf("%d %d", x+i, y+i);

        int lo = 1, hi = 50000;
        while(lo < hi) {
            int mid = (lo + hi) / 2;
            if(ok(mid)) hi = mid;
            else lo = mid + 1;
        }
        printf("Case %d: %d\n", ++tc, hi);
    }

    return 0;
}
```

***

{% include disqus.html %}
