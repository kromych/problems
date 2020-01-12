#include <string>
#include <iostream>

using namespace std;

bool isPalindrome(const string& s) 
{
    const int n = s.size();
    
    int begin = 0;
    int end = n - 1;
    
    while (begin < end)
    {
        while (begin < end && !((s[begin] <= 'Z' && s[begin] >= 'A') || (s[begin] <= 'z' && s[begin] >= 'a') || (s[begin] <= '9' && s[begin] >= '0')))
        {
            ++begin;
        }

        while (begin < end && !((s[end] <= 'Z' && s[end] >= 'A') || (s[end] <= 'z' && s[end] >= 'a') || (s[end] <= '9' && s[end] >= '0')))
        {
            --end;
        }
                    
        char x = s[begin];
        char y = s[end];
        
        if (x <= 'Z' && x >='A')
        {
            x += ('a' - 'A');
        }

        if (y <= 'Z' && y >='A')
        {
            y += ('a' - 'A');
        }
        
        if (x != y)
        {
            return false;
        }
        
        ++begin;
        --end;
    }
    
    return true;
}

int main()
{
	cout << isPalindrome("0P") << endl;
}
