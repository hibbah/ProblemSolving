/**********************************************************************************

2015.05.26

https://www.acmicpc.net/problem/1395

- title : Light Switching
(USA Olympiad 2008-2009 Season :: Gold - C)

- input : the number of Switch N(<=100,000), the number of Query M(<= 100,000)
- output : for each Query[t, a, b]
	1. t == 0 : toggle the switch in range[a, b]
	2. t == 1 : print the number of On-Switch in range[a, b]
- issue : how to update(toggle) fast the switch state in range[a, b]
- solution : using IndexTree(SUM) apply 'lazy propagation'
-time complexity : O(MlogN)

**********************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<bool> VB;

class SEGTREE
{
public:
	int n;
	VI tree;
	VB lazy; // toggle information

	SEGTREE() {}
	SEGTREE(const int & size)
	{
		n = size;
		tree.resize(4 * n, 0);
		lazy.resize(4 * n, false);
	}

	int query(const int & a, const int & b)
	{
		return query(1, 0, n - 1, a, b);
	}

	// toggle
	int update(const int & a, const int & b)
	{
		return update(1, 0, n - 1, a, b);
	}

private:
	int query(const int node, const int left, const int right, const int & a, const int & b)
	{
		if (b < left || right < a) return 0;
		
		if (lazy[node])
		{
			tree[node] = (right - left + 1) - tree[node]; // toggle

			if (left != right) // if not leaf
			{
				// propagate the toggle information to child
				lazy[node * 2] = lazy[node * 2] ? false : true;
				lazy[node * 2 + 1] = lazy[node * 2 + 1] ? false : true;
			}
			lazy[node] = false;
		}
		
		if (a <= left && right <= b) return tree[node];
		const int mid = (left + right) / 2;
		return query(node * 2, left, mid, a, b) + query(node * 2 + 1, mid + 1, right, a, b);
	}

	int update(const int node, const int left, const int right, const int & a, const int & b)
	{
		if (lazy[node])
		{
			tree[node] = (right - left + 1) - tree[node]; // toggle

			if (left != right) // if not leaf
			{
				// propagate the toggle information to child
				lazy[node * 2] = lazy[node * 2] ? false : true;
				lazy[node * 2 + 1] = lazy[node * 2 + 1] ? false : true;
			}
			lazy[node] = false;
		}

		if (b < left || right < a) return tree[node];
		if (a <= left && right <= b)
		{
			tree[node] = (right - left + 1) - tree[node]; // toggle

			if (left != right) // if not leaf
			{
				// propagate the toggle information to child
				lazy[node * 2] = lazy[node * 2] ? false : true;
				lazy[node * 2 + 1] = lazy[node * 2 + 1] ? false : true;
			}
			return tree[node];
		}
		const int mid = (left + right) / 2;
		return tree[node] = update(node * 2, left, mid, a, b) + update(node * 2 + 1, mid + 1, right, a, b);
	}
};

int n, m;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d", &n, &m);
	SEGTREE idxtree(n);
	
	while (m--)
	{
		int type, a, b;
		scanf("%d %d %d", &type, &a, &b); --a; --b;
		switch (type)
		{
		case 0: // toggle in range[a, b]
			idxtree.update(a, b);
			break;
		case 1: // print the number of On-Switch
			printf("%d\n", idxtree.query(a, b));
			break;
		}
	}
	return 0;
}
