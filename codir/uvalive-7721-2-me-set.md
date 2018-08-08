---
layout: default
---

# UVaLive 7721 - 2-ME Set
_Aug 08 2018 1629_

You're given some numbers. You have to calculate the number of such multisets where any two numbers in a multiset would have AND value equals to zero. The maximum value of the numbers can be 20000 as well as the number of such numbers. [Problem Statement](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5743)

### Solution

Notice that the value can be at most 20000, which may have at most 15 bits in binary representation. As the and value have to be zero, we store a dp array where dp[x] will be the number of such multisets where the elements will have such bit representation such that their AND values are ZERO and OR/XOR values will be x. Basically it's subset dp.

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000000+7;
const int N = (1<<15);
int cnt[N+7], a[N+7];
long long dp[N+7];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t, tc=0;
    cin >> t;
    while(t--) {
        memset(cnt, 0, sizeof cnt);
        int n;
        cin >> n;
        for(int i=0, x; i<n; ++i) {
            cin >> x;
            ++cnt[x];
        }
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        long long res = 0;
        for(int mask=1; mask<N; ++mask) {
            for(int i=mask; i; i=((i-1)&mask)) {
                if((i ^ mask) > i) continue;
                dp[mask] += (dp[i^mask] * cnt[i]);
                dp[mask] %= MOD;
            }
            res += dp[mask];
            res %= MOD;
        }
        res = (res -n + MOD) % MOD;
        cout << "Case #" << ++tc << ": " << res << "\n";
    }
    return 0;
}
```

***

{% include disqus.html %}
