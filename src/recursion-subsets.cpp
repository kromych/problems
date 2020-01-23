/*

	Given a set of distinct integers, nums, return all possible subsets (the power set).

	Note: The solution set must not contain duplicate subsets.

	Example:

	Input: nums = [1,2,3]
	Output:
	[
	  [3],
	  [1],
	  [2],
	  [1,2,3],
	  [1,3],
	  [2,3],
	  [1,2],
	  []
	]

*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <typename T>
ostream& operator<< (ostream& ost, const vector<T>& v)
{
	ost << '[';

	if (!v.empty())
	{
		for (int i = 0; i < v.size() - 1; ++i)
		{
			cout << v[i] << ',';
		}

		cout << v.back();
	}

	ost << ']';

	return ost;
}

vector<vector<int>> subsets(const vector<int>& nums) // BFS
{
    vector<vector<int>> ans;

    ans.push_back({});

    for (int i = 0; i < nums.size(); ++i)
    {
    	vector<vector<int>> new_subsets;

    	for (int j = 0; j < ans.size(); ++j)
    	{
    		vector<int> subset_copy(ans[j]);

    		subset_copy.push_back(nums[i]);
    		new_subsets.push_back(subset_copy);
    	}

    	for (const auto& new_subset : new_subsets)
    	{
    		ans.push_back(new_subset);
    	}
    }

    return ans;
}

void backTrack(const vector<int>&nums, vector<int>&tmp, vector<vector<int>>&ans, int pos)
{
    ans.push_back(tmp);

    for(int i = pos; i < nums.size(); ++i)
    {
        tmp.push_back(nums[i]);

        backTrack(nums, tmp, ans, i+1);

        tmp.pop_back();
    }
}

vector<vector<int>> subsets_recursive(const vector<int>& nums) // DFS
{
    vector<vector<int>> ans;
    vector<int> tmp;

    backTrack(nums, tmp, ans, 0);

    return ans;
}

int main()
{
	const auto ans = subsets({1,2,3});
	const auto ans_recursive = subsets_recursive({1,2,3});

	cout << ans << endl;
	cout << ans_recursive << endl;
}
