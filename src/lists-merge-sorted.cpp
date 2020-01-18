/*

	Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

	Example:

	Input: 1->2->4, 1->3->4
	Output: 1->1->2->3->4->4

*/

#include <string>
#include <iostream>

using namespace std;


struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
{
	ListNode* l1p = l1;
	ListNode* l2p = l2;

	ListNode* resp = nullptr;
	ListNode** respp = &resp;

	while (l1p != nullptr && l2p != nullptr)
	{
		ListNode* newNode = nullptr;

		if (l1p->val < l2p->val)
		{
			newNode = new ListNode(l1p->val);
			l1p = l1p->next;
		}
		else
		{
			newNode = new ListNode(l2p->val);
			l2p = l2p->next;			
		}

		*respp = newNode;
		respp = &newNode->next;
	}

	ListNode* lp = (l1p == nullptr ? l2p : l1p);

	while (lp != nullptr)
	{
		ListNode* newNode = nullptr;

		newNode = new ListNode(lp->val);
		lp = lp->next;

		*respp = newNode;
		respp = &newNode->next;
	}

	return resp;
}

/*
	ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		ListNode *temp = l1, *tem;
		if (l1 == NULL)
			swap(l1, l2);
		while (temp != NULL && l2 != NULL) {
			if (temp->val <= l2->val) {
				if (temp->next == NULL) {
					temp->next = l2;
					break;
				}
				temp = temp->next;
			}
			else {
				swap(temp->val, l2->val);
				tem = l2;
				l2 = l2->next;
				tem->next = temp->next;
				temp = temp->next = tem;
			}
		}
		return l1;
	}

*/

int main()
{
	ListNode l1(1);

	l1.next = new ListNode(2);
	l1.next->next = new ListNode(4);

	ListNode l2(1);

	l2.next = new ListNode(3);
	l2.next->next = new ListNode(4);

	ListNode* res = mergeTwoLists(&l1, &l2);

	ListNode* ptr = res;

	while (ptr != nullptr)
	{
		cout << ptr->val << ' ';
		ptr = ptr->next;
	}

	cout << endl;
}
