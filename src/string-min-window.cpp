#include <string>
#include <array>
#include <limits>
#include <iostream>

using namespace std;


struct pos_min_max_t
{
    int min;
    int max;
    
    pos_min_max_t() : min(numeric_limits<int>::max()), max(numeric_limits<int>::min())
    {            
    }
};

string minWindow(const string& s, const string& t) 
{
	if (t.size() > s.size())
	{
		return "";
	}

    pos_min_max_t pos_map[256];
    
    for (int i = 0; i < s.size(); ++i)
    {
        pos_map[s[i]].min = min(pos_map[s[i]].min, i);
        pos_map[s[i]].max = max(pos_map[s[i]].max, i);
    }

    int left_min = numeric_limits<int>::max();
    int left_max = numeric_limits<int>::min();

    int right_min = numeric_limits<int>::max();
    int right_max = numeric_limits<int>::min();

    for (int i = 0; i < t.size(); ++i)
    {
    	const int pos_min = pos_map[t[i]].min;

    	if (pos_min >= s.size() || pos_min < 0)
    	{
    		return "";
    	}

    	left_min = min(left_min, pos_min);
    	left_max = max(left_max, pos_min);

    	const int pos_max = pos_map[t[i]].max;

    	if (pos_max >= s.size() || pos_max < 0)
    	{
    		return "";
    	}

    	right_min = min(right_min, pos_max);
    	right_max = max(right_max, pos_max);
    }

    int left;
    int right;

	if (left_min == left_max && right_min == right_max)
	{
		right = right_max;
		left = left_min;		
	}
    else if (left_min == right_min)
    {
		left = left_min;
		right = min(left_max, right_max);
    }
    else if (left_max == right_max)
    {
		right = right_max;
		left = min(left_min, right_min);
    }
    else // if (left_min < right_min && left_max < right_max)
    {
		if (left_max - left_min < right_max - right_min)
		{
			right = left_max;
			left = left_min;
		}
		else
		{
			right = right_max;
			left = right_min;
		}
    }

    return s.substr(left, right-left+1);
}

int main()
{
	cout << minWindow("ADOBECODEBANC", "ABC") << endl;
	cout << minWindow("ADOBECODEBANC", "XYZ") << endl;
	cout << minWindow("aa", "aa") << endl;
	cout << minWindow("aab", "aab") << endl;
	cout << minWindow("bba", "ab") << endl;
}
