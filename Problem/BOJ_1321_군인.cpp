/**********************************************************************************

2015.09.22
https://www.acmicpc.net/problem/1321

- title : 군인
- input : 그룹의 수 N(<=500,000), N개의 각 그룹의 초기 인원(<=1,000), 질의의 수 M(<=10,000),
- query : M개의 질의마다 아래의 연산을 실행하거나 요구하는 값을 출력
	- [1 b c] :: b번 그룹에 |c|명이 추가되거나 빠저나감
	- [2 b] :: b번째 사람이 소속된 그룹의 번호를 출력
- issue :
	1. 각 그룹의 인원이 유동적으로 변화하는 상황.
	2. 1번~X번 그룹까지의 인원의 총합을 부분합 SUM(1, X)라고 할 때, 
	   SUM(1, X) >= B 를 만족하는 그룹 번호 X를 어떻게 빨리 찾을 것인가
- solution : 
	1. 특정 구간의 합을 빠르게 계산할 수 있는 SegmentTree(FenwickTree)구조 유지
	2. SUM(1, X) >= B 를 만족하는 X를 parametric search로 탐색

- complexity : O( NlogN + M(logN)^2 )
	1. FenwickTree 구축 시간 NlogN
	2. 인구 변화 질의 처리시간 logN, B번째 사람이 속한 그룹의 번호 출력 시간 (logN)^2

**********************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// FenwickTree
class Fenwick
{
public:
	int tree[500002];
	int n;

	Fenwick() {}
	Fenwick(const int size)
	{
		n = size + 1;
		memset(tree, 0, 4 * n);
	}

	void add(int idx, const int & val)
	{
		++idx;
		while (idx < n)
		{
			tree[idx] += val;
			idx += (idx & -idx);
		}
	}

	int sum(int idx)
	{
		++idx;
		int ret = 0;
		while (idx > 0)
		{
			ret += tree[idx];
			idx -= (idx & -idx);
		}
		return ret;
	}
};

int n, m;

// parametric search
// return the first index 'idx' satisfying [ SUM(arr[1]~arr[idx]) >= sum ]
int getGroupNum(Fenwick & fenwick, const int & sum)
{
	int l = 1, r = n; // index
	int ret = n;

	while (l <= r)
	{
		const int mid = (l + r) / 2;
		if (fenwick.sum(mid) >= sum)
		{
			r = mid - 1;
			ret = min(ret, mid);
		}
		else l = mid + 1;
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	// input
	scanf("%d", &n);
	Fenwick fenwick(n + 1); // create FenwickTree
	for (int i = 1; i <= n; ++i)
	{
		int num; scanf("%d", &num);
		fenwick.add(i, num);
	}

	// query
	scanf("%d", &m);
	while (m--)
	{
		int a, b, val;
		scanf("%d", &a); // operation type

		switch (a)
		{
		case 1: // arr[b] += val
			scanf("%d %d", &b, &val);
			fenwick.add(b, val);
			break;

		case 2: // print the group number that include 'b'
			scanf("%d", &b);
			printf("%d\n", getGroupNum(fenwick, b));
			break;
		}
	}
	return 0;
}
