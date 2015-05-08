/*******************************************************************************

2015.05.08

https://www.acmicpc.net/problem/2234

BOJ 2234 - The Castle (IOI 1994 - B)

- input : Castle map include walls (w<=50, h<=50)
- output :
	1. the number of Rooms
	2. the biggest area of room
	3. the biggest area that can be created by combining two adjacent rooms

- solution : DFS (Depth First Search)
	Graph design : Mapping each cell to a Vertex (each vertex can be identified by the index [i][j])
	
	1. int DFSall()		:: the number of Rooms == the number of components
	2. int DFS(v)		:: the bigeest area of room == size of the largest component
	3. int mergeComp()	:: the biggest area that Merge Rooms == max(component size of two adjacent rooms)

- time complexity :
	DFSall() + mergeComp() == O(w*h) + O(w*h) == O(w*h)

*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, -1, 0, 1 };
int w, h;
VVI table;
VVI visit; // visit[i][j] == component identity number that include cell[i][j]
VI compSize; // component size

int DFS(const int & i, const int & j, const int & compNum)
{
	visit[i][j] = compNum;

	int ret = 1;
	int wall = table[i][j];
	for (int d = 0; d < 4; ++d)
	{
		const int y = i + dy[d];
		const int x = j + dx[d];
		if ((wall & 0x01) == 0 && visit[y][x] == -1)
		{
			ret += DFS(y, x, compNum);
		}
		wall >>= 1;
	}
	return ret;
}

int DFSall()
{
	int compNum = 0;
	int maxx = -1;

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		if (visit[i][j] == -1)
		{
			int size = DFS(i, j, compNum);
			maxx = max(maxx, size);
			compSize.push_back(size);
			++compNum;
		}
	}
	return maxx;
}

int mergeComp()
{
	int maxx = -1;

	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
	{
		for (int d = 0; d < 4; ++d)
		{
			const int y = i + dy[d];
			const int x = j + dx[d];

			if (!(0 <= x && x < w && 0 <= y && y < h)) continue;
			if (visit[i][j] == visit[y][x]) continue;

			maxx = max(maxx, compSize[visit[i][j]] + compSize[visit[y][x]]);
		}
	}
	return maxx;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d", &w, &h);
	table = VVI(h, VI(w));
	visit = VVI(h, VI(w, -1));

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
			scanf("%d", &table[i][j]);
	}

	const int maxRoom = DFSall();
	const int maxMergeRoom = mergeComp();
	printf("%d\n%d\n%d\n", compSize.size(), maxRoom, maxMergeRoom);

	return 0;
}
