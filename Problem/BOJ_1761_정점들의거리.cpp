/******************************************************************************

2015.05.04

https://www.acmicpc.net/problem/1761/

- input : acyclic bi-directional weighted graph (weighted tree). 2<=V<=40,000
- output : for M(<=10,000) query <a, b>, print Distance(a, b)
- solution :
	1. find LCA(Lowest Common Ancestor) using RMQ.
	2. print Depth[a]+Depth[b]-2Depth[LCA]
- time complexity :
	1. depthNumbering(DFS, preOrder traversal) : O(2N)
	2. construct RMQ : O(2N)
	3. calc Distance(a, b) for M query : M * O(log2N)
	=> total complexity : O( MlogN )

******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PI;
typedef vector<int> VI;
typedef vector< vector<PI> > ADJ;
#define MP make_pair

const int INF = 999999999;
int n, m, num = 0;
ADJ adj; // adjacent list
VI path; // preorder traversal path
VI ori2dep, depth, pos;

class RMQ
{
public:
	int n;
	VI tree;
	
	RMQ() {}
	RMQ(VI & vi)
	{
		n = vi.size();
		tree = VI(n * 4, INF);
		init(1, 0, n - 1, vi);
	}

	int init(const int node, const int left, const int right, VI & vi)
	{
		if (left == right) return tree[node] = vi[left];
		const int mid = (left + right) / 2;
		return tree[node] = min(init(node * 2, left, mid, vi), init(node * 2 + 1, mid + 1, right, vi));
	}

	int query(const int & a, const int & b)
	{
		return query(1, 0, n - 1, a, b);
	}

private:
	int query(const int node, const int left, const int right, const int & a, const int & b)
	{
		if (b < left || right < a) return INF;
		if (a <= left && right <= b) return tree[node];
		const int mid = (left + right) / 2;
		return min(query(node * 2, left, mid, a, b), query(node * 2 + 1, mid + 1, right, a, b));
	}
};

void depthNumbering(const int & here, const int d)
{
	ori2dep[here] = num++;

	depth[ori2dep[here]] = d;
	pos[ori2dep[here]] = path.size();
	path.push_back(ori2dep[here]);

	for (int i = 0; i < adj[here].size(); ++i)
	{
		const int & child = adj[here][i].first;
		const int & cost = adj[here][i].second;

		if (ori2dep[child] != -1) continue;
		depthNumbering(child, d + cost);
		path.push_back(ori2dep[here]);
	}
}

int Distance(const int & a, const int & b, RMQ & rmq)
{
	int posa = pos[ori2dep[a]];
	int posb = pos[ori2dep[b]];
	if (posa > posb) swap(posa, posb);
	int lca = rmq.query(posa, posb);
	return depth[ori2dep[a]] + depth[ori2dep[b]] - 2 * depth[lca];
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	adj = ADJ(n + 1);
	ori2dep = VI(n + 1, -1);
	depth = VI(n + 1, -1);
	pos = VI(n + 1);

	for (int i = 1; i < n; ++i)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		adj[a].push_back(MP(b, w));
		adj[b].push_back(MP(a, w));
	}
	depthNumbering(1, 0);
	RMQ rmq(path);

	scanf("%d", &m);
	while (m--)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", Distance(a, b, rmq));
	}
	return 0;
}
