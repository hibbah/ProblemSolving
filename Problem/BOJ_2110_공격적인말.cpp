/********************************************************************************

2015.04.04

https://www.acmicpc.net/problem/2110

- input : N (the number of integer), C (the number of choice), N positive integers (<=10^9)
- output : when i choose the C number, Value such that the minimum distance is the maximum
- solution : parametric-search
- time complexity : O( log10^9 * NlogN ) == O( 30 * NlogN )

********************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(v, repeat) for(int v=0; v<(repeat); ++v)
typedef vector <int> VI;

int n, c;
VI vi;

inline bool isPossible(const int & interval)
{
	int cnt = 0;
	VI::iterator it = vi.begin();

	while (it != vi.end())
	{
		if (++cnt >= c) return true;
		it = lower_bound(it + 1, vi.end(), interval + *it); // binary-search
	}
	return false;
}

int maxLength()
{
	int l = 1, r = vi.back(); // min, max distance
	int ret = -1; // return value (max Length)

	while (l <= r)
	{
		int m = (l + r) / 2; // interval distance between each MAL
		
		if (isPossible(m)) // is it possible to place C hourse as interval M ?
		{
			ret = max(ret, m); // update
			l = m + 1; // interval increase
		}
		else r = m - 1; // interval decrease
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w+", stdout);
#endif

	scanf("%d%d", &n, &c);
	vi = VI(n);
	REP(i, n) scanf("%d", &vi[i]);
	sort(vi.begin(), vi.end());
	printf("%d\n", maxLength());
	
	return 0;
}
