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
    int length(ListNode* head) {
        int len = 0;

        ListNode* curr = head;

        while(curr) {
            len++;
            curr = curr->next;
        }

        return len;
    }


    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = length(head);

        if(len == n) return head->next;

        ListNode* curr = head;

        int i = 0;

        ListNode* prev = NULL;

        while(curr && (len-i) != n) {
            prev = curr;
            curr = curr->next;
            i++;
        }

        prev->next = curr->next;

        return head;
    }
};