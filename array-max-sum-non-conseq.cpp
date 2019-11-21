/*
    Find the maximum sum of non-consequiutive items
    in an array.
*/

#include <cstdint>
#include <array>
#include <list>
#include <algorithm>
#include <iostream>

constexpr   std::size_t             N       = 4;
const       std::array<double, N>   input   = {4, 1, 1, 4};

std::list<unsigned> indices;

template<typename T>
unsigned get_sum(const std::list<T> l)
{
    unsigned sum = 0;

    for (const auto& i : l)
    {
        sum += input[i];
    }

    return sum;
}

template<typename T>
void print(const std::list<T> l)
{
    for (const auto& i : l)
    {
        std::cout << "input[" << i << "] = " << input[i] << ' ';
    }

    std::cout << std::endl;
}

unsigned form(unsigned i)
{
    unsigned max = 0;
    unsigned candidate  = 0;

    for (auto j = i; j < N - 2; ++j)
    {
        indices.push_back(j + 2);

        candidate = form(j + 2);
        if (candidate > max)
        {
            max = candidate;
        }

        indices.pop_back();
    }

    print(indices);

    candidate = get_sum(indices);

    return candidate > max ? candidate : max;
}

int main()
{
    for (auto i = 0; i < N; ++i)
    {
        indices.push_back(i);
        auto s = form(i);
        std::cout << "Sum: " << s << std::endl;
        indices.pop_back();
    }

    return 0;
}
