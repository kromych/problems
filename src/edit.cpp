/*
    Given two strings, find the minimum number of operations to turn one string into the other one.
    Operations may be: insert a symbol, remove a symbol, replace a symbol. All operations are of equal cost.
*/

#include <iostream>
#include <vector>
#include <algorithm>

const std::string x = "abcdef";
const std::string y = "acdefgh";

int edit(int n, int k)
{
	if (n == 0)
	{
		// Insert characters into the second string
		return k;
	}

	if (k == 0)
	{
		// Insert characters into the first string
		return n;
	}

	if (x[n] == y[k])
	{
		// Last chareacters are the same, nothing to do
		return edit(n-1, k-1);
	}

	return 1 + std::min(
					std::min(
						edit(n, k-1), 	// Insert into the second string
						edit(n-1, k)), 	// Remove from the first string
					edit(n-1, k-1));	// Replace
}

int main()
{
	std::cout << edit(x.size() - 1, y.size() - 1) << std::endl;
	return 0;
}
