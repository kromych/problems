/*
    Given a string, find the length of the longest substring without repeating characters.

    Example 1:

        Input: "abcabcbb"
        Output: 3 
        Explanation: The answer is "abc", with the length of 3. 

    Example 2:

        Input: "bbbbb"
        Output: 1
        Explanation: The answer is "b", with the length of 1.

    Example 3:

        Input: "pwwkew"
        Output: 3
        Explanation: The answer is "wke", with the length of 3. 
                     Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

*/

#include <string>
#include <vector>
#include <unordered_map>

#include <iostream>

using namespace std;
   
int length_of_longest_substring(const string& s) 
{
/*
    int n = s.size();
    
    unordered_set<char> set;
    
    int ans = 0, i = 0, j = 0;
    
    while (i < n && j < n) 
    {
        // try to extend the range [i, j]
        
        if (set.find(s[j]) == set.end())
        {
            set.insert(s[j++]);
            ans = max(ans, j - i);
        }
        else 
        {
            set.erase(s[i++]);
        }
    }
    
    return ans;
*/

    int n = s.size();
    int subStringStartIdx = 0;
    int longestLength = 0;
    
    unordered_map<char, int> startIdxMap; // current index of character
    
    // try to extend the range [i, j]
    
    for (int j = 0; j < n; ++j) 
    {
        const auto ch = s[j];
        const auto it = startIdxMap.find(ch);
        
        if (it != startIdxMap.end())
        {
            const auto oldStartIdx = it->second;
            subStringStartIdx = max(oldStartIdx, subStringStartIdx);
        }
        
        longestLength = max(longestLength, j - subStringStartIdx + 1);

        startIdxMap[ch] = j + 1;
    }
    
    return longestLength;

/*
    int n = s.size();
    int i = 0;
    int ans = 0;
    
    vector<int> char_map(128, 0);
    
    for (int j = 0; j < n; ++j) 
    {
        const char c = s[j];

        i = max(char_map[c], i);
        ans = max(ans, j + 1 - i);

        char_map[c] = j + 1;
    }
*/  

/*
        int n = s.size();
        int i = 0;
        int longest_length = 0;
        
        int index[128];

        memset(index, 0, sizeof(index));
                
        for (int j = 0; j < n; ++j) 
        {
            const char c = s[j];
            
            if (index[c] > i)
            {
                i = index[c];
            }
            
            if (j + 1 - i > longest_length)
            {
                longest_length = j + 1 - i;
            }
            
            index[c] = j + 1;
        }
        
        return longest_length;
*/
}

int main()
{
    cout << length_of_longest_substring("pwwkew") << endl;
    cout << length_of_longest_substring("abba") << endl;

    return 0;
}
