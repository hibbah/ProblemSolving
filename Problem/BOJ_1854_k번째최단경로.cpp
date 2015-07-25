/**********************************************************************************

2015.07.25

https://www.acmicpc.net/problem/1854/

- title : k'th shortest path
- input : directed-Graph G(V, E), K. V<=1,000. E<=2,000,000. K<=100
- output : all k'th minimum distance. (start Vtx == 1)
- solution : Dijkstra algorithm
- complexity : ElogVK

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair <int, int> PI;
typedef vector <vector <PI>> ADJ;
#define MP make_pair
#define INF 999999999

int n, m, k;
ADJ adj; // adjacent list

void getKthpath(const int & start, vector <priority_queue<int>> & dist)
{
	priority_queue <PI, vector<PI>, greater<PI>> pq; // minheap <distance, vtx>
	dist = vector <priority_queue <int>>(n + 1);
	pq.push(MP(0, start));
	dist[start].push(0);

	while (pq.size())
	{
		const int here = pq.top().second;
		const int cost = pq.top().first;
		pq.pop();

		for (int i = 0; i < adj[here].size(); ++i)
		{
			const int & there = adj[here][i].first;
			const int newcost = adj[here][i].second + cost;
			const int kthcost = dist[there].size() == k ? dist[there].top() : INF;

			if (newcost < kthcost)
			{
				if (kthcost != INF) dist[there].pop();
				dist[there].push(newcost);
				pq.push(MP(newcost, there));
			}
		}
	}
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d %d", &n, &m, &k);
	adj = ADJ(n + 1);

	while (m--)
	{
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		adj[a].push_back(MP(b, w));
	}
	vector <priority_queue <int>> kthPath;
	getKthpath(1, kthPath);
	for (int v = 1; v <= n; ++v)
	{
		printf("%d\n", kthPath[v].size() < k ? -1 : kthPath[v].top());
	}

	return 0;
}