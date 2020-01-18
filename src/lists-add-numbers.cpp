/*

	You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

	You may assume the two numbers do not contain any leading zero, except the number 0 itself.

	Example:

	Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	Output: 7 -> 0 -> 8
	Explanation: 342 + 465 = 807.

*/

#include <iostream>

using namespace std;

struct ListNode 
{
    int val;

    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) 
    {
    }

    ~ListNode()
    { 
    	delete next; 
   	}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
	ListNode* resp = nullptr;
    ListNode** respp = &resp;
    
	int carry = 0;

	ListNode* l1p = l1;
	ListNode* l2p = l2;

	while (l1p != nullptr && l2p != nullptr)
	{
		int sum = l1p->val + l2p->val + carry;

		ListNode* digit = new ListNode(sum % 10);
        
        *respp = digit;
        respp = &digit->next;

		l1p = l1p->next;
		l2p = l2p->next;

		carry = sum / 10;        
	}		

	ListNode* lp = ((l1p == nullptr) ? l2p : l1p);

	while (lp != nullptr)
	{
		int sum = lp->val + carry;

		ListNode* digit = new ListNode(sum % 10);
        
        *respp = digit;
        respp = &digit->next;

		lp = lp->next;

		carry = sum / 10;
    }

	if (carry)
	{
		*respp = new ListNode(carry);			
	}

	return resp;
}

/*
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        ListNode* re = l1;
        ListNode* pre;
        while(l1 != NULL && l2 != NULL){
            
            l1->val += l2->val;
            
            cout << l1-> val;
            
            pre = l1;
            
            l1 = l1->next;  
            l2 = l2->next;
        }
        
        if(pre->next == NULL && l2 != NULL){
            pre->next = l2;
        }
        
        ListNode* fin = re;
        
        int car = 0;
        ListNode* pre2;
        while(re != NULL){
            re->val = re->val + car;
            
            car = 0;
            
            if(re->val > 9){
                car = re->val / 10;
                re->val = re->val % 10;
            }
            
            pre2 = re;
            re = re->next;
        }
        
        if(car != 0){
            ListNode* listcar = new ListNode(car);
            pre2->next = listcar;
        }
        
        
        return fin;
    }
*/

int main()
{
	ListNode l1(2);

	l1.next = new ListNode(4);
	l1.next->next = new ListNode(3);

	ListNode l2(5);

	l2.next = new ListNode(6);
	l2.next->next = new ListNode(4);

	ListNode* sum = addTwoNumbers(&l1, &l2);

	ListNode* ptr = sum;

	while (ptr != nullptr)
	{
		cout << ptr->val << ' ';
		ptr = ptr->next;
	}

	cout << endl;
}
