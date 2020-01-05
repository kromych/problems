#include <vector>
#include <iostream>

using namespace std;

ostream& operator<< (ostream& ost, const vector<int>& v)
{
	ost << '[';

	if (!v.empty())
	{
		const int n = v.size();
		for (size_t i = 0; i < n-1; ++i)
		{
			ost << v[i] << ',';
		}

		ost << v.back();
	}

	ost << ']';

	return ost;
}

vector<int> productExceptSelf(const vector<int>& nums) 
{
	vector<int> res(nums.size(), 1);

	const int n = nums.size();
	
	{
		int product_left = 1;

		for (int i = 1; i < n; ++i)
		{
			product_left *= nums[i-1];
			res[i] = product_left;
		}		
	}

	{
		int product_right = 1;

		for (int i = n - 2; i >= 0; --i)
		{
			product_right *= nums[i+1];
			res[i] *= product_right;
		}		
	}

	return res;    
}

int main()
{
	cout << productExceptSelf({1,2,3,4}) << endl;
}
