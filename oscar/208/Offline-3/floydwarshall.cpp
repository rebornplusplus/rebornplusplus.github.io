#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 507;
int g[N][N];
int par[N][N];

bool floydwarshall(int n) {
    #define rep(i, n) for(int i=1; i<=n; ++i)
    rep(k, n) {
        rep(i, n) {
            rep(j, n) {
                if(g[i][j] > g[i][k] + g[k][j] and g[i][k] < INF and g[k][j] < INF) {
                    g[i][j] = g[i][k] + g[k][j];
                    par[i][j] = par[k][j];
                }
            }
        }
    }

    rep(i, n) if(g[i][i] < 0) return false;
    return true;
}

int main() {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    memset(g, INF, sizeof g);
    memset(par, -1, sizeof par);
    for(int i=1; i<=n; ++i) g[i][i] = 0;
    for(int i=0; i<m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if(g[u][v] > w) g[u][v] = w;
        par[u][v] = u;
    }

    bool negcy = !floydwarshall(n);
    printf("Negative Cycle: %s\n", negcy ? "Yes" : "No");

    if(!negcy) {
        puts("All pair shortest path:");
        for(int i=1; i<=n; ++i) {
            for(int j=1; j<=n; ++j) {
                if(g[i][j] != INF) printf("%3d ", g[i][j]);
                else printf("INF ");
            }
            putchar('\n');
        }
        puts("Predecessor Matrix:");
        for(int i=1; i<=n; ++i) {
            for(int j=1; j<=n; ++j) {
                printf("%3d ", par[i][j]);
            }
            putchar('\n');
        }
    }

    return 0;
}
