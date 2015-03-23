/******************************************************************************

2015.03.23

https://www.acmicpc.net/problem/2481

- input : the number of Vertex N (<= 100,000)
- output : all vertex number on shortest Path 1 to V for M(<=50) Query
- issue : constructGraph ( O(n^2) solution is impossible )

- solution complexity : O(nlogn)

*****************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

#define VALUE first
#define VTX second
#define MP make_pair
typedef pair<int, int> PI;
typedef vector<int> VI;
typedef vector<VI> VVI;

const int INF = 99999999;
int t, n, len;
char _str[31];
vector <PI> v; // < value, vertex number >
VI parent; // spanning tree after BFS (using find path)
VI dist; // shortest distance
VVI adj; // adjacent list

inline bool cmp(const PI & a, const int & b)
{
	return a.VALUE < b;
}

void constructGraph()
{
	adj = VVI(n + 1); // adjacent list
	
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); ++i)
	{
		const int & val = v[i].VALUE; // i'th value
		const int & vtx = v[i].VTX; // i'th vertex number
		int mask = 1; // bit mask

		for (int j = 0; j < len; ++j) // shift mask & search adjacent Vertex
		{
			if ((val & mask) == 0) // j'th bit == 0
			{
				const int target = val | mask;
				vector<PI>::iterator it = lower_bound(v.begin() + i, v.end(), target, cmp);
				if (it != v.end() && it->VALUE == target) // if exist target
				{
					adj[vtx].push_back(it->VTX);
					adj[it->VTX].push_back(vtx);
				}
			}
			mask <<= 1; // shift left
		}
	}
}

void getShortestPath(const int & start) // BFS
{
	dist = VI(n + 1, INF); dist[start] = 0;
	parent = VI(n + 1, -1); parent[start] = start;
	queue <int> q; q.push(start);

	while (q.size())
	{
		const int here = q.front(); q.pop();

		for (int i = 0; i < adj[here].size(); ++i)
		{
			const int & there = adj[here][i];
			if (dist[there] == INF) // non-visited
			{
				dist[there] = dist[here] + 1;
				parent[there] = here;
				q.push(there);
			}
		}
	}
}

void dplyPath(int v)
{
	if (parent[v] == -1)
	{
		printf("-1\n");
		return;
	}

	VI path(1, v);
	while (parent[v] != v)
	{
		v = parent[v];
		path.push_back(v);
	}
	for (int i = path.size() - 1; i >= 0; --i) printf("%d ", path[i]);
	puts("");
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	// input
	scanf("%d%d", &n, &len);
	v = vector<PI>(n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", _str);
		v[i] = MP(stoi(string(_str), NULL, 2), i + 1); // < value, Vnum >
	}

	constructGraph(); // construct Graph
	getShortestPath(1); // calc shortest path (1 to all)

	// query
	scanf("%d", &t);
	while (t--)
	{
		int v; scanf("%d", &v);
		dplyPath(v);
	}
	return 0;
}
