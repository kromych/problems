#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& ost, const vector<int>& v)
{
	ost << '[';

	if (!v.empty())
	{
		const int n = v.size();

		for (int i = 0; i < n - 1; ++i)
		{
			ost << v[i] << ',';
		}

		ost << v.back();
	}

	ost << ']';

	return ost;
}

void nextPermutation(vector<int>& nums) 
{
	// 1. Find non-increasing suffix

	const int n = nums.size();

	int pivot = -1;

	for (int i = n - 2; i >= 0; --i)
	{
		if (nums[i+1] > nums[i])
		{
			pivot = i;

			break;
		}
	}

	if (pivot >= 0)
	{
		// 2. In the suffix, find the rightmost item that is > nums[pivot],
		//    and swap it with the pivot

		int new_pivot = pivot + 1;

		for (int i = n - 1; i > pivot; --i)
		{
			if (nums[i] > nums[pivot])
			{
				new_pivot = i;
				break;
			}
		}

		// 3. Swap nums[pivot] and nums[new_pivot]

		swap(nums[pivot], nums[new_pivot]);
	}

	// 4. Reverse the suffix (what's aftre the pivot)

	reverse(nums.begin() + pivot + 1, nums.end());
}

int main()
{
	//vector<int> v{2,3,1,3,3}; // Next [2,3,3,1,3]
	vector<int> v{1,5,1}; // Next [5,1,1]

	for (int i = 0; i < 3; ++i)
	{
		cout << v << endl;
		nextPermutation(v);		
	}	
}
