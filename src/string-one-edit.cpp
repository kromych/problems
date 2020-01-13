/*
	Given two strings s and t, determine if they are both one edit distance apart.

	Note: 

	There are 3 possiblities to satisify one edit distance apart:

	    Insert a character into s to get t
	    Delete a character from s to get t
	    Replace a character of s to get t

	Example 1:

	Input: s = "ab", t = "acb"
	Output: true
	Explanation: We can insert 'c' into s to get t.

	Example 2:

	Input: s = "cab", t = "ad"
	Output: false
	Explanation: We cannot get t from s by only one step.

	Example 3:

	Input: s = "1203", t = "1213"
	Output: true
	Explanation: We can replace '0' with '1' to get t.

*/

#include <string>
#include <iostream>

using namespace std;

bool isOneEditDistance(const string& s, const string& t) 
{
    const size_t n = s.size();
    const size_t m = t.size();

    if (n > m + 1 || m > n + 1)
    {
    	return false;
    }

    if (n == 0 && m == 0)
    {
    	return false;
    }

    if (n == 0 || m == 0)
    {
    	return true;
    }

    if (n == 1 && m == 1 && s[0] != t[0])
    {
    	return true;
    }
    
    if (n == 1 && m == 1 && s[0] == t[0])
    {
    	return false;
    }
    
    int i = 0;
    int j = 0;

    int edits = 0;

    while (i < n && j < m)
    {
    	if (s[i] == t[j])
    	{
    		++i;
    		++j;
    	}
    	else
    	{
    		if (i < n - 1 && s[i+1] == t[j])
    		{
	    		++i; ++i;
	    		++j;

    		}
    		else if (j < m - 1 && s[i] == t[j+1])
    		{
	    		++i;
	    		++j; ++j;    			
    		}
    		else if (i < n - 1 && j < m - 1 && s[i+1] == t[j+1])
    		{
	    		++i; ++i;
	    		++j; ++j;   			    			
    		}
    		else if (i == n - 1 && j == m - 1 && edits == 0)
    		{
    			return true;
    		}
    		else
    		{
    			return false;
    		}

    		++edits;
    	}
    }

	return (edits == 1 && i == n && j == m) || 
			(edits == 0 && ((i == n && j == m-1) || (i == n-1 && j == m)));
}


int main()
{
	cout << isOneEditDistance("ab", "acb") << endl;
	cout << isOneEditDistance("cab","ad") << endl;
	cout << isOneEditDistance("1203","1213") << endl;
	cout << isOneEditDistance("a","ac") << endl;
	cout << isOneEditDistance("ab","ac") << endl;
	cout << isOneEditDistance("ab","ba") << endl;
}
