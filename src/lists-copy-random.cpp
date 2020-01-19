/*
	A linked list is given such that each node contains an additional random pointer 
	which could point to any node in the list or null.

	Return a deep copy of the list.

	The Linked List is represented in the input/output as a list of n nodes. Each node 
	is represented as a pair of [val, random_index] where:

		val: an integer representing Node.val
		random_index: the index of the node (range from 0 to n-1) where random pointer points to, 
		or null if it does not point to any node.

	Example 1:

	Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
	Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]

	Example 2:

	Input: head = [[1,1],[2,1]]
	Output: [[1,1],[2,1]]

	Example 3:

	Input: head = [[3,null],[3,0],[3,null]]
	Output: [[3,null],[3,0],[3,null]]

	Example 4:

	Input: head = []
	Output: []
	Explanation: Given linked list is empty (null pointer), so return null.

	Constraints:

		-10000 <= Node.val <= 10000
		Node.random is null or pointing to a node in the linked list.
		Number of Nodes will not exceed 1000.
*/

#include <unordered_map>
#include <iostream>

using namespace std;


class Node 
{
public:
	int val;
	Node* next;
	Node* random;
	
	Node(int _val) 
	{
		val = _val;
		next = nullptr;
		random = nullptr;
	}
};

Node* copyRandomList(Node* head) 
{
	Node* 						res = nullptr;
	Node** 						respp = &res;
	unordered_map<Node*, Node*>	pmap;

	{
		Node* cur = head;

		while (cur != nullptr)
		{
			Node* new_node = new Node(cur->val);

			new_node->random = cur->random;

			pmap[cur] = new_node;

			*respp = new_node;
			respp = &new_node->next;

			cur = cur->next;
		}
	}

	{
		Node* cur = res;

		while (cur != nullptr)
		{
			cur->random = pmap[cur->random];
			cur = cur->next;
		}			
	}

	return res;
}

Node* copyRandomList1(Node* head) 
{    
    Node* oldh = head;
    if(!head) return nullptr;
    //creating all nodes
    while(oldh){
        Node* dcopy = new Node(oldh->val);
        dcopy->next = oldh->next;
        oldh->next = dcopy;
        oldh = dcopy->next;
    }
    oldh = head;
    //making all next pointers
    while(oldh){
        if(oldh->random){
           oldh->next->random = oldh->random->next;
        } else{
            oldh->next->random = nullptr;
        }
        oldh = oldh->next->next;
    }
	
    Node* dcopy;
    oldh = head;
    dcopy = oldh->next;
    Node *new_head = dcopy;
	//making all random pointers and undoing changes in original list
    while(oldh){
        oldh->next = dcopy->next;
        if(dcopy->next) {
          dcopy->next = dcopy->next->next; 
        }
        oldh = oldh->next;
        dcopy = dcopy->next;
    }
    return new_head;
}

int main()
{
	
}
