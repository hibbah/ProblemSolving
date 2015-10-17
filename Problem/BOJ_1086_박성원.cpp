/*************************************************************************************

2015.10.17
https://www.acmicpc.net/problem/1086

- input : 최대 50자리수의 서로 다른 자연수 N개(<=15), K(<=100)
- output : N개의 수를 임의의 순서로 나열하여 만든 자연수들 중, K로 나누어 떨어지는 경우의 수
- issue :
	1. 각 숫자가 최대 50자리 이므로, 정수형 자료형에 저장할 수 없음
	2. 숫자를 나열하는 모든 경우의 수 == N! (15!. 약 1조 3천억)

- solution :
	1. 자연수 A, B에 대하여 B의 자릿수를 L이라고 할 때, A와 B를 연결하여 만든 자연수를 K로 나눈 나머지는
	   (A*10^L + B) % K == ( (A % K) * 10^L + B ) % K.
	   즉, 앞에서부터 숫자를 하나씩 선택해 나열해 나가면서 매번 나머지 값을 갱신. (counting함수 재귀 호출부분)

	2. 모든 경우의 수는 최대 15!이지만, 계산과정에서 중복이 발생.
	   가령, 26개의 자연수 A~Z에 대하여 이들을 연결하여 만든 자연수 중,
	   ..IJABCD와 ..XYABCD에서, [ABCD]가 가장 뒤쪽에 나란히 존재하는데,
	   이런 경우에 대해 ABCD를 K로 나눈 나머지를 매번 중복해서 계산할 필요가 없음.

- complexity : O( 2^n * k )

*************************************************************************************/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

typedef long long ll;

int n, mod, complete; // complete == 각 자연수의 사용여부를 bitmask로 표현했을 때, 모든 자연수를 사용한 상태를 표현
ll cache[1 << 15][100]; // memoization table
ll tenMod[52]; // tenMod[e] == 10^e를 mod로 나눈 나머지
ll numMod[15]; // numMod[i] == i번째 수를 mod로 나눈 나머지
string num[15];

// return the GCD(a, b)
ll GCD(ll a, ll b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

// return the N!
ll factorial(const ll & n)
{
	ll ret = 1;
	for (ll i=2; i<=n; ++i) ret *= i;
	return ret;
}

void init()
{
	complete = (1<<n)-1; // N개의 자연수를 모두 사용했음을 나타내는 상태 (bit-mask)
	memset(cache, -1, sizeof(cache)); // memoization table initialize

	tenMod[0] = 1; // 1 % mod == 1
	for (int i = 1; i <= 50; ++i)
		tenMod[i] = (tenMod[i-1]*10) % mod;

	// 각 숫자 num[i]를 mod로 나눈 나머지값 계산
	for (int i = 0; i < n; ++i)
	{
		int r = 0;
		for (int j = 0; j < num[i].size(); ++j)
		{
			r *= 10;
			r += (num[i][j] - '0');
			r %= mod;
		}
		numMod[i] = r;
	}
}

// 현재까지 사용한 숫자들을 bitmask로 표현한 상태가 state이고, 현재까지 만들어 온 나머지 값이 R일 때,
// 남은 숫자들을 모두 사용하여 생성한 자연수가 mod로 나눠 떨어지는 경우의 수 반환
ll counting(const int state, const int R)
{
	if (state == complete) return R == 0 ? 1 : 0;

	ll & ret = cache[state][R];
	if (ret != -1) return ret;
	ret = 0;

	for (int i = 0; i < n; ++i)
	{
		if (state & (1<<i)) continue;
		ret += counting(state|(1<<i), (R * tenMod[num[i].size()] + numMod[i]) % mod);
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
	for (int i=0; i<n; ++i) cin >> num[i];
	scanf("%d", &mod);
	init();
	
	const ll cnt = counting(0, 0); // mod로 나눠 떨어지는 모든 경우의 수
	const ll allcase = factorial(n); // N개의 수를 나열하는 모든 경우의 수(N!)
	const ll gcd = GCD(cnt, allcase);
	printf("%lld/%lld\n", cnt/gcd, allcase/gcd); // 기약분수로 출력

	return 0;
}
