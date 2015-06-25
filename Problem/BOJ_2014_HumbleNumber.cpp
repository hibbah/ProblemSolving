/**********************************************************************************

2015.06.25

https://www.acmicpc.net/problem/2014/

- title : humble number
- input : K(<=100) prime numbers, N(<=100,000)
- output : N'th Humble number
- complexity : O(N*K)

***********************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector <int> VI;

int k, n;
VI prime, pos, humble(1, 1);

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d %d", &k, &n);
	prime = VI(k);
	pos = VI(k, 0); // save the index of the next multiply Humble number for each prime number
	
	for (int i = 0; i < k; ++i) scanf("%d", &prime[i]);
	while (humble.size() <= n)
	{
		int num = 2100000000;
		for (int i = 0; i < k; ++i)
			num = min(num, prime[i] * humble[pos[i]]);
		
		for (int i = 0; i < k; ++i)
		{
			if (num == humble[pos[i]] * prime[i]) ++pos[i];
		}
		humble.push_back(num);
	}
	printf("%d\n", humble.back());

	return 0;
}
