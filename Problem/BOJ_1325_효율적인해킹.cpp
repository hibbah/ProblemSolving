/**************************************************************************

2015.03.29

https://www.acmicpc.net/problem/1325/

- input : (cyclic) directed Graph (N, M)
	- N <= 10,000, M <= 100,000
- output : all vertex that largest mastery

- issue : cycle. (=> N*DFS solution O(N*M) is maybe timelimit...) => accept for BOJ
- solution : SCC + SCCDFS

**************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

#define MP make_pair
#define REP(v, repeat) for(int v=0; v<(repeat); ++v)
#define REPD(v, repeat) for(int v=(repeat)-1; v>=0; --v)
#define FOR(v, pos, end) for(int v=(pos); v<=(end); ++v)
#define FORD(v, pos, end) for(int v=(pos); v>=(end); --v)

typedef vector <int> VI;
typedef vector <VI> VVI;
typedef vector <bool> VB;

// Strongly Connected Component
class SCC
{
public:
	VI node;
	SCC(){}
};

int n, m, maxx = -1;
vector <SCC> scc;
stack <int> s; // for SCC
VVI adjF, adjR; // adjacent list (Foward, Reverse)
VB visit;
VI sccNumof, size;

void DFS(const int & v)
{
	visit[v] = true;
	REP(i, adjF[v].size())
	{
		const int & next = adjF[v][i];
		if (visit[next] == false) DFS(next);
	}
	s.push(v);
}

void RDFS(const int & v, const int & idx)
{
	visit[v] = true;
	REP(i, adjR[v].size())
	{
		const int & next = adjR[v][i];
		if (visit[next] == false) RDFS(next, idx);
	}
	scc[idx].node.push_back(v);
	sccNumof[v] = idx;
}

void calcSCC()
{
	FOR(v, 1, n) if (visit[v] == false) DFS(v);
	fill(visit.begin(), visit.end(), false);
	
	int idx = 0;
	while (s.size())
	{
		const int v = s.top(); s.pop();
		if (visit[v] == false)
		{
			scc.push_back(SCC());
			RDFS(v, idx);
			++idx;
		}
	}
}

int cnt = 0;

int calcSize(const int & scchere, VI & sccVisit)
{
	sccVisit[scchere] = cnt;

	const VI & list = scc[scchere].node;
	int ret = list.size();

	REP(i, list.size())
	{
		const int & here = list[i];

		REP(j, adjR[here].size())
		{
			const int & there = adjR[here][j];
			const int & sccthere = sccNumof[there];
			if (scchere == sccthere) continue;
			if (sccVisit[sccthere] == cnt) continue;
			ret += calcSize(sccthere, sccVisit);
		}
	}
	
	REP(i, list.size()) size[list[i]] = ret;
	return ret;
}

void calcSize()
{	
	VI sccVisit(scc.size(), -1);
	REP(i, scc.size())
	{
		maxx = max(maxx, calcSize(i, sccVisit));
		++cnt;
	}
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &n, &m);
	adjF = VVI(n + 1);
	adjR = VVI(n + 1);
	size = VI(n + 1);
	sccNumof = VI(n + 1);
	visit = VB(n + 1, false);

	REP(i, m)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		adjF[a].push_back(b);
		adjR[b].push_back(a);
	}
	
	calcSCC();
	calcSize();

	FOR(v, 1, n) if (size[v] == maxx) printf("%d ", v);
	puts("");

	return 0;
}
