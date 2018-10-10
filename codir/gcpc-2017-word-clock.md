---
layout: default
---

# GCPC 2017 - Word Clock (J)
_Oct 10 2018 0916_

Given a set S of at most 18 words and a rectangular grid, fill the grid with letters such that every word occurs in the grid. 18x18 grid at most, 18 words of highest 18 characters. [Problem Statement](https://codeforces.com/gym/101873/attachments/download/7413/20172018-acmicpc-german-collegiate-programming-contest-gcpc-2017-en.pdf)

### Solution

From [Editorial](http://gcpc.nwerc.eu/outlines_2017.pdf)
> Use dynamic programming: for S' ⊆ S and s ∈ S' let
> 
> f (S' ,s) = the earliest possible end position (row,column) of a text containing all the words from S' and ending in s.
> - A solution exists if and only if one of the positions f (S,s) still lies in the grid.
> - To reconstruct the solution one needs to keep track of the best
predecessor states while building the DP table
> - From the current state (S',s) try to append every t ∈/ S' to the text, maximizing overlap between s and t.<br/>
> If t doesn’t fit in the current line, start a new line.<br/>
> The new state is (S' ∪ {t},t).
> - The maximal overlaps between words can be precalculated. Possible pitfall: some words may be substrings of other words.
> - Time complexity: O(n^2 2^n)

Implementation
<iframe src="https://pastebin.com/embed_iframe/8nXmuWwg" style="border:none;width:100%;height:360px;"></iframe>

***

{% include disqus.html %}
