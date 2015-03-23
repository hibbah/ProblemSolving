/***********************************************************************

https://www.acmicpc.net/problem/1948

- summary : calc all Longest-Path on graph
- input : DAG(directed acyclic graph), start/end point
- output : Largest-distance, the number of the distinct edges that compose every longest paths

***********************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define MP make_pair
#define REP(v, repeat) for(int v=0; v<(repeat); ++v)

typedef pair<int, int> PI;
typedef vector <int> VI;
typedef vector <VI> VVI;
typedef vector <vector <PI> > ADJ;

const int INF = 2100000000;

int n, m, maxcost;
ADJ adj; // adjacent list

VVI Dijkstra(const int & start, const int & end)
{
	VVI parent(n + 1);
	priority_queue <PI> pq; pq.push(MP(0, start));
	VI dist(n + 1, -1); dist[start] = 0;

	while (pq.size())
	{
		const int here = pq.top().second;
		const int cost = pq.top().first;
		pq.pop();

		if (cost < dist[here]) continue;

		REP(i, adj[here].size())
		{
			const int & there = adj[here][i].first;
			const int newcost = adj[here][i].second + cost;

			if (newcost < dist[there]) continue;
			
			if (newcost > dist[there])
			{
				parent[there].clear();
				dist[there] = newcost;
				pq.push(MP(newcost, there));
			}
			parent[there].push_back(here);
		}
	}
	maxcost = dist[end];
	return parent;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt","w+", stdout);
#endif

	scanf("%d%d", &n, &m);
	adj = ADJ(n + 1);

	REP(i, m)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		adj[a].push_back(MP(b, w));
	}
	int start, end;
	scanf("%d%d", &start, &end);

	VVI && parent = Dijkstra(start, end);
	int cnt = 0;
	queue <int> q; q.push(end);
	while (q.size())
	{
		int v = q.front(); q.pop();
		cnt += parent[v].size();
		REP(i, parent[v].size()) q.push(parent[v][i]);
		parent[v].clear();
	}
	printf("%d\n%d\n", maxcost, cnt);

	return 0;
}
