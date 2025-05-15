# Insta-Influencer-Fest
Covers the concepts of Graphs like Strongly Connected Components, Cyclic Dependencies, Topological Sorting.

## Background

In March 2025, following the success of Shaastra, IIT Madras is hosting its first InstaInfluencer Fest. This event features GenZ influencers, content creators, and fans across a wide array of events: viral dance-offs, meme contests, podcast sessions, and live-streaming challenges.

Each event has a set of dependencies — for instance, the final round of an event can only happen after its preliminaries. Some influencers have demanded additional constraints, creating complex dependencies. These constraints form a directed graph where:
- Each node represents an event.
- Each directed edge `u → v` means event `u` must occur before event `v`.
- Each event also has a "hype score" based on its popularity.

## Objective

Build a system that answers various queries on the event graph:
1. Detect cycles caused by conflicting dependencies.
2. Find strongly connected components (SCCs) and identify the largest group.
3. Return a valid topological sort of the events (if possible).
4. Compute the maximum achievable hype score along any valid path.

---
## Input Format
1. The first line contains two integers N and M, representing the number of events and dependencies respectively.
2. The second line contains N integers h1,h2,,hN, where hi is the hype score of event i.
3. The next M lines each contain two integers u and v, indicating that event u must precede event v.
4. The next line contains an integer Q, representing the number of queries.
5. The next Q lines contain one integer per line indicating query type (1, 2, 3 or 4).


- `N`: Number of events (1 ≤ N ≤ 10^5)
- `M`: Number of dependency edges (1 ≤ M ≤ 10^5)
- `hi`: Hype score of the i-th event (1 ≤ hi ≤ 10^4)
- `ui vi`: Directed edge from event `u` to event `v`
- `Q`: Number of queries (1 ≤ Q ≤ 10^5)
- `qi`: Type of query (1, 2, 3, or 4)

---

## Query Types

| Query Type | Description |
|------------|-------------|
| 1          | Check for cycles in the graph. Output `YES` if any cycle exists, otherwise `NO`. |
| 2          | Find the number of SCCs and the size of the largest SCC. |
| 3          | Print a valid topological order of events. If multiple orders are valid, choose lexicographically smallest one among all possibilities. If cycle exists, output `NO`. |
| 4          | Compute the maximum hype score from a valid event path. Collapse each SCC into a node and sum their hype scores, then compute the longest path hype sum on the DAG. |

---

## Output Format

- For **Query 1**: Output `YES` or `NO`
- For **Query 2**: Output two integers: number of SCCs and the size of the largest SCC
- For **Query 3**: Output the topological order as space-separated integers, or `NO` if not possible
- For **Query 4**: Output one integer — the maximum hype score on a valid path

---

## Sample Test Case 1

**Input**
```
4 4
10 20 30 40
1 2
2 3
3 1
3 4
4
1
2
3
4
```
**Output**
```
YES
2 3
NO
100
```
```
Derived Classes
class isCycle: Implements cycle detection using DFS

class indepComponent: Implements Kosaraju's algorithm for SCCs

class validOrder: Uses Kahn's algorithm + priority queue for lexicographically smallest topological sort

class maxHype: Collapses SCCs into DAG and uses DP on DAG to get max hype score

Optional
Comparator functor can be defined for priority queue in topological sort
```

 




