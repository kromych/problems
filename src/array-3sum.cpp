#pragma GCC target ("arch=icelake-server") 
#pragma GCC target ("tune=icelake-server")

#pragma GCC optimize ("O3")
#pragma GCC optimize ("no-exceptions")
#pragma GCC optimize ("no-rtti")
#pragma GCC optimize ("no-threadsafe-statics")
#pragma GCC optimize ("no-implement-inlines")   
    
static const auto fast=[]()
{
    ios_base::sync_with_stdio(false);
    
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    return nullptr;
}();

#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <iostream>

using namespace std;

ostream& operator<<(ostream& ost, const vector<int>& v)
{
    ost << '[';
    for (size_t i = 0; i < v.size() - 1; ++i)
    {
        ost << v[i] << ',';
    }

    if (!v.empty()) ost << v.back();

    cout << ']';

    return ost;
}

vector<vector<int>> threeSum(vector<int>& nums) 
{
    vector<vector<int>> res;

    sort(nums.begin(), nums.end());

    if (nums.size() < 3)
    {
        return {};
    }

    if (nums.front() == 0 && nums.back() == 0)
    {
        vector<int> v{0, 0, 0};

        res.emplace_back(v);
        
        return res;
    }
            
    if (nums.front() >= 0 || nums.back() <= 0)
    {
        return {};
    }            

    int i = 0;
    size_t n = nums.size();
    int max = nums.back();

    while (i < n - 1)
    {
        int a = nums[i];

        if (-a/2 <= max)
        {
            int start = i + 1;
            int end = n - 1;

            while (start < end)
            {
                int b = nums[start];
                int c = nums[end];

                if (a + b + c > 0)
                {
                    --end;
                }
                else if (a + b + c < 0)
                {
                    ++start;
                }
                else
                {
                    vector<int> v{a, b, c};

                    res.emplace_back(v);   

                    while (start < end && nums[start] == b)
                    {
                        ++start;
                    }

                    while (start < end && nums[end] == c)
                    {
                        --end;
                    }
                }            
            }
        }

        do
        {
            ++i;
        }
        while (i < n - 1 && nums[i-1] == nums[i]);
    }

    return res;
}

int main()
{
    vector<vector<int>> v{
        {-1, 0, 1, 2, -1, -4, -4},
        {1,-1,-1,0},
        {-2,0,1,1,2},
        {-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6}
    };

    for (auto& i : v)
    {
        cout << i << endl;

        for (const auto& s : threeSum(i))
        {
            cout << '\t' << i << s << endl;            
        }
    }
}
