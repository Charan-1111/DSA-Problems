/* Structure of linked list Node
class Node {
  public:
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};
*/
class Solution {
  public:
    int getCount(Node* head) {
        int len = 0;
        
        Node* curr = head;
        
        while(curr) {
            len++;
            curr = curr->next;
        }
        
        return len;
    }
};