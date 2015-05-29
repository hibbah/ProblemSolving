/**********************************************************************************

2015.05.27

https://www.acmicpc.net/problem/2463/

- title : Cost
(KOI2011 HighSchool problem 4)

- input : bi-directional weighted Graph(V, E). (1<=|V|<=100,000. 1<=|M|<=100,000)
- output :
	1. Define Cost(u, v) == sum of edge that the weight of the smallest until there is no path between the U and V
	2. for all vertex pair Cost(u, v) that satisfied (u<v) in graph. print the sum of Cost(u, v)
- issue : When was the path that disappears between the U and V ?
- solution :
	calculate Maximum Spanning Tree.
	Each time to remove the Edge one is the calculation Cost(U, V).
	using UnionFind Structure
- time complexity : MlogM ( == sorting time )

**********************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long ull;
typedef pair<int, int> PI;
typedef vector<int> VI;
typedef pair<ull, PI> EDGE;
#define MP make_pair

const ull MOD = 1000000000;

// UnionFind structure based on array(tree)
class UF
{
public:
	VI parent, rank;

	UF() {}
	UF(const int n) : parent(n), rank(n, 0)
	{
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}

	int find(const int & a)
	{
		if (a == parent[a]) return a;
		return parent[a] = find(parent[a]);
	}

	bool merge(int a, int b)
	{
		a = find(a), b = find(b);
		if (a == b) return false;
		if (rank[a] > rank[b]) swap(a, b);
		if (rank[a] == rank[b]) ++rank[b];
		parent[a] = b;
		return true;
	}
};

int n, m;
vector <EDGE> edge;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d", &n, &m);
	vector <ull> compSize(n + 1, 1);
	edge = vector <EDGE>(m);
	UF uf(n + 1);

	ull sum = 0;
	for (int i = 0; i < edge.size(); ++i)
	{
		int a, b; ull w;
		scanf("%d %d %llu", &a, &b, &w);
		edge[i] = MP(w, MP(a, b));
		sum += w;
		sum %= MOD;
	}
	sort(edge.rbegin(), edge.rend()); // sorting descending order

	ull ret = 0;
	for (int i = 0; i < edge.size(); ++i)
	{
		const int & a = uf.find(edge[i].second.first);
		const int & b = uf.find(edge[i].second.second);

		if (uf.merge(a, b)) // if 'a' and 'b' are of different set
		{
			// add all Cost Cost(X, a), Cost(a, X), Cost(X, b), Cost(b, X)
			ret += (sum * compSize[a] * compSize[b]);
			ret %= MOD;
			compSize[a] = compSize[b] = (compSize[a] + compSize[b]);
		}
		sum = ((MOD + sum - edge[i].first) % MOD);
	}
	printf("%llu\n", ret);

	return 0;
}