/*
    Find the maximum sum of non-consequiutive items
    in an array.
*/

#include <cstdint>
#include <array>
#include <algorithm>
#include <iostream>

const std::array<unsigned, 4> input = {4, 1, 1, 4};

unsigned solution_recursive(signed i)
{
    if (i < 0)
    {
        return 0;
    }

    if (i == 0)
    {
        return input[0];
    }

    return std::max(solution_recursive(i - 1), solution_recursive(i - 2) + input[i]);
}

int main()
{
    std::cout << "Max. sum: " << solution_recursive(input.size() - 1) << std::endl;
    return 0;
}
