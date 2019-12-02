/*
    In an array, find a subarray whose items are of the maximum sum.
*/

#include <iostream>
#include <vector>
#include <limits>

const std::vector<int> a = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
//const std::vector<int> a = { -2, 2, -3 };

int max_sum(int i, int j)
{
	return 0;
}

int kadane()
{
	int sum = a[0];
	int max_sum = sum;

	for (const auto& item : a)
	{
		sum = std::max(item, sum + item);
		max_sum = std::max(sum, max_sum);
	}

	return max_sum;
}

int main()
{
	std::cout << "Max subarray sum " << max_sum(0, a.size()-1) << std::endl;
	std::cout << "Max subarray sum (Kadane) " << kadane() << std::endl;

	return 0;
}
