/*
	Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

	Example 1:

	Input:nums = [1,1,1], k = 2
	Output: 2

	Note:

	    The length of the array is in range [1, 20,000].
	    The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

*/

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;


// hashmap + preSum
/*
    1. Hashmap<sum[0,i - 1], frequency>
    2. sum[i, j] = sum[0, j] - sum[0, i - 1]    --> sum[0, i - 1] = sum[0, j] - sum[i, j]
           k           sum      hashmap-key     -->  hashmap-key  =  sum - k
    3. now, we have k and sum.  
          As long as we can find a sum[0, i - 1], we then get a valid subarray
         which is as long as we have the hashmap-key,  we then get a valid subarray
    4. Why don't map.put(sum[0, i - 1], 1) every time ?
          if all numbers are positive, this is fine
          if there exists negative number, there could be preSum frequency > 1
*/

int subarraySum(vector<int>& nums, int k) 
{
    int count = 0;
    
    unordered_map<int, int> hash; // (key, value) = (sum, count)
    hash[0] = 1; 
    
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) 
    {
        sum += nums[i];

        if (hash.count(sum - k))
        {
            count += hash[sum - k];
        }

        ++hash[sum];
    }
    
    return count; 
}

int subarraySum1(const vector<int>& nums, int k) 
{
	int ans = 0;

	const int n = nums.size();

	vector<int> sums;

	{
		int s = 0;

		for (int i = 0; i < n; ++i)
		{
			s += nums[i];
			sums.push_back(s);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			if (sums[j] - sums[i] + nums[i] == k)
			{
				++ans;
			}
		}
	}

	return ans;
}

int main()
{
	cout << subarraySum({1,1,1}, 2) << endl;
}
