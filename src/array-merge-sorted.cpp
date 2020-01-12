#include <vector>
#include <iostream>

using namespace std;

ostream& operator<< (ostream& ost, const vector<int>& v)
{
	ost << '[';

	if (!v.empty())
	{
		const int n = v.size();

		for (int i = 0; i < n - 1; ++i)
		{
			cout << v[i] << ',';
		}

		cout << v.back();
	}

	ost << ']';

	return ost;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
{
	vector<int> t(m, 0);

	copy(nums1.begin(), nums1.begin() + m, t.begin());

    int i1 = 0;
    int i2 = 0;
    int it = 0;

    while (it < m && i2 < n)
    {
    	if (t[it] < nums2[i2])
    	{
    		nums1[i1] = t[it];
    		++it;
    	}
    	else
    	{
    		nums1[i1] = nums2[i2];
    		++i2;
    	}

    	++i1;
    }

    while (i1 < m + n)
    {
    	if (it < m)
    	{
    		nums1[i1] = t[it];
    		++it;
    	}
    	else if (i2 < n)
    	{
    		nums1[i1] = nums2[i2];
    		++i2;
    	}

    	++i1;    	
    }
}

int main()
{
	vector<int> nums1{1,2,3,0,0,0};
	vector<int> nums2{2,5,6};

	cout << nums1 << endl;
	cout << nums2 << endl;

	merge(nums1, 3, nums2, 3);

	cout << nums1 << endl;
}