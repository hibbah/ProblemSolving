/***********************************************************************

2015.03.17

https://algospot.com/judge/problem/read/SKICOURSE
DP & Graph

***********************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector <int> VI;
typedef vector <VI> VVI;
typedef pair<int, int> PI;
typedef vector <vector <PI>> ADJ;

#define MP make_pair
#define REP(v, repeat) for(int v=0; v<(repeat); ++v)
#define REPD(v, repeat) for(int v=(repeat)-1; v>=0; --v)
#define FOR(v, pos, end) for(int v=(pos); v<=(end); ++v)
#define FORD(v, pos, end) for(int v=(pos); v>=(end); --v)

const int INF = 2100000000;
int t, n, m, s;
VVI cache;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d%d", &n, &m, &s);
		cache = VVI(n + 1, VI(s + 1, 0)); // DP table - cache[V][cnt] == when reached node V, MaxCost for used cnt
		ADJ adj(n + 1); // adjacent list

		REP(i, m)
		{
			int a, b, w;
			scanf("%d%d%d", &a, &b, &w);
			adj[a].push_back(MP(b, w));
		}

		// process
		// recurence : DP[V][cnt] = for each (U->V) ( max(DP[U][cnt-1]) )
		int maxx = 0;
		FOR(cnt, 1, s){ // using count of Edge
			FORD(here, n, 1){ // for all Vertex
				REP(j, adj[here].size()){ // for all edge here->there
					const int & there = adj[here][j].first;
					const int & cost = adj[here][j].second;
					cache[there][cnt] = max(cache[there][cnt], cache[here][cnt - 1] + cost);
					maxx = max(maxx, cache[there][cnt]);
				}
			}
		}
		printf("%d\n", maxx);
	}
	return 0;
}
