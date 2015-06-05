/**********************************************************************************

2015.06.06

http://codeforces.com/contest/548/problem/D

- title : Mike and Feet
- input : N(<=200,000). N integers (<= 1,000,000,000)
- output :
	1. define 'strength' for group[x] : minimum Value of the group[X] that length is X.
	2. for each X from 1 to N, print the maximum strength among all groups of size X.
- issue : how to find the strength among all groups of size X.
- solution :
	1. define Num == i'th number
	2. calc Num is the strength that the lagest range[left ~ right] (using histogram algorithm)
- time complexity : O(N)

**********************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

typedef vector <int> VI;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	int n;
	scanf("%d", &n);
	VI vi(n), ret(n + 1, -1);
	for (int i = 0; i < n; ++i) scanf("%d", &vi[i]);

	VI left(n, -1), right(n, n), stack;
	for (int i = 0; i < n; ++i)
	{
		while (stack.size() && vi[stack.back()] >= vi[i]) stack.pop_back();
		if (stack.size()) left[i] = stack.back();
		stack.push_back(i);
	}

	while (stack.size()) stack.pop_back();

	for (int i = n - 1; i >= 0; --i)
	{
		while (stack.size() && vi[stack.back()] >= vi[i]) stack.pop_back();
		if (stack.size()) right[i] = stack.back();
		stack.push_back(i);
	}

	for (int i = 0; i < n; ++i)
	{
		const int len = right[i] - left[i] - 1;
		ret[len] = max(ret[len], vi[i]);
	}

	for (int len = n - 1; len >= 1; --len)
		ret[len] = max(ret[len], ret[len + 1]);

	for (int len = 1; len <= n; ++len)
		printf("%d ", ret[len]);
	puts("");

	return 0;
}
