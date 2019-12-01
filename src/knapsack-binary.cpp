/*
	Put items of maximum total value in a knapsack of capacity W.
*/

#include <iostream>
#include <vector>

constexpr int W = 50;

const std::vector<int> weights = { 10, 20,  29  };
const std::vector<int> values  = { 60, 100, 120 };

int knapsack(int capacity, int item_index)
{
	if (capacity <= 0 || item_index < 0)
	{
		return 0;
	}

	if (capacity < weights[item_index])
	{
		return 0;
	}

	// Changing " + values[item_index]" to " + weights[item_index]" below
	// calculates the max used weight.

	return std::max(
			knapsack(capacity - weights[item_index], item_index-1) + values[item_index],
			knapsack(capacity, item_index-1));
}

int main()
{
	std::cout << knapsack(W, values.size()-1) << std::endl;
	return 0;
}
