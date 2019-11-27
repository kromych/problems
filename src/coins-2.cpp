/*
    Given a value N, if we want to make change for N cents, and we have infinite supply of each
    of S = {S1, S2, .. , Sm} valued coins, how many ways can we make the change? The order of coins
    does not matter.

    For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}.
    So output should be 4.

    For N = 10 and S = {2, 5, 3, 6}, there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5}
    and {5,5}.
    So the output should be 5.
*/

#include <iostream>
#include <vector>

constexpr 	int 				money_to_change 	= 4;
const 		std::vector<int> 	change_coin_values 	= {1, 2};

int change_ways(int call_level, int money, int change_coin_index)
{
	std::cout << std::string(call_level*2, ' ') << money << ';' << change_coin_index;

	if (change_coin_index < 0)
	{
		// Tried all coins already
		
		std::cout << " => 0\n";

		return 0;
	}

	if (money < 0)
	{
		// Money was less than the coin for change tried

		std::cout << " => 0\n";

		return 0;
	}

	if (money == 0)
	{
		std::cout << " => 1\n";

		// Money was equal to the coin for change tried
		return 1;
	}

	std::cout << std::endl;

	const auto change_ways_1 = change_ways(call_level + 1, money, change_coin_index - 1);
	const auto change_ways_2 = change_ways(call_level + 1, money - change_coin_values[change_coin_index], change_coin_index);

	std::cout << std::string(call_level*2, ' ') << money << ';' << change_coin_index <<
				" => " << change_ways_1 << '+' << change_ways_2 << std::endl;

	return change_ways_1 + change_ways_2;
}

int main()
{
	const auto w = change_ways(0, money_to_change, change_coin_values.size() - 1);

	std::cout << "Coins change ways: " << w << std::endl;

	return 0;
}
