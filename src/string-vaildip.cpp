#include <string>
#include <iostream>

using namespace std;

string validIPAddress(const string& ip) 
{
	if (ip.size() < 7)
	{
		return "Neither";
	}

    constexpr uint64_t oct_v6 = 1<<2;
    constexpr uint64_t oct_v4 = 1<<3;
    constexpr uint64_t sep_col = 1 << 4;
    constexpr uint64_t sep_dot = 1 << 5;
    constexpr uint64_t v4 = 1 << 6;
    constexpr uint64_t v6 = 1 << 7;

    constexpr uint64_t neither = 0;

    const int n = ip.size();

    int oct_start = 0;
    int oct_end = 0;
    int octet_count = 1;
    
    uint64_t expected = neither;
    uint64_t state = neither;

	if (ip[1] == '.' || ip[2] == '.' || ip[3] == '.')
	{
	    expected = oct_v4;
	    state = oct_v4;		
	}
	else if (ip[1] == ':' || ip[2] == ':' || ip[3] == ':' || ip[4] == ':' || ip[5] == ':')
	{
	    expected = oct_v6;
	    state = oct_v6;		
	}
	else
	{
		return "Neither";
	}
    
    for (int i = 0; i < n; ++i)
    {
        if ((state & expected) == 0)
        {
            state = neither;
            goto out;                
        }
            
        switch (ip[i])
        {
            case 'a' ... 'f':
            case 'A' ... 'F':
                expected = oct_v6 | sep_col;
                state = oct_v6;            

            case '0' ... '9':
                                    
                if (expected & oct_v4)
                {
	                if (oct_end-oct_start >= 3)
	                {
	                    state = neither;
	                    goto out;
	                }

	                if ((oct_end-oct_start >= 1) && (ip[oct_start] == '0'))
	                {
	                    state = neither;
	                    goto out;
	                }

	                if (oct_end-oct_start >= 2 && ip[oct_start] >= '2' && ip[oct_start+1] >= '5' && ip[oct_start+2] > '5')
	                {
	                    state = neither;
	                    goto out;
	                }

                    if (i == n - 1)
                    {
                    	state = octet_count == 4 ? v4 : neither;
                    }
                    else
                    {
	                    expected = oct_v4 | sep_dot;
	                    state = oct_v4;
                    }                    
                }                    
                else if (expected & oct_v6)
                {                  
	                if (oct_end-oct_start >= 4)
	                {
	                    state = neither;
	                    goto out;
	                }

                    if (i == n - 1)
                    {
                    	state = octet_count == 8 ? v6 : neither;
                    }
                    else
                    {
	                    expected = oct_v6 | sep_col;
	                    state = oct_v6;
                    }
                }
                else
                {
                    state = neither;
                    goto out;
                }
                
                ++oct_end;
                
                break;
                
            case '.':

            	if ((expected & sep_dot) == 0 || octet_count >= 4)
                {
                    state = neither;
                    goto out;
                }
                
                expected = oct_v4;
                state = oct_v4;
                    
                oct_end = i+1;
                oct_start = i+1;
                
                ++octet_count;
                
                break;
                
            case ':':

                if ((expected & sep_col) == 0 || octet_count >= 8)
                {
                    state = neither;
                    goto out;
                }

                expected = oct_v6;
                state = oct_v6;
              
                oct_end = i+1;
                oct_start = i+1;

                ++octet_count;

                break;
                                    
            default:
                
                state = neither;
                goto out;
        }
    }        
    
out:
    
    if (state & v4) return "IPv4";
    if (state & v6) return "IPv6";

	return "Neither";
}

int main()
{
	cout << validIPAddress("00.0.0.0") << endl;
	cout << validIPAddress("1111.4.5.6") << endl;
	cout << validIPAddress("2001:0db8:85a3:00000:0:8A2E:0370:7334") << endl;
	cout << validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:733a") << endl;
}
