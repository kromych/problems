/*
    The Longest Increasing Subsequence (LIS) problem is to find the length of the 
    longest subsequence of a given sequence such that all elements of the subsequence 
    are sorted in increasing order.

    For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 
    and LIS is {10, 22, 33, 50, 60, 80}.
*/

#include <iostream>
#include <array>
#include <algorithm>

std::array<int, 9> input = {10, 22, 9, 33, 21, 50, 41, 60, 80};

int lis(int n)
{
    int lis_n = 1;

    for (auto i = 0; i < n; ++i)
    {
        auto lis_i = lis(i);

        lis_n = std::max(input[i] < input[n] ? lis_i + 1 : lis_i, lis_n);
    }

    return lis_n;
}

int main()
{
    std::cout << "LIS length: " << lis(input.size() - 1) << std::endl;

    return 0;
}
