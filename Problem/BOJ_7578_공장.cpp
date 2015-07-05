/**********************************************************************************

2015.07.05

https://www.acmicpc.net/problem/7578
(KOI2013 - HighSchool problem 3)

- title : Factory
- input :
	N(<=500,000). two array of N integers. (arr[], brr[])
	(same elements of two arrays. but, not order)
- output :
	when the connection between the same elements in two array,
	print the number of intersections pair.
- solution : 
	1. translate array (arr[] = {1 2 3 4 5} / brr[] = {3 5 1 4 2})
	2. for all the elements of brr[], large number of which can precede them.
	3. print the sum of '2.'
- complexity : O(NlogN)

***********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair <int, int> PI;
typedef vector <ll> VI;
#define MP make_pair

class Fenwick
{
public:
	VI tree;

	Fenwick() {}
	Fenwick(const int & n) : tree(n + 1) {}

	ll sum(int idx)
	{
		++idx;
		ll ret = 0;
		while (idx > 0)
		{
			ret += tree[idx];
			idx -= (idx & -idx);
		}
		return ret;
	}

	void add(int idx, const ll & val)
	{
		++idx;
		while (idx < tree.size())
		{
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}
};

int n;
PI arr[500000];
ll vi[500000];

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i].first);
		arr[i].second = i;
	}
	sort(arr, arr + n);

	for (int i = 0; i < n; ++i)
	{
		int num; scanf("%d", &num);
		vi[i] = lower_bound(arr, arr + n, MP(num, -1))->second;
	}
	
	Fenwick fenwick(n);
	ll sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += (i - fenwick.sum(vi[i]));
		fenwick.add(vi[i], 1);
	}
	printf("%lld\n", sum);

	return 0;
}

