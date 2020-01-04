#include <string>
#include <iostream>
#include <memory>

using namespace std;

string addBinary(const string& a, const string& b) 
{                
    size_t na = a.size();
    size_t nb = b.size();
 
    const char* sa;
    const char* sb;
    
    if (na > nb)
    {
        sa = &a[0];
        sb = &b[0];            
    }
    else
    {
        sa = &b[0];
        sb = &a[0];
        
        swap(na, nb);
    }
    
    int diff = na-nb;
    
    unique_ptr<char[]> buffer = make_unique<char[]>(na+2);

    buffer[na+1] = 0;
    
    char bit_carry = 0;
    char bit_sum = 0;
            
    for (int i = na-1; i >= diff; --i)
    {
        char bit_a = sa[i] == '1';
        char bit_b = sb[i-diff] == '1';
        
        bit_sum   = bit_a ^ bit_b ^ bit_carry;
        bit_carry = (bit_a & bit_b) | (bit_a & bit_carry) | (bit_b & bit_carry); // minimized from ab!c | (a|b)c

        cout << i << endl;

        buffer[i+1] = bit_sum + '0';
    }

    for (int i = diff - 1; i >= 0; --i)
    {
        char bit_a = sa[i] == '1';
        
        bit_sum   = bit_a ^ bit_carry;
        bit_carry = bit_a & bit_carry;

        buffer[i+1] = bit_sum + '0';    	
    }

    if (bit_carry)
    {
        buffer[0] = '1';
        
        return string(&buffer[0]);
    }
    
    return string(&buffer[1]);
}

int main()
{
	cout << addBinary("1010", "1011") << endl;
}
