#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

ostream& operator<<(ostream& ost, const vector<int>& v)
{
    ost << '[';
    for (int i = 0; i < (int)v.size() - 1; ++i)
    {
        ost << v[i] << ',';
    }

    if (!v.empty()) ost << v.back();

    cout << ']';

    return ost;
}

 int removeDuplicates2(vector<int>& nums) 
 {
            
    if(nums.size() == 0)
        return 0;
    
    
    int prevIndx = 0;
    int prevVal = nums.at(0);
    int newLen = 1;

    for (int i=1; i<nums.size(); i++)
    {
        while(i < (nums.size()-1) && nums.at(i) == prevVal)
        {
            i++;
        }    

        if (nums.at(i) != prevVal) 
        {
            nums.at(prevIndx+1) = nums.at(i);
            prevIndx++;
            prevVal = nums.at(i);
            newLen++;
        }
    }

    return newLen;
}

int removeDuplicates3(vector<int>& nums) 
{
    if (nums.empty())
        return 0;
    
    int duplicates = 0;
    for (int i = 1; i < nums.size(); i++) 
    {
        if (nums[i] == nums[i - 1])
            duplicates++;
        else
            nums[i - duplicates] = nums[i];
    }

    return nums.size() - duplicates;
}

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) 
        return 0;

    int i = 0;
    for (int j = 1; j < nums.size(); j++) 
    {
        if (nums[j] != nums[i]) 
        {
            i++;
            nums[i] = nums[j];
        }
    }

    return i + 1;
}

int removeDuplicates1(vector<int>& nums) 
{
    int n = nums.size();

    if (n <=1)
    {
        return n;
    }

    if (nums.front() != nums.back())
    {
        int i = 0;
        
        while (i < n - 1)
        {
            int j = i;
            
            while (j < n - 1 && nums[j] == nums[j+1])
            {                
                ++j;
            }
            
            if (i != j)
            {
                if (j < n - 1)
                {
                    memmove(&nums[i+1], &nums[j+1], sizeof(int)*(n - j - 1));
                }
            }

            n -= (j-i);

            ++i;
        }           

        nums.resize(n);
    }
    else
    {
        nums.resize(1);
    }

    return nums.size();
}


int main()
{
    vector<vector<int>> v {
        {1,2},
        {1,2,2,2,2},
        {1,1,2,3},
        {1,1,2},
        {0,0,1,1,1,2,2,3,3,4},
        {},
        {1},
        {1,1},
        {1,1,1}
    };

    for (auto& i : v)
    {
        cout << i;// << '\n';
        removeDuplicates(i);
        cout << i << endl;    
    }
}
