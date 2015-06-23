/**********************************************************************************

2015.06.23

https://www.acmicpc.net/problem/2118

- title : the two tower
- input : N(<=50,000) integers (circular array). (sum of integers <= 1,000,000,000)
- output : when the array is divided into two sub-sequences, the maximum value of the small value
- issue : A very large number of cases to split into two parts fo the array. (nC2)
- solution : parametric search for Distance(len)
- complexity : N*log(1,000,000,000) == 30*N

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, total = 0;
vector <int> vi;

// is it possible that the Distance(A, B) is more than 'len' ?
bool isPossible(const int & len)
{
	int sum = 0;
	int f = 0, b = 0; // pop, push index

	while (f < n && b < n)
	{
		while (b < n && sum < len)
			sum += vi[b++];
		while (f < b && sum >= len)
		{
			if (min(sum, total - sum) >= len)
				return true;
			sum -= vi[f++];
		}
	}
	return false;
}

// parametric search
// return the maximum Distance
int maxDistance()
{
	int ret = 0;
	int l = 0, r = total;

	while (l <= r)
	{
		const int mid = (l + r) / 2;

		if (isPossible(mid))
		{
			ret = max(ret, mid);
			l = mid + 1;
		}
		else r = mid - 1;
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	vi = vector <int>(n);
	for (int i = 0; i < n; ++i) scanf("%d", &vi[i]), total += vi[i];
	printf("%d\n", maxDistance());
	
	return 0;
}
