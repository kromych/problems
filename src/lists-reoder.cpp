/*
	Given a singly linked list L: L0→L1→…→Ln-1→Ln,
	reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

	You may not modify the values in the list's nodes, only nodes itself may be changed.

	Example 1:

	Given 1->2->3->4, reorder it to 1->4->2->3.

	Example 2:

	Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
*/

#include <iostream>
#include <string>
#include <memory>
#include <deque>

using namespace std;


struct ListNode 
{
	int val;
	ListNode *next;

	ListNode(int x) : val(x), next(nullptr) {}
	~ListNode() { delete next; }
};

ostream& operator << (ostream& ost, ListNode* node)
{
	ListNode* ptr = node;

	while (ptr != nullptr)
	{
		ost << ptr->val << ' ';
		ptr = ptr->next;
	}

	return ost;
}


ListNode* middleNode(ListNode* head)
{
	ListNode* slowp = head;
	ListNode* fastp = head;

	while (fastp != nullptr && fastp->next != nullptr)
	{
		fastp = fastp->next->next;

		if (fastp != nullptr)
		{
			slowp = slowp->next;
		}
	}

	return slowp;
}

void reverseList(ListNode** head) 
{
	ListNode* current = *head; 

	ListNode* prev = nullptr;
	ListNode* next = nullptr; 

	while (current != nullptr) 
	{ 
		next = current->next; 

		current->next = prev; prev = current; 

		current = next; 
	} 

	*head = prev;
}

void mergeLists(ListNode* l1, ListNode* l2)
{
	ListNode* l1p = l1;
	ListNode* l2p = l2;

	while (l1p != nullptr && l2p != nullptr)
	{
		ListNode* next = l1p->next;
		ListNode* node = new ListNode(l2p->val);

		l1p->next = node;
		node->next = next;

		l1p = next;
		l2p = l2p->next;
	}
}

void reorderList(ListNode* head) 
{
	if (head == nullptr)
	{
		return;
	}

	// Find the middle item 

	ListNode* middle = middleNode(head);

	// Cut the tail off

	ListNode* tail = middle->next;
	middle->next = nullptr;

	// Reverse the tail

	reverseList(&tail);

	// Merge

	mergeLists(head, tail);
}

void reorderList1(ListNode* head) 
{
	deque<ListNode*> dq;
	ListNode* trav=head;
	bool alternate=false;
	
	if (!head)
		return;
	
	while(trav) 
	{
		dq.push_back(trav);
		trav=trav->next;
	} 
	
	trav=dq.front();
	dq.pop_front();
	
	while(!dq.empty()) 
	{
		if (!alternate) 
		{
			trav->next=dq.back();
			trav=dq.back();
			dq.pop_back();
		} 
		else 
		{
			trav->next=dq.front();
			trav=dq.front();
			dq.pop_front();
		}

		alternate=!alternate;
	}

	trav->next=NULL;
}

int main()
{
	ListNode* l1 = new ListNode(1);

	l1->next = new ListNode(2);
	l1->next->next = new ListNode(3);
	l1->next->next->next = new ListNode(4);

	ListNode* l2 = new ListNode(1);

	l2->next = new ListNode(2);
	l2->next->next = new ListNode(3);
	l2->next->next->next = new ListNode(4);
	l2->next->next->next->next = new ListNode(5);

	reorderList(l1);

	cout << l1 << endl;

	reorderList(l2);

	cout << l2 << endl;

	delete l1;
	delete l2;
}
