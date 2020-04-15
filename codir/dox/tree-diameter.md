---
layout: default
---

{% include head.html %}

# Queries on Tree Diameter
_Apr 15, 2020_

The diameter of the tree is the longest path in it. You are given a tree with a bunch of queries. Each query changes the weight of an edge and asks to output the diameter right after it. No offline processings allowed.

This problem appeared in CEOI 2019 and a CF round as a Div1-C. While there exist some solution concerning HLDs and what not, there's a simple, yet good observation and tricks to play here. Let's consider the euler tour traversal of the tree. Let's denote $s(u)$ as the index of first occurrance of $u$ in the traversal array and $t(idx)$ as the node in $idx$ position. Also let $l(u)$ be the level for a node $u$. For a path $u - v$, the lca should be the one with minimal $l(w)$ such that for a $idx$ in $[s(u), s(v)]$, $t(idx) = w$ considering $s(u) \leq s(v)$. Quite simply, the node with the minimal level in this range.

So, the path length should be $f(u, v) = l(u) + l(v) - \min\limits_{s(u) \leq idx \leq s(v)} l(t(idx))$. Now, for the diameter, it should be the longest path. Hence the diameter is: $\max\limits_{u, v \in V(G)} f(u, v) = \max\limits_{u, v \in V(G)} \\{ l(u) + l(v) - \min\limits_{s(u) \leq idx \leq s(v)} l(t(idx)) \\} $.

The only crucial part to this is figuring out how to maintain the query result. We can store the following for each segment:
- max $l(u)$
- max $-2 l(w)$
- max $l(u) - 2l(w)$
- max $-2l(w) + l(v)$
- max $l(u) - 2l(w) + l(v)$.

The last one would be our diameter in a segment of nodes. About the update, it boils down to changing the levels of a few nodes in a segment which can be done with lazy.

To do:
+ [CF 1192B](http://codeforces.com/contest/1192/problem/B)
+ [CF 1149C](https://codeforces.com/contest/1149/problem/C)
