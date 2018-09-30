---
layout: default
---

# Faced Flow
_Sept 26 2018 1306_

Recently, I took on flow problems. For most of them, I was unable to find a complete solution. But I liked some tricks/solutions of some problems. This page is simply about noting those problems and those tricks.

[UVa 11167 - Monkeys in the Emei Mountain](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2108) <br/>
[LightOJ 1350 - Aladdin and the Grand Feast](http://lightoj.com/volume_showproblem.php?problem=1350)

Both problems are quite the same. The UVa Monkeys:

> Xuexue is a pretty monkey living in the Emei mountain. She is extremely thirsty during time 2 and
time 9 everyday, so she must drink 2 units water during this period. She may drink water more than
once, as long as the total amount of water she drinks is exactly 2 - she never drinks more than she
needs. Xuexue drinks 1 unit water in one time unit, so she may drinks from time 2 to time 4, or from
3 to 5, . . ., or from 7 to 9, or even drinks twice: first from 2 to 3, then from 8 to 9. But she can’t drink
from 1 to 3 since she’s not thirsty at time 1, and she can’t drink from 8 to 10, since she must finish at
time 9.
> 
> There are many monkeys like Xuexue: we use a triple (v, a, b) to describe a monkey who is thirsty
during time a and b, and must drink exactly v units of water during that period. Every monkey drinks
at the same speed (i.e. one unit water per unit time).
> 
> Unfortunately, people keep on doing something bad on the environment in Emei Mountain. Eventually,
there are only one unpolluted places for monkeys to drink. Further more, the place is so small
that at most m monkeys can drink water together. Monkeys like to help each other, so they want to
find a way to satisfy all the monkeys’ need. Could you help them?

I think the solution is best explained [here](https://abitofcs.blogspot.com/2014/12/uva-11167-monkeys-in-emei-mountain.html).

> A pretty tough maxflow problem. Oh yes, this is a bipartite matching problem between N monkeys and 50000 time intervals. The simplest way to think about this problem is to have N nodes representing monkeys, 50000 nodes representing time intervals, and two nodes S and T which are source and sink respectively. A monkey has to drink v times, hence we add an edge between S and that monkey with capacity v. This monkey can drink from time interval s to t, so we add an edge to each time interval from s to t by capacity 1 each. Finally, each time interval can only be shared between M monkeys, so for each time interval we add an edge to T with capacity M. The maximum flow from S to T will give us the maximum bipartite matching between the monkeys and the time intervals. If this maximum flow exactly equals to the total times all monkeys have to drink, we have found a valid matching.
> 
> However, that is only half of the story. If we implement it directly using 50000 time intervals, we are faced with a huge running time (since it is O(VE2), with V at least 50000 and E is O(V2), with best case running time of O(V2), still too big). Hence we need to consider the time intervals in a more compressed manner. The easiest way to do this is by breaking the intervals (s,t) into smaller intervals only if there are intersections with other intervals. (E.g., if we have monkey 1 drinking from interval (3, 7), and monkey 2 drinking from interval (4, 12), we can break the intervals into (3, 4), (4, 7), and (7, 12) ). What is the bound of the number of intervals in the end? We can think of this incrementally, in each addition of monkey, we will have to break at most two existing interval, introducing 2 new interval segments. Hence in total we will have O(N) intervals. Thus we have pushed V to O(N). :D
> 
> The last thing needed is a careful implementation and a strong heart to face several WAs..

<details>
  <summary>My Code for LightOJ 1350</summary>
  <br/>

<pre>

const int MAX_E=25000;	// 60003;
const int MAX_V=160;	// 5003;
int ver[MAX_E],cap[MAX_E],nx[MAX_E],last[MAX_V],ds[MAX_V],st[MAX_V],now[MAX_V],edge_count,S,T;

void reset()
{
	memset(nx,-1,sizeof(nx));
	memset(last,-1,sizeof(last));
	edge_count=0;
}
inline void addedge(const int v,const int w,const int capacity,const int reverse_capacity)
{
	ver[edge_count]=w; cap[edge_count]=capacity; nx[edge_count]=last[v]; last[v]=edge_count++;
	ver[edge_count]=v; cap[edge_count]=reverse_capacity; nx[edge_count]=last[w]; last[w]=edge_count++;
}
bool bfs()
{
	memset(ds,-1,sizeof(ds));
	int a,b;
	a=b=0;
	st[0]=T;
	ds[T]=0;
	while (a<=b)
	{
		int v=st[a++];
		for (int w=last[v];w>=0;w=nx[w])
		{
			if (cap[w^1]>0 && ds[ver[w]]==-1)
			{
				st[++b]=ver[w];
				ds[ver[w]]=ds[v]+1;
			}
		}
	}
	return ds[S]>=0;
}
int dfs(int v,int cur)
{
	if (v==T) return cur;
	for (int &w=now[v];w>=0;w=nx[w])
	{
		if (cap[w]>0 && ds[ver[w]]==ds[v]-1)
		{
			int d=dfs(ver[w],min(cur,cap[w]));
			if (d)
			{
				cap[w]-=d;
				cap[w^1]+=d;
				return d;
			}
		}
	}
	return 0;
}
long long flow()
{
	long long res=0;
	while (bfs())
	{
		for (int i=0;i<MAX_V;i++) now[i]=last[i];
		while (1)
		{
			int tf=dfs(S,INF);
			res+=tf;
			if (!tf) break;
		}
	}
	return res;
}

const int N = 55, M = 10005, TC = 30;
int n, table, chair, e, ni, seats;
int a[N], d[N], f[N];
vector< pii > intervals;
int wedge[MAX_V][MAX_V];	// which edge
char who[M][TC];

void kompress() {
	vector< pii > v;
	for(int i=1; i<=n; ++i) {
		v.push_back(mp(a[i], 1));
		v.push_back(mp(d[i], -1));
	}
	sort(v.begin(), v.end());

	intervals.clear();
	int carry = 0;
	for(int i=1; i<(int) v.size(); ++i) {
		carry += v[i-1].ss;
		if(carry <= 0) continue;
		if(v[i-1].ff != v[i].ff) intervals.push_back(mp(v[i-1].ff, v[i].ff));
	}
}

inline bool intersex(pii &p, pii &q) {
	if(p.ff >= q.ss or p.ss <= q.ff) return false;
	return true;
}

bool fuk() {
	memset(wedge, -1, sizeof wedge);
	reset();
	S = 0, T = n+ni+1;
	ll req = 0;
	for(int i=0; i<ni; ++i) {
		int v = n+i+1;
		int len = intervals[i].ss - intervals[i].ff;
		for(int j=1; j<=n; ++j) {
			pii temp = mp(a[j], d[j]);
			if(!intersex(temp, intervals[i])) continue;
			wedge[j][v] = edge_count;
			addedge(j, v, len, 0);
		}
		addedge(v, T, seats*len, 0);
	}
	for(int i=1; i<=n; ++i) {
		req += f[i];
		addedge(S, i, f[i], 0);
	}
	return (req == flow());
}

inline char fuker(int id) {
	if(id <= 26) return ('a'+id-1);
	id -= 26;
	return ('A'+id-1);
}

void hookem() {
	for(int i=1; i<e; ++i) for(int j=1; j<=seats; ++j) who[i][j] = '.';
	for(int i=0; i<ni; ++i) {
		int v = n+i+1;
		int len = intervals[i].ss - intervals[i].ff;
		int cur = 0;
		for(int j=1; j<=n; ++j) {
			if(wedge[j][v] == -1) continue;
			int fl = len - cap[wedge[j][v]];
			while(fl--) {
				int col = cur/len;
				int row = cur - col*len;
				row += intervals[i].ff;
				col += 1;
				who[row][col] = fuker(j);
				++cur;
			}
		}
	}
}

void printem() {
	for(int i=1; i<e; ++i) {
		int temp = table;
		for(int j=1; j<=seats; ++j) {
			putchar(who[i][j]);
			if(j % chair == 0) {
				--temp;
				if(temp > 0) putchar('|');
			}
		}
		putchar('\n');
	}
}

int main() {
	int t, tc=0;
	scanf("%d", &t);

	while(t--) {
		scanf("%d %d %d %d", &n, &table, &chair, &e);
		for(int i=1; i<=n; ++i) scanf("%d %d %d", a+i, d+i, f+i);

		kompress();
		ni = intervals.size(), seats = table*chair;
		bool ok = fuk();
		
		printf("Case %d: %s\n", ++tc, (ok ? "Yes" : "No"));
		if(!ok) continue;
		hookem();
		printem();
	}

	return 0;
}
</pre>
</details>
