/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseLL(ListNode* head) {
        ListNode* curr = head;
        ListNode* prev = NULL;

        while(curr) {
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        return prev;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carryOver = 0;

        ListNode* curr1 = l1;
        ListNode* curr2 = l2;

        ListNode* head = NULL;

        while(curr1 && curr2) {
            int sum = curr1->val + curr2->val + carryOver;

            int rem = sum%10;
            carryOver = sum/10;

            ListNode* temp = new ListNode();
            temp->val = rem;
            temp->next = head;
            head = temp;

            curr1 = curr1->next;
            curr2 = curr2->next;
        }

        while(curr1) {
            int sum = curr1->val + carryOver;

            int rem = sum%10;
            carryOver = sum/10;

            ListNode* temp = new ListNode();
            temp->val = rem;
            temp->next = head;
            head = temp;

            curr1 = curr1->next;
        }

        while(curr2) {
            int sum = curr2->val + carryOver;

            int rem = sum%10;
            carryOver = sum/10;

            ListNode* temp = new ListNode();
            temp->val = rem;
            temp->next = head;
            head = temp;

            curr2 = curr2->next;
        }


        while(carryOver) {
            int rem = carryOver%10;
            carryOver /= 10;

            ListNode* temp = new ListNode();
            temp->val = rem;
            temp->next = head;
            head = temp;
        }


        head = reverseLL(head);

        return head;
    }
};