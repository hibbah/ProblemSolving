/**********************************************************************************

2015.09.06
https://www.acmicpc.net/problem/10258
(ACMICPC Asia Regional - Daejeon Internet Competition 2014 problem J)

- title : Switch Array
- input : 0/1로 구성된 이진수 B. (2 <= |B| <= 31)
- output : B를 0으로 만들기 위해 필요한 최소 연산 횟수
- operation : 
	1. 가장 오른쪽에 있는 비트는 자유롭게 toggle 가능.
	2. (왼쪽부터)비트i를 toggle시키기 위해서는 비트i+1이 반드시 '1'이고, i+1이후의 모든 비트는 '0'이어야 함.
- solution :
	1. B -> 0이 아닌, 0 -> B를 만드는 최소 횟수를 계산.
	2. 특정 비트를 toggle시키기 위해서는 해당 비트의 우측에 존재하는 비트들만 필요.
	   즉, 가장 왼쪽에 있는 비트부터 시작해서 한 번 맞춘 비트는 다시 조작할 필요가 없음.
	4. 가장 오른쪽을 0번째로 시작했을 때, 비트i를 toggle시키기 위한 최소 연산 횟수 == 2^i
	   단, 비트i를 toggle시켰을 때, 비트i+1은 항상 '1'이고 이후의 모든 비트틑 '0'.
	5. 초기 문자열을 str = "00...000"으로 놓고, str을 B로 만들기위해, 가장 왼쪽 비트부터 차례대로 변환.
	   str[i] != B[i]일 경우, str[i]를 toggle시키기 위해 2^i번 연산이 필요하고, 이 때 str[i+1] = '1'로 변환.
- Complexity : O(|B|)

***********************************************************************************/

#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int t;
ll toggleCnt[31] = { 1, 2 }; // 오른쪽에서부터 i번 bit를 toggle시키기위해 필요한 최소 연산 횟수
string B, str;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	for (int i = 2; i < 31; ++i) toggleCnt[i] = toggleCnt[i - 1] * 2;

	scanf("%d", &t);
	while (t--)
	{
		cin >> B;
		str = string(B.length(), '0');

		ll ret = 0;
		for (int i = 0; i < B.length() - 1; ++i)
		{
			if (B[i] != str[i]) // 문자가 다를경우
			{
				ret += toggleCnt[B.size() - i - 1]; // str[i]를 toggle시키기 위해 필요한 최소 연산 횟수
				str[i + 1] = '1'; // str[i]를 toggle시키고난 뒤, str[i+1]는 반드시 '1'
			}
		}
		if (B.back() != str.back()) ++ret;
		printf("%lld\n", ret);
	}
	return 0;
}
