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

    while (fastp != nullptr)
    {
    	slowp = slowp->next;

    	if (fastp != nullptr) fastp = fastp->next;
    	if (fastp != nullptr) fastp = fastp->next;
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

		l1p = l1p->next;
		l2p = l2p->next;
	}
}

void reorderList(ListNode* head) 
{
    // Find the middle item 

	ListNode* middle = middleNode(head);

    // Cut the tail off

    ListNode* tail = middle->next;
    middle->next = nullptr;

    // Reverse the tail

    reverseList(&tail);

    // Merge the initial list (just cut in half)
    // and the tail

    mergeLists(head, tail);
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

	reverseList(&l1);
	reverseList(&l2);

	reorderList(l1);
	reorderList(l2);

	cout << l1 << endl;
	cout << l2 << endl;

	delete l1;
	delete l2;
}
