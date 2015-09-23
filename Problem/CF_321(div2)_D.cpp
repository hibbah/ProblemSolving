/**********************************************************************************

2015.09.23
http://codeforces.com/contest/580/problem/D

- title : Kefa and Dishes
- input : 음식의 종류 N(<=18), 선택할 음식의 종류 M(<=N), 음식 조합의 갯수 K
N개 음식의 점수, K개의 음식 조합 정보(A와 B를 연속해서 먹으면 C의 점수 얻음)
- output : N개 중에 서로 다른 M개의 음식을 먹을 때, 최대 점수를 출력
- issue : 모든 경우의 수 == (N Combination M)!
- solution :
1. maxScore(prev, cnt, bits)
: 이전에 prev를 먹었고 앞으로 cnt개를 더 먹어서 얻을 수 있는 최대 점수 반환
(bits == N개의 음식을 먹은 정보를 먹었다/안먹었다 로 표현한 bit-stream)
2. prev값과 bits값이 동일할 때, maxScore함수는 동일한 값을 반환.
즉, 탐색과정에서 prev와 bits로 특정 상태를 유일하게 표현 가능.
cnt값은 bits를 조사하여 얻을 수 있으나, 구현의 편의성을 위해 사용
3. prev(18) * bits(2^18) 크기의 memoizationTable을 선언하여 DP수행

- complexity : O( N * 2^N )

**********************************************************************************/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

int n, m, k;
ll score[20];
ll bonus[20][20];
ll cache[19][1 << 18];

// returns the maximum score that can be obtained by eating more 'cnt' foods
ll maxScore(const int & prev, const int cnt, const int state)
{
	if (cnt == 0) return 0;

	ll & ret = cache[prev][state];
	if (ret != -1) return ret;
	ret = 0;

	for (int i = 0; i < n; ++i)
	{
		if (state & (1 << i)) continue; // food 'i' aleady eat
		ret = max(ret, maxScore(i, cnt - 1, state | (1 << i)) + score[i] + bonus[prev][i]);
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	memset(cache, -1, sizeof(cache)); // memoization Table init

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; ++i)
		scanf("%lld", &score[i]);
	while (k--)
	{
		int a, b; ll c;
		scanf("%d %d %lld", &a, &b, &c);
		bonus[a - 1][b - 1] = c;
	}
	printf("%lld\n", maxScore(18, m, 0)); // 18 == garbage value

	return 0;
}
