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
#include <queue>

/* Money to change */
constexpr 	auto 				money 		= 10;

/* Coin values for changing */
const 		std::vector<int> 	coin_change = {2, 5, 3, 6};

struct bfs_state_t
{
	int money;
	int coin_change_index;

	bfs_state_t(int _money, int _coin_change_index) : money(_money), coin_change_index(_coin_change_index)
	{		
	}

	bfs_state_t() : bfs_state_t(-1, -1)
	{		
	}
};

int coin_change_ways_bfs()
{
	int 					   ways = 0;
	std::queue<bfs_state_t>    queue;

	queue.push(bfs_state_t(money, coin_change.size() - 1));

	while (!queue.empty())
	{
		const auto front = queue.front();
		queue.pop();

		if (front.coin_change_index < 0)
		{
			// Ran out of coin change values 

			continue;
		}

		if (front.money < 0)
		{
			// Ran out of money
			continue;
		}

		if (front.money == 0)
		{
			// Just enough

			++ways;

			continue;
		}

		queue.push(
			bfs_state_t(
				front.money, 
				front.coin_change_index - 1));

		queue.push(
			bfs_state_t(
				front.money - coin_change[front.coin_change_index], 
				front.coin_change_index));						
	}

	return ways;
}

int main()
{
	const auto ways = coin_change_ways_bfs();

	std::cout << "Ways: " << ways << std::endl;

	return 0;
}
