/*********************************************************************************

2015.09.17
http://codeforces.com/contest/579/problem/D
( Codeforces#320 (div2)_D )

- title : "OR" Game
- input : N(<=200,000), K(<=10), X(<=8)
- output : N개의 숫자들 중. 임의의 숫자에 X를 곱하는 연산을 최대 K번 수행한 뒤,
	모든 숫자들을 비트OR연산한 결과값이 최대가 되는 값을 출력
- issue :
	1. 모든 경우의 수 == 연산을 0~K번 하는 경우의 수 == 1+N^1+N^2+N^3+...+N^K
	2. 연산은 K번 모두 사용하는 것이 이득인가 ?
	3. N개의 정수들 중. 어떤 숫자에 X를 곱하는 것이 이득인가 ?
- solution :
- 자릿수가 높을수록 수(이진수)의 값은 커진다.
- X>=2 이므로, 어떤 숫자에 X를 곱할 때마다 이진수의 자릿수가 증가한다.
- 자릿수가 높은 이진수가 존재하면 bitwiseOR연산의 결과값이 커진다.
=> "하나의 숫자"에 "연산횟수 K를 모두 사용"하여 곱하는것이 이득이다.

1. bitCnt[i] : i번 비트에 set(1)인 숫자의 갯수를 저장
2. N개의 각 숫자마다 X^K를 곱한 결과를 bitCnt[]에 등록하여 OR연산 계산
3. 1~2의 결과값들중 최대값을 출력

- complexity :
	indexTree solution : O(4N+NlogN)
	'yukariko' solution : O(64N)
	editorial solution : O(N)

*********************************************************************************/

// yukariko solution

#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

int n, k;
int bitCnt[64];
ull x, arr[200001];

// counting the num in binary ( d=1 : set // d=-1 : reset )
void add(ull num, const ull & d)
{
	for (int i = 0; i < 64 && num; ++i)
	{
		if (num & 1) bitCnt[i] += d;
		num >>= 1;
	}
}

// return the number converting the bitCnt[] as decimal
ull getNum()
{
	ull ret = 0, exp = 1;
	for (int i = 0; i < 64; ++i)
	{
		ret += (bitCnt[i] > 0 ? exp : 0);
		exp <<= 1;
	}
	return ret;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d %llu", &n, &k, &x);
	for (int i = 0; i < n; ++i)
	{
		scanf("%llu", &arr[i]);
		add(arr[i], 1);
	}

	ull maxx = 0, mul = 1;
	for (int i = 0; i < k; ++i) mul *= x;
	for (int i = 0; i < n; ++i)
	{
		ull target = arr[i] * mul;
		add(arr[i], -1); // reset arr[i]
		add(target, 1); // set arr[i]*mul
		maxx = max(maxx, getNum()); // bitwise OR for N numbers
		add(target, -1); // reset arr[i]*mul
		add(arr[i], 1); // set arr[i]
	}
	printf("%llu\n", maxx);

	return 0;
}

/****** using INDEX - TREE code

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int n, k;
ull x;
vector <ull> vi;

class SEGTREE
{
public:
	int n;
	vector <ull> tree;

	SEGTREE(const vector <ull> & vi)
	{
		n = vi.size();
		tree.resize(4 * n);
		init(vi, 0, n - 1, 1);
	}

	ull init(const vector <ull> & vi, const int left, const int right, const int node)
	{
		if (left == right) return tree[node] = vi[left];
		const int mid = (left + right) / 2;
		return tree[node] = init(vi, left, mid, node * 2) | init(vi, mid + 1, right, node * 2 + 1);
	}

	ull query(const int & a, const int & b)
	{
		return query(a, b, 1, 0, n - 1);
	}
private:
	ull query(const int & a, const int & b, const int node, const int & nodeleft, const int & noderight)
	{
		if (b < nodeleft || noderight < a) return 0;
		if (a <= nodeleft && noderight <= b) return tree[node];
		const int mid = (nodeleft + noderight) / 2;
		return query(a, b, node * 2, nodeleft, mid) | query(a, b, node * 2 + 1, mid + 1, noderight);
	}
};

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d %llu", &n, &k, &x);
	vi = vector <ull>(n);
	for (int i = 0; i < n; ++i) scanf("%llu", &vi[i]);

	SEGTREE segtree(vi);
	ull maxx = 0, mul = 1;
	for (int i = 0; i < k; ++i) mul *= x;
	for (int i = 0; i < n; ++i)
	{
		ull target = vi[i] * mul;
		ull left = i == 0 ? 0 : segtree.query(0, i - 1);
		ull right = i == n - 1 ? 0 : segtree.query(i + 1, n - 1);
		maxx = max(maxx, target | left | right);
	}
	printf("%llu\n", maxx);

	return 0;
}

*/


/************** CF :: editorial code

#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

const int SIZE = 2e5;
ull arr[SIZE], pre[SIZE], suf[SIZE];

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	int n, k, x;
	scanf("%d %d %d", &n, &k, &x);
	for (int i = 0; i < n; ++i) scanf("%llu", &arr[i]);

	pre[0] = arr[0]; suf[n - 1] = arr[n - 1];
	for (int i = 1; i < n; ++i) pre[i] = pre[i - 1] | arr[i];
	for (int i = n - 2; i >= 0; --i) suf[i] = suf[i + 1] | arr[i];

	ull mul = 1, maxx = 0;
	while (k--) mul *= x;
	for (int i = 0; i < n; ++i)
		maxx = max(maxx, (arr[i] * mul | pre[i - 1] | suf[i + 1]));

	printf("%llu\n", maxx);

	return 0;
}

*/