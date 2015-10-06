/*************************************************************************************

2015.10.06
https://www.acmicpc.net/problem/11066
(ACMICPC Asia Regional - Daejeon Internet Competition 2015 problem B)

- title : Merging Files
- input : N(<=500), N integers(<=10,000)
- output :
	'인접한' 두 수를 하나로 합치는데 필요한 비용이 두 수의 합일 때,
	주어진 N개의 숫자들을 하나로 합치는데 필요한 최소비용을 출력.

- issue :
	greedy전략(매 순간 인접한 두 수의 합이 최소인 쌍을 합침)으로는 불가능.
	현재 단계에서 최선의 선택이 이후 단계에서 좋지 않은 결과를 가져올 수 있음.
	=> 다른 논리가 있거나, 모든 경우를 다 수행해봐야 함.

- solution :
	1. 숫자 N개가 주어졌을 때, 항상 N-1번의 합치기 과정을 수행. (방법만 다를뿐, 합치는 횟수는 동일)
	2. 범위 [l, r]에 대해, 합치는 방법은 다양하지만 합친 결과값은 Sum[l, r]로 동일.
	3. minCost[l, r] == 범위 [l, r]의 숫자들을 하나로 합치는데 필요한 최소비용으로 정의.
	4. minCost[l, r]= min( minCost[l, k] + minCost[k+1, r] + Sum[l, r] ). (l<=k<r)
	=> 주어진 범위[l, r]에 대해, l<=k<r을 만족하는 k를 기준으로 [l, k], [l+1, r]을 우선적으로 합치고
	   그 결과로 남은 두 숫자를 마지막으로 합쳐서 하나의 숫자로 만들때 필요한 최소비용
	   마지막으로 남은 두 숫자를 합치는데 필요한 비용 = Sum[l, l] + Sum[l+1, r] = Sum[l, r]
	5. 숫자를 하나로 합치는데 가능한 모든 경우를 계산.
	   계산 과정에서 동일한 범위[l, r]에 대한 최소비용의 계산을 중복으로 수행할 수 있으므로 DP테크닉 이용

- complexity : O(N^3)

*************************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
typedef long long ll;
 
const ll INF = 999999999999;
ll card[502]; // data
ll Sum[502]; // Sum[a] == Sum(card[0] ~ card[a])
ll cache[502][502]; // memoization table

// return the minimum Cost to combine a number one
ll minCost(const int l, const int r)
{
    if (l == r) return 0;
    if (l + 1 == r) return card[l] + card[r];
 
    ll & ret = cache[l][r]; // memoization
    if (ret != -1) return ret;
    ret = INF;
 
    for (int mid = l; mid < r; ++mid) // split range [l, mid] + [mid+1, r]
    {
	// minCost[l, r] = min( minCost[l, mid] + minCost[mid+1, r] + Sum(card[l]~card[r]) )
        ret = min(ret, minCost(l, mid) + minCost(mid+1, r) + Sum[r] - Sum[l-1]);
    }
    return ret;
}
 
int main()
{
#ifdef _CONSOLE
    freopen("input.txt", "r", stdin);
#endif
 
    int t;
	scanf("%d", &t);
    while (t--)
    {
        memset(cache, -1, sizeof(cache)); // init the memoization table
        
	// input data
	int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &card[i]);
            Sum[i] = Sum[i - 1] + card[i]; // calc subsum
        }
        
	printf("%lld\n", minCost(1, n));
    }
 
    return 0;
}
