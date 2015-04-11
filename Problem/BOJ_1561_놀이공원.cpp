/*************************************************************************

2015.04.11

https://www.acmicpc.net/problem/1561

- input : N(<=2,000,000,000), M(<=10,000), playing time T[M] (<=30)
- output : Machine Number that boarding N-th person

- solution
	1. calc Nth person boarding time (using Parametric-Search) : O(M*log(MAXTIME))
	2. calc Machine Number that boarding N-th person (Brute force) : O(M)

- time complexity : O( M*log(MAXTIME) + M ) == O( 36*M )

*************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MP make_pair
#define REP(v, repeat) for(int v=0; v<(repeat); ++v)

typedef long long ll;
typedef pair<ll, ll> PI;

int n, m;
vector <ll> vi;

// return moment right before Nth person boarding
PI calcTime()
{
	ll l = 0, r = 60000000000;
	PI ret(-1, -1); // <time, sum>
	
	while (l <= r)
	{
		ll mid = (l + r) / 2; // candidate Time
		ll sum = m; // the number of people used Machine while time(mid)
		REP(i, m) sum += (mid / vi[i]);

		if (sum >= n) r = mid - 1;
		else // sum < n
		{
			ret = max(ret, MP(mid, sum));
			l = mid + 1;
		}
	}
	return ret;
}

// return Machine Number that N-th person boards on
int getMachineNum(const PI & last)
{
	ll Time = last.first + 1; // N'th person boarding time
	ll sum = last.second;

	REP(i, m)
	{
		if (Time % vi[i] == 0)
			if (++sum == n) return i + 1;
	}
	while (1);
	return 0;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt","w+", stdout);
#endif

	scanf("%d %d", &n, &m);
	vi = vector <ll> (m);
	REP(i, m) scanf("%lld", &vi[i]);
	PI last = calcTime();
	printf("%d\n", getMachineNum(last));

	return 0;
}
