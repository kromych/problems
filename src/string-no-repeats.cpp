#include <string>
#include <map>
#include <iostream>

using namespace std;

int lengthOfLongestSubstring(const string& s) 
{
    if (s.empty())
    {
        return 0;
    }

    if (s.size() == 1)
    {
        return 1;
    }

    int startIdx = 0;
    int global_max = 0;
    
    map<char, int> chars;
    
    for (int i = 0; i < s.size(); ++i)
    {
        const auto it = chars.find(s[i]);
                    
        if (it != chars.end())
        {            
            startIdx = max(startIdx, it->second + 1);
            cout << "Start: " << startIdx << endl;
        }

        global_max = max(global_max, i - startIdx + 1);

        chars[s[i]] = i;        
    }

    return global_max ? global_max : s.size();
}

int main()
{
    // cout << lengthOfLongestSubstring(" ") << endl;              // 1
    // cout << lengthOfLongestSubstring("au") << endl;             // 2
    // cout << lengthOfLongestSubstring("aab") << endl;            // 2
    cout << "aabaab!bb" << lengthOfLongestSubstring("aabaab!bb") << endl;      // 3
    // cout << lengthOfLongestSubstring("pwwkew") << endl;         // 3
    // cout << lengthOfLongestSubstring("bbbbb") << endl;          // 1
    // cout << lengthOfLongestSubstring("abcabcbb") << endl;       // 3
}
