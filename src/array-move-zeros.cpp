#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <iostream>

using namespace std;


void moveZeroes(vector<int>& nums) 
{
    int j = 0;
    int n = nums.size();
    
    for (int i = 0; i < n; ++i)
    {
        if (nums[i] != 0)
        {
            nums[j] = nums[i];
            j++;
        }
    }
    
    while (j < n)
    {
        nums[j] = 0;
        j++;
    }

    //memset(&nums[j], 0, sizeof(int)*(n-j));
}

int main()
{

}
