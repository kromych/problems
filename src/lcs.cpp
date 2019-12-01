/*
	Given two sequences, find the length of longest subsequence present in both of them. 
*/

#include <iostream>
#include <vector>

const std::vector<char> x = {'a','b','c','d','e','f'};
const std::vector<char> y = {'a',    'c','d','e','f','g','h'};

int lcs(int n, int k)
{
	if (n == 0 || k == 0)
	{
		return 0;
	}

	if (x[n] == y[k])
	{
		return 1 + lcs(n-1, k-1);
	}

	return std::max(lcs(n-1, k), lcs(n, k-1));
}

int main()
{
	std::cout << lcs(x.size()-1, y.size()-1) << std::endl;
	return 0;
}
