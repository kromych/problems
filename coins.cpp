/*
    Given a set of coin values { c1 , c 2 , . . . , ck } 
    and a target sum of money n, form the sum n 
    using as few coins as possible.
*/

#include <climits>
#include <algorithm>
#include <map>
#include <vector>
#include <iostream>

const std::vector<int> coins = {1, 2, 5, 20};

int solve_recursive(int x);
int solve_memoization(int x);

int solve_recursive(int x) 
{
    if (x < 0) 
        return std::numeric_limits<int>::max() - 1;
    if (x == 0) 
        return 0;
    
    int best = std::numeric_limits<int>::max() - 1;
    for (auto c : coins) 
    {
        best = std::min(best, solve_recursive(x-c)+1);
    }
    
    return best;
}

int solve_memoization(int x) 
{
    static std::map<int, int> memo;

    if (x < 0) 
        return std::numeric_limits<int>::max() - 1;

    if (x == 0) 
        return 0;

    auto it = memo.find(x);
    if (it != memo.end())
        return it->second;

    int best = std::numeric_limits<int>::max() - 1;
    for (auto c : coins) 
    {
        best = std::min(best, solve_memoization(x-c)+1);
        std::cout << x << ',' << c << ',' << best << '\n';
    }

    memo[x] = best;

    return best;
}

void solve_dynamic(int x) 
{
    std::map<int, int> memo;

    memo[0] = 0;
    for (int i = 1; i <= x; ++i)
    {
        memo[i] = std::numeric_limits<int>::max() - 1;
        for (auto c : coins) 
        {
            if (i - c >= 0)
            {
                memo[i] = std::min(memo[i], memo[i-c]+1);
                std::cout << i << ',' << c << ',' << memo[x] << '\n';
            }
        }
    }
}

int main()
{
    int money = 100;
    //solve_recursive(money);
    //solve_memoization(money);
    solve_dynamic(money);
}