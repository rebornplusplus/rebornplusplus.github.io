---
layout: default
---

# Queries on Tree Diameter
_Apr 15, 2020_

The diameter of the tree is the longest path in it. You are given a tree with a bunch of queries. Each query changes the weight of an edge and asks to output the diameter right after it. No offline processings allowed.

This problem appeared in CEOI 2019 and a CF round as a Div1-C. While there exist some solution concerning HLDs and what not, there's a simple, yet good observation and tricks to play here. Let's consider the euler tour traversal of the tree. Let's denote $s(u)$ as the index of first occurrance of $u$ in the traversal array. For a path $u - v$, the lca should be the one with minimal heights in $[s(u), s(v)]$ considering $s(u) \leq s(v)$.
