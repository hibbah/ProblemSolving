/**********************************************************************************

2015.08.08

http://codeforces.com/contest/560/problem/D

- title : Equivalent Strings
- input : string str1, str2. (length <= 200,000)
- output : print the Equivalency ( YES, NO )
	* Equivalency(str1, str2)
	1. str1 == str2
			or
	2. str1 = a1 + a2, str2 = b1 + b2.
	( Equivalent(a1, b1) && Equivalent(a2, b2) ) OR ( Equivalent(a1, b2) && Equivalent(a2, b1) )

- solution : http://codeforces.com/blog/entry/19331
	One can check if lexicographically smallest string witch is equals to first string in statement the same as second.
- complexity : NlogN ( N == length )

**********************************************************************************/

#include <iostream>
#include <string>

using namespace std;

// return a string with a chain of sorted alphabetically divided the two elements
string smallest(const string & str)
{
	if (str.size() % 2 == 1) return str;
	const int len = str.size() / 2;
	string s1 = smallest(str.substr(0, len));
	string s2 = smallest(str.substr(len, len));
	return s1 < s2 ? s1 + s2 : s2 + s1;
}

int main()
{
#ifdef _CONSOLE
	freopen("input.txt", "r", stdin);
#endif

	string str1, str2;
	cin >> str1 >> str2;
	str1 = smallest(str1);
	str2 = smallest(str2);
	printf("%s\n", str1 == str2 ? "YES" : "NO");

	return 0;
}
