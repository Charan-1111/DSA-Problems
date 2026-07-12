/* a Node of the doubly linked list
class Node {
  public:
    int data;
    Node* next;
    Node* prev;

    Node(int x) {
        data = x;
        next = nullptr;
        prev = nullptr;
    }
};
*/

class Solution {
  public:

    // Function to delete a specified node from the linked list
    Node* deleteAllOccurOfX(Node* head, int x) {
        while(head->data == x) {
            head = head->next;
        }
        
        head->prev = NULL;
        
        Node* curr = head;
        
        while(curr) {
            if(curr->data == x) {
                curr->prev->next = curr->next;
                
                if(curr->next) {
                    curr->next->prev = curr->prev;
                }
                
                curr = curr->prev->next;
            } else {
                curr = curr->next;
            }
        }
        
        return head;
    }
};