/**********************************************************************************

2015.06.02

https://www.acmicpc.net/problem/1657

- title : DooBoo
(KOI2006 HighSchool problem 2)

- input : H*W table (1 <= H,W <= 14), cost Table for each Pair<A~F, A~F>
- ouptut : print the maximum Cost of all the possible combination
each cell must satisfy one of the conditions below
	1. not used
	2. pair with adjacent(up, down, left, right) cell
- issue :
	1. design the backtracking(BruteForce) Function maxCost(y, x)
	2. but, Since the number of cases 3^(H*W), it is impossible within the 2seconds.
	3. using DP about the current state of the 'entire table'. but, DP table size is [ W*H*2^(W*H) ].
- solution : bit-mask DP for 'next W cell' => DP table size = [ W*H*2^W ]
- time complexity : O(WH * 2^W) == O(16384 * WH)

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

bool visit[15][15];
char table[15][15];
int cost[6][6] = { // cost of each pair <A~F, A~F>
	{ 10, 8, 7, 5, 0, 1 },
	{ 8, 6, 4, 3, 0, 1 },
	{ 7, 4, 3, 2, 0, 1 },
	{ 5, 3, 2, 2, 0, 1 },
	{ 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0, 0 }
};
const int mask = 0x3FFF; // 14bit masking
int cache[14][14][1 << 14]; // memoization table
int w, h;

// s == state of next W cells
int maxCost(const int y, const int x, const int s)
{
	if (y == h) return 0;
	if (x == w) return maxCost(y + 1, 0, s);

	int & ret = cache[y][x][s];
	if (ret != -1) return ret;

	ret = maxCost(y, x + 1, (s << 1) & mask); // not use cell[y][x]
	if (visit[y][x]) return ret;

	visit[y][x] = true;
	if (x + 1 < w && visit[y][x + 1] == false) // grouping [y][x] + [y][x+1]
	{
		visit[y][x + 1] = true;
		ret = max(ret, cost[table[y][x] - 'A'][table[y][x + 1] - 'A']
			+ maxCost(y, x + 2, (s << 2) & mask));
		visit[y][x + 1] = false;
	}
	if (y + 1 < h && visit[y + 1][x] == false) // grouping [y][x] + [y+1][x]
	{
		visit[y + 1][x] = true;
		ret = max(ret, cost[table[y][x] - 'A'][table[y + 1][x] - 'A']
			+ maxCost(y, x + 1, ((s << 1) & mask) + 1));
		visit[y + 1][x] = false;
	}
	visit[y][x] = false;
	
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	memset(cache, -1, sizeof(cache));
	scanf("%d %d", &h, &w);
	for (int i = 0; i < h; ++i) scanf("%s", table[i]);
	printf("%d\n", maxCost(0, 0, 0));

	return 0;
}
