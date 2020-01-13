#include <string>
#include <array>
#include <vector>
#include <unordered_map>

#include <limits>
#include <iostream>

using namespace std;

string minWindow(const string& s, const string& t) 
{
    unordered_map<char, size_t> t_counts;

    for (auto c : t)
    {
        auto it = t_counts.find(c);
        if (it == t_counts.end())
        {
            t_counts[c] = 1;
        }
        else
        {
            ++t_counts[c];
        }
    }

    
    // Number of unique characters in t, which need to be present in the desired window.
    const size_t required = t_counts.size();

    // Left and Right pointer
    size_t l = 0, r = 0;

    // formed is used to keep track of how many unique characters in t
    // are present in the current window in its desired frequency.
    // e.g. if t is "AABC" then the window must have two A's, one B and one C.
    // Thus formed would be = 3 when all these conditions are met.
    size_t formed = 0;

    // Dictionary which keeps a count of all the unique characters in the current window.
    unordered_map<char, size_t> window_counts;

    // ans list of the form (window length, left, right)
    int ans[3] = {-1, 0, 0};

    while (r < s.length()) 
    {
        // Add one character from the right to the window
        char c = s[r];

        auto it = window_counts.find(c);
        if (it == window_counts.end())
        {
            window_counts[c] = 1;
        }
        else
        {
            ++window_counts[c];
        }

        // If the frequency of the current character added equals to the
        // desired count in t then increment the formed count by 1.
        if (t_counts.find(c) != t_counts.end() && 
            window_counts[c] == t_counts[c]) 
        {
            ++formed;
        }

        // Try and contract the window till the point where it ceases to be 'desirable'.
        while (l <= r && formed == required) 
        {
            c = s[l];

            // Save the smallest window until now.

            if (ans[0] == -1 || r - l + 1 < ans[0]) 
            {
                ans[0] = r - l + 1;
                ans[1] = l;
                ans[2] = r;
            }

            // The character at the position pointed by the
            // `Left` pointer is no longer a part of the window.

            --window_counts[c];

            if (t_counts.find(c) != t_counts.end() && 
                window_counts[c] < t_counts[c]) 
            {
                --formed;
            }

            // Move the left pointer ahead, this would help to look for a new window.

            ++l;
        }

        // Keep expanding the window once we are done contracting.
        ++r;   
    }

    return ans[0] == -1 ? "" : s.substr(ans[1], ans[2] - ans[1] + 1);
}

string minWindow2(const string& s, const string& t) 
{
    string ans="";

    int len1=s.size();
    int len2=t.size();

    if (len1<len2) 
        return ans;

    vector<int> dict(256,0);

    for(int i=0;i<len2;i++)
    {
        dict[t[i]]++;
    }
    
    int l=0, r=0, count=len2;
    int min_len=len1+1;

    while(r<len1)
    {
        dict[s[r]]--;

        if (dict[s[r]]>=0)
        {
            count--;
        }

        r++;

        while (dict[s[l]] < 0)
        {
            dict[s[l]]++;
            l++;
        }

        if (count==0)
        {
            if (r-l<min_len)
            {
                min_len=r-l;
                ans=s.substr(l,r-l);
            }

            dict[s[l]]++;
            l++;

            count++;
        }
    }

    return ans;
}

int main()
{
	cout << minWindow("ADOBECODEBANC", "ABC") << endl;
	cout << minWindow("ADOBECODEBANC", "XYZ") << endl;
	cout << minWindow("aa", "aa") << endl;
	cout << minWindow("aab", "aab") << endl;
	cout << minWindow("bba", "ab") << endl;
}
