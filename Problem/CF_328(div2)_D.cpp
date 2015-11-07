/********************************************************************************************

2015.11.07
http://codeforces.com/contest/592/problem/D

- title : Super M
- input : N(<=123456)개의 노드를 가지는 트리, M(<=N)개의 몬스터 마을 번호
- output : 모든 몬스터마을을 방문하는 거리를 최소로 하기 위한 시작정점과 최소이동거리
- solution : 좀비마을 사이를 이동하는 경로상에 존재하는 모든 간선의 수 - 트리의 지름
- complexity : O(N)

********************************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef vector <int> VI;
typedef vector <VI> VVI;

int n, m, maxlen;
bool isMonster[123457];
bool visit[123457];
VVI adj; // adjacent list

// here를 루트로하는 서브트리에서 좀비마을에 이르는 경로상에 있는 모든 정점의 수 반환
int DFS(const int & here, const int len, int & END)
{
	visit[here] = true; // visit check

	// 트리의 지름 계산
	if (isMonster[here] && len >= maxlen)
	{
		if (len > maxlen) END = here;
		else END = min(END, here); // len == maxlen
		maxlen = len;
	}

	// 좀비마을로 가는 경로상에 있는 정점의 수
	int nearMonsterCnt = 0;
	for (int i = 0; i < adj[here].size(); ++i)
	{
		const int & there = adj[here][i];
		if (visit[there]) continue;
		nearMonsterCnt += DFS(there, len+1, END);
	}
	if (nearMonsterCnt > 0 || isMonster[here]) ++nearMonsterCnt;

	return nearMonsterCnt;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d", &n, &m);

	// construct Tree (acyclic Graph)
	adj = VVI(n+1);
	for (int i = 1; i < n; ++i)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	for (int i = 0; i < m; ++i)
	{
		int monster;
		scanf("%d", &monster);
		isMonster[monster] = true;
	}
	
	// 트리의 지름을 구성하는 양끝점
	int start = 999999, end = 999999;

	maxlen = 0;
	DFS(1, 0, start);

	memset(visit, false, sizeof(visit));
	maxlen = 0; // 트리의 지름 길이
	int edgeCnt = DFS(start, 0, end) - 1; // 정점수-1 == 좀비마을에 이르는 경로상의 간선의 개수
	printf("%d\n%d\n", min(start, end), edgeCnt*2 - maxlen);

	return 0;
}