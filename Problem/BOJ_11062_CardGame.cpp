/**********************************************************************************

2015.10.04
https://www.acmicpc.net/problem/11062
(ACMICPC Asia Regional - Daejeon Internet Competition 2015 problem B)

- title : Card Game
- input : 카드의 개수 N(<=1,000), N개의 카드값(1~10,000)
- output :
	엘리스와 컴퓨터가 한 턴씩 번갈아가면서 맨 왼쪽 또는 맨 오른쪽 카드를 가져가는 게임을 한다.
	게임은 엘리스부터 시작하며, 컴퓨터는 매 순간 엘리스를 방해하려고 최선을 다한다고 했을 때,
	결과적으로 엘리스가 얻을 수 있는 점수의 최대값을 출력.

- solution :
	1. maxScore(l, r) : 범위 l~r에서 엘리스가 얻을 수 있는 점수의 최대값 반환
	2. 엘리스가 card[l]을 가져가는 경우, 컴퓨터에게 주어지는 범위는 [l+1 ~ r].
	3. 컴퓨터의 차례 이후 다시 엘리스의 턴에서 취할 수 있는 범위는 [l+2 ~ r]또는 [l+1 ~ r-1].
	4. 컴퓨터는 엘리스가 [l+2 ~ r]과 [l+1 ~ r-1]중에 최소값을 얻을 수 경우를 남길 것.
	5. 따라서, 점화식은
		maxScore(l, r) = max(
		card[l] + min( maxScore(l+2, r), maxScore(l+1, r-1) ),
		card[r] + min( maxScore(l+1, r-1), maxScore(l, r-2) ) )
	6. 계산 과정에서 동일한 입력 범위에 대해 중복연산을 수행할 수 있으므로 dp를 수행
	
- complexity : O(N^2)

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int arr[1010];
int cache[1010][1010];

// return the maximum Score in range(l ~ r)
int maxScore(const int l, const int r)
{
	if(r < l) return 0; // invalid range
	if(l == r) return arr[l]; // base case

	int & ret = cache[l][r]; // memoization
	if(ret != -1) return ret;
	ret = 0;

	// recursive
	ret = max(ret, arr[l] + min(maxScore(l+2, r), maxScore(l+1, r-1)));
	ret = max(ret, arr[r] + min(maxScore(l+1, r-1), maxScore(l, r-2)));

	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	int t;
	scanf("%d", &t);
	while(t--)
	{
		memset(cache, -1, sizeof(cache)); // initialize memoization table 
		int n; scanf("%d", &n);
		for(int i=0; i<n; ++i) scanf("%d", &arr[i]); // card values
		printf("%d\n", maxScore(0, n-1));
	}
	return 0;
}