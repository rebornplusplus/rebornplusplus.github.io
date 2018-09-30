---
layout: default
---

<div style="text-align: right; font-style: oblique;">
  Roses are red<br/>
  Violates are blue<br/>
  I wish 'flow' was<br/>
  pronounced as 'floo'.<br/>
  <br/>
  Comrade Mo (1993-)
</div>

# Faced Flow
_Sept 26 2018 1306_

Recently, I took on flow problems. For most of them, I was unable to find a complete solution. But I liked some tricks/solutions of some problems. This page is simply about noting those problems and those tricks.

<details>
  <summary>
    Edge demands / Flow lowerbound<br/>
    <a href="http://lightoj.com/volume_showproblem.php?problem=1367">LightOJ 1367 - Pizza and Inner Peace</a><br/>
    <a href="https://codeforces.com/problemset/problem/704/D">Codeforces 704D - Captain America</a>
  </summary>
  <br>
  In the given graph, a number of flow needs to be passed at least through edges. This value of minimum flow varies depending on edges. This is a good note solving this problem: <a href="http://jeffe.cs.illinois.edu/teaching/algorithms/notes/25-maxflowext.pdf">#</a>
</details>

<hr/>

<details>
  <summary>
    Flow between intervals, Interval compressing<br/>
    <a href="https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2108">UVa 11167 - Monkeys in the Emei Mountain</a><br/>
    <a href="http://lightoj.com/volume_showproblem.php?problem=1350">LightOJ 1350 - Aladdin and the Grand Feast</a>
  </summary>
  <br/>

  Both problems are quite the same. The UVa Monkeys:

  <blockquote>
    Xuexue is a pretty monkey living in the Emei mountain. She is extremely thirsty during time 2 and
    time 9 everyday, so she must drink 2 units water during this period. She may drink water more than
    once, as long as the total amount of water she drinks is exactly 2 - she never drinks more than she
    needs. Xuexue drinks 1 unit water in one time unit, so she may drinks from time 2 to time 4, or from
    3 to 5, . . ., or from 7 to 9, or even drinks twice: first from 2 to 3, then from 8 to 9. But she can’t drink
    from 1 to 3 since she’s not thirsty at time 1, and she can’t drink from 8 to 10, since she must finish at
    time 9.
    <br/><br/>
    There are many monkeys like Xuexue: we use a triple (v, a, b) to describe a monkey who is thirsty
    during time a and b, and must drink exactly v units of water during that period. Every monkey drinks
    at the same speed (i.e. one unit water per unit time).
    <br/><br/>
    Unfortunately, people keep on doing something bad on the environment in Emei Mountain. Eventually,
    there are only one unpolluted places for monkeys to drink. Further more, the place is so small
    that at most m monkeys can drink water together. Monkeys like to help each other, so they want to
    find a way to satisfy all the monkeys’ need. Could you help them?
  </blockquote>

  I think the solution is best explained <a href="https://abitofcs.blogspot.com/2014/12/uva-11167-monkeys-in-emei-mountain.html">here</a>.

  <blockquote>
    A pretty tough maxflow problem. Oh yes, this is a bipartite matching problem between N monkeys and 50000 time intervals. The simplest way to think about this problem is to have N nodes representing monkeys, 50000 nodes representing time intervals, and two nodes S and T which are source and sink respectively. A monkey has to drink v times, hence we add an edge between S and that monkey with capacity v. This monkey can drink from time interval s to t, so we add an edge to each time interval from s to t by capacity 1 each. Finally, each time interval can only be shared between M monkeys, so for each time interval we add an edge to T with capacity M. The maximum flow from S to T will give us the maximum bipartite matching between the monkeys and the time intervals. If this maximum flow exactly equals to the total times all monkeys have to drink, we have found a valid matching.
    <br/><br/>
    However, that is only half of the story. If we implement it directly using 50000 time intervals, we are faced with a huge running time (since it is O(VE2), with V at least 50000 and E is O(V2), with best case running time of O(V2), still too big). Hence we need to consider the time intervals in a more compressed manner. The easiest way to do this is by breaking the intervals (s,t) into smaller intervals only if there are intersections with other intervals. (E.g., if we have monkey 1 drinking from interval (3, 7), and monkey 2 drinking from interval (4, 12), we can break the intervals into (3, 4), (4, 7), and (7, 12) ). What is the bound of the number of intervals in the end? We can think of this incrementally, in each addition of monkey, we will have to break at most two existing interval, introducing 2 new interval segments. Hence in total we will have O(N) intervals. Thus we have pushed V to O(N). :D
  <br/><br/>  
    The last thing needed is a careful implementation and a strong heart to face several WAs..
  </blockquote>

  <script src="https://pastebin.com/embed_js/HWiw3gkK">Solution of LightOJ 1350</script>
</details>
