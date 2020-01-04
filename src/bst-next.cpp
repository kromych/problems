/*
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

 

Follow up:

    You may only use constant extra space.
    Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.

 

Example 1:

Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.

 

Constraints:

    The number of nodes in the given tree is less than 4096.
    -1000 <= node.val <= 1000

================================================
*/

#include <vector>
#include <deque>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

Node* connect(Node* root) 
{
	constexpr int MAX_ITEMS = 12;

    Node* bfs[MAX_ITEMS];
    int   bfs_idx = 0;

    Node* lst[MAX_ITEMS];
    int   lst_idx = 0;

	memset(bfs, 0, sizeof(lst));
	memset(lst, 0, sizeof(lst));

    
    bfs[bfs_idx++] = root;

    while (bfs_idx != 0)
    {

		for (int i = 0; i < nodes.size(); ++i)
		{
			Node* node = nodes[i];

			if (node != nullptr)
			{
				node->next = nodes[i+1];

				bfs.push_back(node->left);
				bfs.push_back(node->right);				
			}
		}

		memset(lst, 0, sizeof(lst));
    }
    
/*
    static Node* connect(Node* root) 
    {
        constexpr int MAX_ITEMS = 8192;

        Node* bfs[MAX_ITEMS];
        int   bfs_idx = 0;

        Node* lst[MAX_ITEMS];
        int   lst_idx = 0;

        bfs[bfs_idx++] = root;

        while (bfs_idx != 0)
        {
            memcpy(lst, bfs, sizeof(bfs[0])*bfs_idx);

            lst_idx = bfs_idx;
            bfs_idx = 0;

    	    lst[lst_idx++] = nullptr;
            
            for (int i = 0; i < lst_idx - 1; ++i)
            {
                Node* node = lst[i];

                if (node != nullptr)
                {
                    node->next = lst[i+1];

                    bfs[bfs_idx++] = node->left;
                    bfs[bfs_idx++] = node->right;
                }
            }
        }

        return root;
    }
*/

/*
        deque<Node*> bfs;
        vector<Node*> nodes;

        bfs.push_back(root);

        while (!bfs.empty())
        {
            while (!bfs.empty())
            {
                nodes.push_back(bfs.front());
                bfs.pop_front();
            }

            nodes.push_back(nullptr);

            for (int i = 0; i < nodes.size(); ++i)
            {
                Node* node = nodes[i];

                if (node != nullptr)
                {
                    node->next = nodes[i+1];

                    bfs.push_back(node->left);
                    bfs.push_back(node->right);				
                }
            }

            nodes.clear();
        }

        return root;  
*/
    return root;
}


