/**********************************************************************************

2015.05.06

http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=737
UVa 796 - Critical Links

- input : bidirectional graph (maybe include a number of components)
- output : print all CutEdges<a - b> that seperating Graph into different components
- solution : find All CutEdges using DFS
- time complexity : O(|V| + |E|). (adjacent list DFS complexity)

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

using namespace std;

typedef pair<int, int> PI;
typedef vector <int> VI;
typedef vector <VI> VVI;
#define MP make_pair

int n, cnt;
vector <PI> cutedge;
VI visitCnt;
VVI adj;

int findAllCutEdge(const int & here, const int & parent)
{
	visitCnt[here] = cnt++;

	int ret = visitCnt[here]; // it reached the lowest depth Vertex
	for (int i = 0; i < adj[here].size(); ++i)
	{
		const int & there = adj[here][i];
		if (there == parent) continue;

		if (visitCnt[there] == -1)
		{
			const int MVC = findAllCutEdge(there, here); // Minimum Visit Cnt
			if (MVC > visitCnt[here]) // if Edge(here, there) is CutEdge, push
				cutedge.push_back(MP(min(here, there), max(here, there)));
			ret = min(ret, MVC); // update MVC
		}
		else
			ret = min(ret, visitCnt[there]);
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	while (scanf("%d", &n) != EOF)
	{
		adj = VVI(n);
		visitCnt = VI(n, -1);
		cutedge.clear();
		cnt = 0;

		// construct Graph (adjacent list)
		for (int i = 0; i < n; ++i)
		{
			int a, b, edgecnt;
			scanf("%d (%d)", &a, &edgecnt);
			while (edgecnt--)
			{
				scanf("%d", &b);
				adj[a].push_back(b);
			}
		}

		// DFS all
		for (int i = 0; i < n; ++i)
		{
			if (visitCnt[i] == -1)
				findAllCutEdge(i, -1);
		}
		sort(cutedge.begin(), cutedge.end());

		printf("%d critical links\n", cutedge.size()); // the number of cutedge
		for (int i = 0; i < cutedge.size(); ++i)
			printf("%d - %d\n", cutedge[i].first, cutedge[i].second);
		puts("");
	}
	return 0;
}
