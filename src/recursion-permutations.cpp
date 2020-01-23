/*

	Given a collection of distinct integers, return all possible permutations.

	Example:

	Input: [1,2,3]
	Output:
	[
	  [1,2,3],
	  [1,3,2],
	  [2,1,3],
	  [2,3,1],
	  [3,1,2],
	  [3,2,1]
	]

*/

#include <string>
#include <vector>
#include <algorithm>

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

void backtrack(vector<vector<int>>& ans, vector<int>& tmp, int first) 
{
	// if all integers are used up

	if (first == tmp.size()) 
	{
  		ans.push_back(tmp);
	}

	for (int i = first; i < tmp.size(); i++) 
	{
  		// place i-th integer first 
  		// in the current permutation

  		swap(tmp[first], tmp[i]);

  		// use next integers to complete the permutations
  		backtrack(ans, tmp, first + 1);

  		// backtrack
  		swap(tmp[first], tmp[i]);
  	}
}

vector<vector<int>> permute(const vector<int>& nums) 
{
	vector<vector<int>> ans;
	vector<int> tmp(nums);

	backtrack(ans, tmp, 0);

	return ans;
}

int main()
{
	const auto ans = permute({1,2,3});
	cout << ans << endl;
}
