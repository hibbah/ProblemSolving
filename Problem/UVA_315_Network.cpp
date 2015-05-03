/********************************************************************************

2015.05.01

http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=670&page=show_problem&problem=251

- input : bi-directional graph G(N, E), N<=100
- output : the number of cut-Vertex
- solution : find all cut-Vertex using DFS just one time
- time complexity : O(N + E)

********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

typedef vector <int> VI;
typedef vector <VI> VVI;

string str;
VVI adj;
int n, cnt;
int visitCnt[111];
bool isCutVertex[111];
char line[250];

int DFS(const int & here, const bool & isRoot)
{
	visitCnt[here] = cnt++;
	int ret = visitCnt[here];

	int child = 0;
	for (int i = 0; i < adj[here].size(); ++i)
	{
		const int & there = adj[here][i];

		if (visitCnt[there] == -1)
		{
			++child;
			int MVC = DFS(there, false);
			if (!isRoot && MVC >= visitCnt[here]) isCutVertex[here] = true;
			ret = min(ret, MVC);
		}
		else
			ret = min(ret, visitCnt[there]);
	}
	if (isRoot && child >= 2) isCutVertex[here] = true;
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	while (1)
	{
		cnt = 0;
		memset(visitCnt, -1, sizeof(visitCnt));
		memset(isCutVertex, false, sizeof(isCutVertex));
		scanf("%d", &n);
		if (n == 0) break;
		adj = VVI(n + 1);

		int v;
		while (1)
		{
			scanf("%d", &v);
			if (v == 0) break;
			gets(line);
			stringstream ss(line);
			
			while (!ss.eof())
			{
				int num; ss >> num;
				adj[v].push_back(num);
				adj[num].push_back(v);
			}
		}
		DFS(1, true);
		int cnt = 0;
		for (int i = 1; i <= n; ++i) if (isCutVertex[i]) ++cnt;
		printf("%d\n", cnt);
	}
	return 0;
}