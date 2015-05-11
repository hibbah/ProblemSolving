/**********************************************************************************

2015.05.11

https://www.acmicpc.net/problem/3653

- title : Movie collection
(ACMICPC_Regionals_Europe :: NWERC 2011 - C)

- input :
	1. the number of DVD (N <= 100,000)
	2. the number of Query (M <= 100,000)
	3. the order of the DVD to watch. (D1 D2 D3 ... Dm) (M integers)
- output : position for each DVD(Di) in DVD list
- solution : using Fenwick Tree for the virtual array - bool isExist[N + M]
- complexity :
	1. construct Fenwick Tree : O( (N+M)*log(N+M) )
	2. print the output for DVD(Di) : O( 3log(N+M) )
	total complexity == O( (N+M)log(N+M) + 3Mlog(N+M) ) == O( (N+4M)log(N+M) )

**********************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

typedef vector <int> VI;

class FenWick
{
public:
	VI tree;

	FenWick(const int size) : tree(size + 1) {}

	void add(int idx, const int & value)
	{
		++idx;
		while (idx < tree.size())
		{
			tree[idx] += value;
			idx += (idx & -idx);
		}
	}

	int sum(int idx)
	{
		++idx;
		int ret = 0;
		while (idx > 0)
		{
			ret += tree[idx];
			idx -= (idx & -idx);
		}
		return ret;
	}
};

int t, n, m;
VI pos;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		int idx = n + m - 1; // index of the next DVD to be inserted in Fenwick Tree
		FenWick fenwick(idx + 1); // Fenwick Tree for logical array[n + m]
		pos = VI(n + 1); // pos[DVD] == index of the DVD in Fenwick Tree

		for (int DVD = n; DVD >= 1; --DVD)
		{
			pos[DVD] = idx--;
			fenwick.add(pos[DVD], 1);
		}

		while (m--)
		{
			int DVD; scanf("%d", &DVD);
			printf("%d ", fenwick.sum(pos[DVD]) - 1); // print a number of '1' in arr[ 0~pos[DVD] ]
			fenwick.add(pos[DVD], -1); // remove DVD from original position pos[DVD] : (1 -> 0)
			fenwick.add(pos[DVD] = idx--, 1); // insert DVD into new position 'idx' : (0 -> 1)
		}
		puts("");
	}
	return 0;
}
