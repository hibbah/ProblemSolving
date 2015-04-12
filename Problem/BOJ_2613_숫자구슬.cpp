/**********************************************************************************

2015.04.12

https://www.acmicpc.net/problem/2613

- input : 1 <= M <= N <= 300, N's p-integer (<= 100)
- output : 주어진 자연수 리스트를 연속된 부분 집합으로 M분할 하였을 때,
			분할된 그룹의 합들 중 최대값이 최소가 되도록 분할하여라.
			=> 최소가 되는 그룹합의 최대값과 이 때의 그룹별 원소의 수를 차례로 출력

- solution : 각 그룹의 합계가 Sum이하이되 원소가 최대가 되도록 M분할이 가능한지 탐색
															(parametric search)
- time complexity : NlogN * log(100N)

**********************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

#define FOR(v, pos, end) for(int v=(pos); v<=(end); ++v)
typedef vector<int> VI;

int n, m;
VI vi, psum;

// group count that sum of group less than 'sum'
int splitGroup(const int & sum)
{
	int cnt = 0;
	VI::iterator it = psum.begin() + 1;
	while (it != psum.end())
	{
		it = upper_bound(it, psum.end(), sum + *(it - 1));
		++cnt;
	}
	return cnt;
}

// min value that one of possible sum values (parametric search)
int maxToMin()
{
	int l = 0, r = 100 * n;
	int ret = 9999999999;

	while (l <= r)
	{
		int mid = (l + r) / 2;

		int groupcnt = splitGroup(mid);
		if (groupcnt > m)
			l = mid + 1;
		else // groupcnt <= m
		{
			ret = min(ret, mid);
			r = mid - 1;
		}
	}
	return ret;
}

// dply group size interval sum
void dplyGroup(const int & sum)
{
	VI::iterator last;
	VI::iterator next = psum.begin() + 1;
	while (1)
	{
		last = next;
		next = upper_bound(next, psum.end(), sum + *(last - 1));
		printf("%d ", next - last);
		if (next == psum.end()) break;
	}
	puts("");
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
	//freopen("output.txt","w+", stdout);
#endif

	// input
	scanf("%d%d", &n, &m);
	vi = VI(n + 1), psum = VI(n + 1, 0);
	FOR(i, 1, n) scanf("%d", &vi[i]);
	partial_sum(vi.begin(), vi.end(), psum.begin()); // calc partialsum

	int ret = maxToMin(); // calc min of max
	printf("%d\n", ret);
	dplyGroup(ret); // dply group

	return 0;
}
