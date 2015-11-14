/**********************************************************************************************

2015.11.14
http://codeforces.com/contest/598/problem/C

- input : 좌표평면에서 원점을 시점으로하는 N(<=100,000)개의 벡터(x, y). (모든 벡터는 방향이 다름)
- output : 벡터들을 입력받는 순서대로 1~N까지 번호를 붙였을 때, 가장 가까운 두 벡터의 번호
- solution : 벡터 v(1, 0)를 기준으로 하는 내각(0~180)을 계산하여 정렬하고 선형 비교
- issue : 각도의 계산 => m<ath.h> 의 각종 삼각함수(매개변수, 반환값 주의)의 활용
- time complexity : O( NlogN ). (정렬시간)

**********************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<double, int> ITEM;
#define DEG first
#define NUM second

const double PI = acos(-1); // PI값 계산

int n, x, y;
vector <ITEM> list;

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	scanf("%d", &n);
	list.resize(n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d %d", &x, &y);
		double deg = atan2l(y, x) * 180.0/PI; // degree값으로 변환
		if (deg < 0) deg += 360.0; // atan2의 반환값은 [-PI, PI]이므로 각도 크기 조정
		list[i].DEG = deg;
		list[i].NUM = i+1; // 벡터의 번호
	}
	sort(list.begin(), list.end());
	list.push_back({ list.front().DEG + 360.0, list.front().NUM });
	
	int a, b;
	double minn = 999999999.0;
	for (int i = 1; i <= n; ++i)
	{
		double sub = list[i].DEG - list[i - 1].DEG; // 두 벡터가 이루는 각도
		if (sub < minn) // 더 가까울경우, 갱신
		{
			minn = list[i].DEG - list[i-1].DEG;
			a = list[i].NUM;
			b = list[i-1].NUM;
		}
	}
	printf("%d %d\n", a, b);

	return 0;
}
