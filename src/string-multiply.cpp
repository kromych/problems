#include <string>
#include <iostream>
#include <memory>

using namespace std;


static string shift(const string& num1, int n)
{
    if (n == 0)
    {
        return num1;
    }

    if ((num1.size() == 1 && num1.front() == '0'))
    {
        return "0";
    }        
    
    string res(num1);
    
    res.reserve(num1.size() + n);
    
    for (int i = 0; i < n; ++i)
    {
        res.append("0");
    }
    
    return res;
}    

static string add(const string& num1, const string& num2)
{    
    if (num1.size() == 1 && num1.front() == '0')
    {
        return num2;
    }

    if (num2.size() == 1 && num2.front() == '0')
    {
        return num1;
    }

    const char* x;
    const char* y;

    size_t xn;
    size_t yn;
    
    if (num1.size() > num2.size())
    {
        x = num1.c_str();
        y = num2.c_str();
        xn = num1.size();
        yn = num2.size();
    }
    else
    {
        x = num2.c_str();
        y = num1.c_str();            
        xn = num2.size();
        yn = num1.size();
    }

    unique_ptr<char[]> res = make_unique<char[]>(xn + 2);
    int diff = xn - yn;

    res[xn+1] = 0;

    int sum = 0;
    int carry = 0;

    for (int i = xn - 1; i >= diff; --i)
    {
    	sum = (x[i] - '0') + (y[i-diff] - '0') + carry;
    	carry = sum / 10;

    	res[i + 1] = '0' + (sum % 10);
    }

    for (int i = diff-1; i >= 0; --i)
    {
    	sum = (x[i] - '0') + carry;
    	carry = sum / 10;

    	res[i + 1] = '0' + (sum % 10);
    }

    if (carry)
    {
    	res[0] = '1';

    	return &res[0];    	
    }

    return &res[1];
}

static string mul(const string& num1, char digit)
{    
    if (digit == '0')
    {
        return "0";
    }
    
    if (num1.size() == 1 && num1.front() == '0')
    {
        return "0";
    }        
 
    string res("0");

    for (int i = 0; i < digit - '0'; ++i)
    {
    	res = add(res, num1);
    }

    return res;
}

static string multiply(const string& num1, const string& num2) 
{
    if ((num1.size() == 1 && num1.front() == '0') || (num2.size() == 1 && num2.front() == '0'))
    {
        return "0";
    }
    
    const char* x;
    const char* y;

    size_t xn;
    size_t yn;
    
    if (num1.size() > num2.size())
    {
        x = num1.c_str();
        y = num2.c_str();
        xn = num1.size();
        yn = num2.size();
    }
    else
    {
        x = num2.c_str();
        y = num1.c_str();            
        xn = num2.size();
        yn = num1.size();
    }
    
    string res("0");
    
    for (int i = yn - 1; i >=0; --i)
    {
        res = add(res, shift(mul(x, y[i]), yn - 1 - i));
    }

    return res;                
}


int main()
{
	cout << multiply("123", "456") << endl;
}   
