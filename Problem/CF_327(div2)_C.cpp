/****************************************************************************************

2015.10.26
http://codeforces.com/contest/591/problem/C
CF #327 (Div.2) - problem C

- title : Median Smoothing
- input : 최대 길이 500,000인 0/1로만 구성된 배열 arr[]
- output : arr[]이 stable 상태가 될 때까지 걸리는 최소 시간 & 최종 stable상태를 출력. (불가능하면 -1)
	1. arr[i]값은 다음 단계에서 자기 자신과 양 옆의 원소들의 중간값으로 변화된다.
	   (가장 첫 번째 원소와 마지막 원소는 처음 입력받은 값을 그대로 유지한다.)
	2. arr[]의 모든 원소를 위의 방식대로 변경하는데 1의 시간이 필요.
	3. arr[]이 이전과 동일한. 즉, 모든 원소가 더 이상 변하지 않을때, arr[]를 stable 상태라고 함.

- issue : stable이 될 때 까지 매 단계마다 O(n)변환 수행 -> TimeLimit

- solution :
	1. arr[i]의 값이 다음 단계에서 변화되는 경우는 두 가지. [1 0 1] or [0 1 0]
	2. 위의 경우를 확장시켜서 생각해보면, 0/1이 교대로 등장하는 구간(Alternate Range)에서 변화 발생.
	3. Alternate Range = R(l, r)에서
	   3-1. arr[l]==arr[r]인 경우, 최종적으로 구간의 모든 값이 동일하게 됨.
	   3-2. arr[l]!=arr[r]인 경우, arr[l]값과 arr[r]값이 서로 뭉쳐서 양쪽으로 갈라짐.
	4. R(l, r)의 상태가 stable이 되기 위해 필요한 시간은 구간 길이의 절반만큼의 변환 작업이 필요.

- complexity : O(n)

****************************************************************************************/

#include <stdio.h>
#include <algorithm>

using namespace std;

int n;
int arr[500010];

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	// input
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);

	int minn = 0, l = -1, r = -1;
	while (l<n && r<n)
	{
		// find Alternate-Range R(l, r)
		for (l = r + 1; l < n - 1; ++l) if (arr[l] != arr[l+1]) break;
		for (r = l + 1; r < n - 1; ++r) if (arr[r] == arr[r+1]) break;
		
		// Range length >= 3
		if (r-l+1 < 3) continue;

		// to stable state
		const int mid = (l+r)/2;
		for (int i = l; i <= r; ++i)
			arr[i] = i <= mid ? arr[l] : arr[r];

		// the time until stable state that Range(l, r) is (RangeLength-1)/2
		minn = max(minn, (r-l)/2);
	}

	printf("%d\n", minn);
	for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
	puts("");

	return 0;
}

