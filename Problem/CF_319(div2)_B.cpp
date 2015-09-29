/**********************************************************************************

2015.09.29
http://codeforces.com/problemset/problem/577/B

- title : Modulo Sum
- input : N(<=1,000,000), M(<=1,000), arr[N](<= 1,000,000,000)
- output : arr의 부분집합 중, 합을 M으로 나눈 결과가 0이 되는 부분집합이 존재하는가?
- issue :
	1. 부분집합의 수 == 2^N
	2. dp[idx][R] : idx~ 의 조합으로 M으로 나눈 결과가 R이 되는 부분집합의 개수
		=> dp[N][M] == 1,000,000,000 => 메모리&시간 초과

- solution :
	Sum[a][b] : arr[a]~arr[b]까지의 구간합으로 정의.
	N > M인 경우, 비둘기집의원리에 의해 Sum[0][i]%M == Sum[0][j]%M인 서로 다른 i,j쌍이 반드시 존재.
	i < j, Sum[0][i]%M == Sum[0][j]%M == R 이라고 가정 하면,
	Sum[0][j] = Sum[0][i] + Sum[i+1][j]에서
	Sum[0][j] % M = ( Sum[0][i]%M + Sum[i+1][j]%M ) % M 이 되고,
	R == ( R + Sum[i+1][j]%M ) % M 이므로, 반드시 Sum[i+1][j]%M == 0을 만족해야함.
	따라서, 합을 M으로 나눈 결과가 0이 되는 부분집합 Set[i+1][j]가 반드시 존재함.

	1. N > M인 경우, 무조건 "YES"를 출력
	2. N <= M인 경우, dp[1000][1000] 과정 수행

- complexity : O(M^2)

**********************************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

typedef unsigned long long ull;

int n, m;
int arr[1000001];
ull dp[1001][1001];

// arr[idx]~arr[n-1]의 집합중, 합을 M으로 나눈 결과가 R이 부분집합의 개수 반환
ull isPossible(const int idx, const int R)
{
	if (idx == n) return R == 0 ? 1 : 0;

	ull & ret = dp[idx][R]; // memoization
	if (ret != -1) return ret;
	ret = 0;

	ret = isPossible(idx + 1, R); // arr[idx]를 선택하지 않은 경우
	ret += isPossible(idx + 1, (R + m - arr[idx]) % m); // arr[idx]를 포함하는 경우

	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &arr[i]);
		arr[i] %= m;
	}
	bool result;
	if (n > m) result = true;
	else result = isPossible(0, 0) >= 2 ? true : false;
	// 아무것도 선택하지 않은 부분집합(공집합)을 포함하여, 만족하는 부분집합이 2개 이상인 경우만 true
	
	printf("%s\n", result ? "YES" : "NO");

	return 0;
}

