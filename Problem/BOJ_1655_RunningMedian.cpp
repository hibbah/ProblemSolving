/*********************************************************************************

2015.05.12

https://www.acmicpc.net/problem/1655
https://www.acmicpc.net/problem/2696/
https://algospot.com/judge/problem/read/RUNNINGMEDIAN

- title : Running Median
(ACMICPC_Regionals_NorthAmerica :: GNYPC 2009 - D)

- input : N(<=100,000) integers(-10,000 ~ 10,000)
- output : Median values each new number is inserted every moment
- issue : how to find out fast the Median value of every moment
	1. insert, sort, insert, sort, ... -> O( N^2log(N) )
	2. Maintaining an ordered sequence... -> O( N^2 )
- solution :
	1. use two heap structure (maxheap, minheap)
	2. LeftSegment(maxheap) --- MID value --- RightSegment(minheap)
	3. MID value is always to be placed on top of LeftHeap(maxheap)
	4. keeping the [Left.size() - Right.size() <= 1] -> (shift MID value)
- time complexity : O(NlogN)
- other solution : using B-BST(balanced-BinarySearchTree)

*********************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int n, num, mid = 99999999;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	priority_queue <int> left; // maxheap
	priority_queue <int, vector<int>, greater<int>> right; // minheap

	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &num);

		if (num < mid) left.push(num);
		else right.push(num);

		while (left.size() > right.size())
		{
			right.push(left.top());
			left.pop();
		}
		while (left.size() < right.size())
		{
			left.push(right.top());
			right.pop();
		}
		mid = left.top();

		printf("%d\n", mid);
	}
	return 0;
}
