/*

	Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

	Example 1:

	Input: "aba"
	Output: True

	Example 2:

	Input: "abca"
	Output: True
	Explanation: You could delete the character 'c'.

	Note:

	    The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
*/

#include <string>
#include <queue>
#include <stack>
#include <tuple>
#include <iostream>

using namespace std;

/* works not always */
bool validPalindrome1(const string& s) 
{
    int l = 0;
    int r = s.size() - 1;

    int skipped = 0;

    while (l < r && skipped < 2)
    {
    	if (s[l] != s[r])
    	{
    		if (r > 0 && s[l] == s[r-1])
    		{
    			--r;
    			++skipped;    			
    		}
    		else if (l < s.size() - 1 && s[l+1] == s[r])
    		{
    			++l;
    			++skipped;
    		}
    		else
    		{
    			return false;
    		}
    	}
    	else
    	{
    		++l;
    		--r;    		
    	}
    }

    return skipped < 2;
}

bool validPalindrome(const string& str) 
{
    int later[512][3];

    later[0][0] = 0;				// left
    later[0][1] = str.size() - 1;	// right
    later[0][2] = 0;				// skipped

    int later_pos = 1;

    while (later_pos != 0)
    {
	    --later_pos;

	    int l = later[later_pos][0]; // left
	    int r = later[later_pos][1]; // right
	    int s = later[later_pos][2]; // skipped

    	if (str[l] != str[r])
    	{
    		if (l+1 <= r && s < 1)
    		{
			    later[later_pos][0] = l+1;		// left
			    later[later_pos][1] = r;		// right
			    later[later_pos][2] = s+1;	// skipped

			    ++later_pos;
    		}

    		if (l <= r-1 && s < 1)
    		{
			    later[later_pos][0] = l;		// left
			    later[later_pos][1] = r-1;		// right
			    later[later_pos][2] = s+1;	// skipped

			    ++later_pos;
    		}
    	}
    	else
    	{
    		if (l+1 <= r-1)
    		{
			    later[later_pos][0] = l+1;	// left
			    later[later_pos][1] = r-1;	// right
			    later[later_pos][2] = s;	// skipped

			    ++later_pos;
    		}
    		else
    		{
    			return true;
    		}
    	}
    }

    return false;
}


int main()
{
	cout << validPalindrome("abca") << endl;
	cout << validPalindrome("aabdcaa") << endl;
	cout << validPalindrome("aba") << endl;
	cout << validPalindrome("a") << endl;
	cout << validPalindrome("") << endl;
	cout << validPalindrome("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga") << endl;
	cout << validPalindrome("ebcbbececabbacecbbcbe") << endl;
}
