#include <vector>
#include <iostream>
#include <set>

using namespace std;

int totalFruitV0(const vector<int>& tree) 
{
    if (tree.size() < 2)
    {
        return tree.size();
    }

    int      max_harvest = 0;
    int      harvest = 0;
    int      previous_harvest = 0;

    for (size_t start = 0; start < tree.size() - 1; ++start)
    {
        if (start != 0 && tree[start] == tree[start-1])
        {
            harvest = previous_harvest--;   
        }
        else
        {
            set<int>    baskets;
            size_t      k = start;

            harvest = 0;

            while (k < tree.size())
            {
                baskets.insert(tree[k]);

                if (baskets.size() <= 2)
                {
                    ++harvest;
                }
                else
                {
                    previous_harvest = harvest;

                    break;
                }

                ++k;
            }
        }

        max_harvest = max(harvest, max_harvest);
    }        

    return max_harvest;
}

int totalFruitV1(const vector<int>& tree)
{
    int max_harvest = 0;
    int harvest = 0;
    
    int baskets[2];

    for (int i = tree.size() - 1; i >= 0; --i)
    {
        if (i == tree.size() - 1)
        {
            baskets[0] = baskets[1] = tree.back();
            harvest = 1;
        }
        else if (i < tree.size() - 2 && tree[i] == tree[i+1] && tree[i] == tree[i+2])
        {
            baskets[0] = baskets[1] = tree[i];
            ++harvest;  
        }        
        else if (i < tree.size() - 1 && tree[i] == tree[i+1])
        {
            swap(baskets[1], baskets[0]);
            baskets[0] = tree[i];

            ++harvest;  
        }
        else if (i < tree.size() - 2 && tree[i] == tree[i+2])
        {
            swap(baskets[1], baskets[0]);
            baskets[0] = tree[i];

            ++harvest;  
        }
        else
        {            
            if (baskets[0] != baskets[1])
            {                                
                harvest = 2;
            }
            else
            {
                ++harvest;                
            }

            swap(baskets[1], baskets[0]);
            baskets[0] = tree[i];
        }

        max_harvest = max(harvest, max_harvest);
    }
    
    return max_harvest;
}


int main()
{
    cout << totalFruitV1({0,1,2,2}) << endl; // 3
    cout << totalFruitV1({1,2,1}) << endl; // 3
    cout << totalFruitV1({0,1,1,2}) << endl; // 3
    cout << totalFruitV1({1,2,3,2,2}) << endl; // 4
    cout << totalFruitV1({3,3,3,1,2,1,1,2,3,3,4}) << endl; // 5
}
