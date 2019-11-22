/*
    Given 3 numbers {1, 3, 5}, tell the total number of ways 
    to form a number N using the sum of the given three numbers.
    Repetitions and different arrangements are allowed.
*/

#include <iostream>

int number_of_ways(int N)
{
    if (N < 0)
    {
        return 0;
    }

    if (N == 0)
    {
        return 1;
    }

    return number_of_ways(N - 1) + number_of_ways(N - 3) + number_of_ways(N - 5);
}

int main()
{
    std::cout << number_of_ways(2) << std::endl;
    return 0;
}