/*
	Given a string, find the length of the longest substring T that contains at most k distinct characters.

	Example 1:

	Input: s = "eceba", k = 2
	Output: 3
	Explanation: T is "ece" which its length is 3.

	Example 2:

	Input: s = "aa", k = 1
	Output: 2
	Explanation: T is "aa" which its length is 2.

*/

#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

int lengthOfLongestSubstringKDistinct(const string& s, int k) 
{	
	const size_t n = s.size();

	if (n == 0 || k == 0) 
	{
		return 0;
	}

	// sliding window left and right pointers

	int left = 0;
	int right = 0;

	// hashmap character -> its rightmost position 
	// in the sliding window
	map<char, int> map;

	int max_len = 1;

	while (right < n) 
	{
		// add new character and move right pointer

		map[s[right]] = right;

		if (map.size() == k + 1) 
		{
			// delete the leftmost character

			auto del_it = min_element(
				map.begin(), 
				map.end(), 
				[](const auto& l, const auto& r)
				{ 
					return l.second < r.second;
				});

			// move left pointer of the slidewindow

			left = del_it->second + 1;

			// delete

			map.erase(del_it->first);
		}

		max_len = max(max_len, right - left + 1);

		++right;
	}

	return max_len;
}

int lengthOfLongestSubstringKDistinct1(const string& s, int k) 
{
    vector<int> count(256, 0); // ASCII

    int res = 0;
    int length = 0;
    int start = 0;

    for (int end = 0; end < s.size(); end++) 
    {
        if (count[s[end]] == 0) 
        {
            length++;
        }

        count[s[end]]++;
        
        if (length > k) 
        {
            int flag = 1;
            while (flag) 
            {
                count[s[start]]--;

                if(count[s[start]] == 0) 
                {
                    flag = 0;
                }
                
                start++;
            }

            length--; 
        }

        res = max(res, end - start + 1);
    }

    return res;
}

int main()
{
	cout << lengthOfLongestSubstringKDistinct("eceba", 2) << endl;
	//cout << lengthOfLongestSubstringKDistinct("aa", 1) << endl;	
}
