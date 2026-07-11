/*
class Node {
 public:
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    int lengthOfLoop(Node *head) {
        Node* fast = head;
        Node* slow = head;
        bool hasLoop = false;
        
        while(fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            
            if(fast == slow){
                hasLoop = true;
                break;
            }
        }
        
        if(!hasLoop) return 0;
        
        int l = 1;
        fast = fast->next;
        while(fast != slow) {
            l++;
            fast = fast->next;
        }
        
        return l;
    }
};