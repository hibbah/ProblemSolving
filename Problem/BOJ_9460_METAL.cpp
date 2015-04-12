/**********************************************************************************

2015.04.12

https://www.acmicpc.net/problem/9460 - "METAL"
(ACMICPC Asia Regional - Daejeon 2013 problem F)

- input : N(<=10,000), K(<=N), N's point <x, y> (<= |100,000,000|)
- output : min Cost to mining all metal

- solution :
	1. define function F(L) : is it possible to mining all metals use interval L & K group
	2. parametric search (0 ~ L ~ 200,000,000)
- time complexity : Nlog(200,000,000) == 28*N

**********************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(v, repeat) for(int v=0; v<(repeat); ++v)

#define X first
#define Y second
#define INF 999999999

typedef pair<int, int> PI;
typedef vector <int> VI;

int t, n, k;
vector <PI> point;

bool isPossible(const int & len)
{
	int cnt = 1;
	int minn = INF, maxx = -INF;

	REP(i, n)
	{
		minn = min(minn, point[i].Y);
		maxx = max(maxx, point[i].Y);
		if (maxx - minn > len)
		{
			++cnt;
			minn = point[i].Y, maxx = point[i].Y;
		}
	}
	return cnt <= k;
}

double minCost()
{
	int l = 0, r = 200000001;
	int ret = INF;

	while (l <= r)
	{
		int mid = (l + r) / 2;
		
		if (isPossible(mid))
		{
			r = mid - 1;
			ret = min(ret, mid);
		}
		else l = mid + 1;
	}
	return ret*1.0;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt","w+", stdout);
#endif

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &n, &k);
		point = vector <PI>(n);
		REP(i, n) scanf("%d %d", &point[i].X, &point[i].Y);
		sort(point.begin(), point.end());
		printf("%.1lf\n", minCost() / 2);
	}
	return 0;
}
