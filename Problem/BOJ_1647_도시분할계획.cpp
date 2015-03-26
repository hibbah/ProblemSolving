/******************************************************************************

2015.03.26

https://www.acmicpc.net/problem/1647

- input : [ G(V, E) ]. weigted & connected & un-directed Graph
- output : minimum "Cost"
		"cost" : sum of edge.weight when split Graph to Two connected Graph

- solution : kruscal algorithm (get MST)
- complexity : O(ElogE)

******************************************************************************/

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> VI;

#define MP make_pair
#define REP(v, repeat) for(int v=0; v<(repeat); ++v)
#define REPD(v, repeat) for(int v=(repeat)-1; v>=0; --v)
#define FOR(v, pos, end) for(int v=(pos); v<=(end); ++v)
#define FORD(v, pos, end) for(int v=(pos); v>=(end); --v)

class Edge
{
public:
	int a, b, w;

	Edge() {}
	Edge(const int & _a, const int & _b, const int &_w) :a(_a), b(_b), w(_w) {}

	bool operator < (const Edge & e) const
	{
		return w < e.w;
	}
};

// UnionFind (Disjoint set)
class UF
{
public:
	VI rank, parent, size;

	UF() {}
	UF(const int n) : rank(n, 0), parent(n), size(n, 1)
	{
		REP(i, n) parent[i] = i;
	}

	// return root of a
	int find(const int & a)
	{
		if (a == parent[a]) return a;
		return parent[a] = find(parent[a]);
	}

	// return merge set size
	int merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return 0;
		if (rank[a] < rank[b]) swap(a, b);
		if (rank[a] == rank[b]) ++rank[a];
		parent[b] = a;
		size[a] += size[b];
		return size[a];
	}
};

int n, m;
vector <Edge> edge;

// make MST (minimum spanning Tree)
int minCost()
{
	UF uf(n + 1);
	sort(edge.begin(), edge.end());
	
	int ret = 0;
	REP(i, edge.size())
	{
		const int & a = edge[i].a;
		const int & b = edge[i].b;

		int size = uf.merge(a, b); // treesize
		if (size == n) break; // complite MST
		if (size != 0) ret += edge[i].w; // add cost
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif
	
	scanf("%d%d", &n, &m);
	edge = vector<Edge>(m);
	REP(i, m)
	{
		int a, b, w;
		scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].w);
	}
	printf("%d\n", minCost());

	return 0;
}
