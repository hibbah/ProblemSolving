/**********************************************************************************

2015.09.02
https://algospot.com/judge/problem/read/BOJ
https://www.acmicpc.net/problem/1261

- title : Beacjoon Online Judge (알고스팟)
- input : H, W (<= 100). H*W 크기의 테이블.
- output : <1, 1>에서 <H, W>에 이르기 위해 부숴야하는 최소 벽('1')의 갯수
- solution :
	1. minCnt[y][x] : <1, 1>에서 <x, y>에 이르기위해 부숴야하는 최소 벽의 갯수
	2. 최초에 주어진 단 하나의 정보 minCnt[1][1] = 0 으로부터 minCnt[H][W]까지 확장
	3. 점화식 : minCnt[y][x] == min( minCnt[Y][X] ) + (<x, y>==벽 ? 1 : 0).
				<X, Y>는 <x, y>의 인접한 네 방향
	4. 도달 가능한 위치들을 점차적으로 탐색하기 위해 현재 부순 벽의 갯수가 가장 작은 위치부터 탐색
		(자료구조 minheap. STL::priority_queue 이용)

- complexity : HW*log(HW)

***********************************************************************************/


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef vector <string> VS;
typedef vector <int> VI;
typedef vector <VI> VVI;

int h, w;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
VS table;

class Item
{
public:
	int x, y, cnt;

	Item(const int & _x, const int & _y, const int _cnt) : x(_x), y(_y), cnt(_cnt) {}
	bool operator > (const Item & p) const
	{
		return cnt > p.cnt;
	}
};

// Priority(distance) First Search
int PFS()
{
	bool visit[101][101] = { true, };
	priority_queue <Item, vector <Item>, greater <Item> > pq; // minheap <dist, <x, y>>
	pq.push(Item(0, 0, 0));

	while (pq.size())
	{
		const int x = pq.top().x;
		const int y = pq.top().y;
		const int dist = pq.top().cnt;
		pq.pop();

		for (int d = 0; d < 4; ++d)
		{
			const int X = x + dx[d];
			const int Y = y + dy[d];
			if (!(0 <= X&&X < w && 0 <= Y&&Y < h) || visit[Y][X]) continue;
			if (X == w - 1 && Y == h - 1) return dist;
			visit[Y][X] = true;
			pq.push(Item(X, Y, table[Y][X] == '0' ? dist : dist + 1));
		}
	}
	return 0;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d%d", &w, &h);
	table = VS(h);
	for (int i = 0; i < h; ++i) cin >> table[i];
	printf("%d\n", PFS());

	return 0;
}