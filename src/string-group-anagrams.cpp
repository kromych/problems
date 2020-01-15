/*
	Given an array of strings, group anagrams together.

	Example:

	Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
	Output:
	[
	  ["ate","eat","tea"],
	  ["nat","tan"],
	  ["bat"]
	]

	Note:

	    All inputs will be in lowercase.
	    The order of your output does not matter.

*/

#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>

#include <iostream>

using namespace std;

vector<vector<string>> groupAnagrams1(const vector<string>& strs) 
{
	vector<vector<string>>					ans;
	unordered_map<string, vector<string>>	str_maps;

	for (int i = 0; i < strs.size(); ++i)
	{
		string hashable(26, 1);

		for (const auto c : strs[i])
		{
			auto& ref = hashable[c - 'a'];

			ref = (ref - ' ') + 1;
		}

		str_maps[hashable].push_back(strs[i]);
	}

	for (const auto& [k, v] : str_maps)
	{
		ans.push_back(v);
	}

	return ans;	    
}

std::string countingSort(const std::string& s)
{
    std::array<int, 26> count{0};

    for (auto c : s) 
    {
    	count[c - 'a'] += 1;
    }

    std::string res;
    res.reserve(s.size());

    for (int i = 0; i < count.size(); ++i)
    {    	
        while (count[i]--) 
        {
            res.push_back(i + 'a');
        }
    }

    return res;
}
    
vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
    std::unordered_map<std::string, std::vector<string>> anagrams;

    for (auto& s : strs) 
    {
        anagrams[countingSort(s)].push_back(std::move(s));
    }

    std::vector<std::vector<string>> res;

    std::transform(
    	anagrams.begin(), 
    	anagrams.end(), 
    	std::back_inserter(res), [](auto& p) 
    	{
       		return std::move(p.second); 
    	}
    );

    return res;
}


int main()
{
	vector<string> strs {"eat", "tea", "tan", "ate", "nat", "bat"};

	const auto result = groupAnagrams(strs);

	for (const auto& ss : result)
	{
		for (const auto& s : ss)
		{
			cout << s << ' ';
		}

		cout << endl;
	}
}
