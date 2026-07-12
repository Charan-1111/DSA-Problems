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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return head;
        
        vector<int> v;
        int l = 0;

        ListNode* curr = head;

        while(curr) {
            v.push_back(curr->val);
            l++;
            curr = curr->next;
        }

        k = k % l;

        int idx = l-k;

        // cout << "length : " << l << endl;

        reverse(v.begin(), v.begin()+idx);
        reverse(v.begin()+idx, v.end());

        ListNode* newHead = NULL;

        for(int i=0; i<l; i++) {
            ListNode* temp = new ListNode();
            temp->val = v[i];
            temp->next = newHead;
            newHead = temp;
        }

        return newHead;
    }
};