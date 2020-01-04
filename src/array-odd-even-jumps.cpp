#include <iostream>
#include <vector>
#include <map>
#include <stack>

#include <algorithm>
#include <utility>

using namespace std;

constexpr size_t INFNTY = 88888888;

int oddEvenJumps(const vector<int>& A) 
{
    size_t goodStartNum = 0;

    vector<size_t> oddJumps(A.size(), 0);
    vector<size_t> evenJumps(A.size(), 0);

    for (size_t i = 0; i < A.size(); ++i)
    {
        oddJumps[i] = i;
        evenJumps[i] = i;
    }

    // For the odd jumps, we need indices in the order 
    // which makes the items themselves increase

    std::stable_sort(
        oddJumps.begin(), 
        oddJumps.end(), 
        [&A = std::as_const(A)](int i, int j)
        { 
            return A[i] < A[j];
        }
    );

    vector<size_t> oddJumpsNext(oddJumps.size(), INFNTY);
    
    {
        stack<size_t> stk;

        for (size_t i = 0; i < oddJumps.size(); ++i)
        {
            while (!stk.empty() && oddJumps[i] > stk.top())
            {
                oddJumpsNext[stk.top()] = oddJumps[i];
                stk.pop();            
            }

            stk.push(oddJumps[i]);
        }        
    }

    // For the even jumps, we need indices in the order 
    // which makes the items themselves decrease

    std::stable_sort(
        evenJumps.begin(), 
        evenJumps.end(), 
        [&A = std::as_const(A)](int i, int j) 
        { 
            return A[i] > A[j];
        }
    );

    vector<size_t> evenJumpsNext(evenJumps.size(), INFNTY);

    {
        stack<size_t> stk;

        for (size_t i = 0; i < evenJumps.size(); ++i)
        {
            while (!stk.empty() && evenJumps[i] > stk.top())
            {
                evenJumpsNext[stk.top()] = evenJumps[i];
                stk.pop();            
            }

            stk.push(evenJumps[i]);
        }        
    }

    vector<bool> odd(oddJumps.size(), false);
    vector<bool> even(evenJumps.size(), false);

    odd.back() = true;
    even.back() = true;

    for (int i = A.size() - 2; i >= 0; --i)
    {
        if (oddJumpsNext[i] != INFNTY)
        {
            odd[i] = even[oddJumpsNext[i]];
        }

        if (evenJumpsNext[i] != INFNTY)
        {
            even[i] = odd[evenJumpsNext[i]];
        }
    }

    goodStartNum = std::count_if(odd.begin(), odd.end(), [](bool e) { return e; });

    return goodStartNum;
}

struct Node 
{
    Node* left = NULL, * right = NULL;
    bool oddJump, evenJump;
    int val;
    Node(int _val) : val(_val) {}
    
    ~Node() 
    {
        if (left) delete left;
        if (right) delete right;
    }    
};

int findUsingBST(std::vector<int> const & A)
{
    int n = A.size() - 1, res = 1, num;
    Node root(A[n]), * t;
    root.oddJump = true, root.evenJump = true;
    bool oddJump, evenJump;

    while (n--) 
    {
        t = &root, oddJump = evenJump = false, num = A[n];

        while (true) 
        {
            if (num < t->val) 
            {
                if (!t->left) 
                {
                    t->left = new Node(num);
                    t->left->oddJump = t->evenJump;
                    t->left->evenJump = oddJump;
                    if (t->left->oddJump) res++;
                    break;
                }
                evenJump = t->evenJump;
                t = t->left;
            }
            else if (num > t->val) 
            {
                if (!t->right)
                {
                    t->right = new Node(num);
                    t->right->oddJump = evenJump;
                    t->right->evenJump = t->oddJump;
                    if (t->right->oddJump) res++;
                    break;
                }
                oddJump = t->oddJump;
                t = t->right;
            }
            else 
            {
                std::swap(t->oddJump, t->evenJump);
                if (t->oddJump) res++;
                break;
            }
        }
    }
    return res;
}

static auto fast = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    return nullptr;
}();

int main()
{
    cout << oddEvenJumps({10,13,12,14,15}) << "\n"; // 2        
    cout << oddEvenJumps({2,3,1,1,4}) << "\n";      // 3
    cout << oddEvenJumps({15,1,3,4,2}) << "\n";     // 3
    cout << oddEvenJumps({5,1,3,4,2}) << "\n";      // 3
    cout << oddEvenJumps({2,96,18,12,21,80,93,2,42,10,25,22,64,35,18,50,3,10,98,19}) << "\n";      // 15

    cout << findUsingBST({10,13,12,14,15}) << "\n"; // 2        
    cout << findUsingBST({2,3,1,1,4}) << "\n";      // 3
    cout << findUsingBST({15,1,3,4,2}) << "\n";     // 3
    cout << findUsingBST({5,1,3,4,2}) << "\n";      // 3
    cout << findUsingBST({2,96,18,12,21,80,93,2,42,10,25,22,64,35,18,50,3,10,98,19}) << "\n";      // 15
}
