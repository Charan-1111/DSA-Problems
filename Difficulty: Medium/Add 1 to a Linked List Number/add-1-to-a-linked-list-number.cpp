/* Structure of linked list Node
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};
*/
class Solution {
  public:
    Node* reverseLL(Node* head) {
        Node* curr = head;
        Node* prev = NULL;
        
        while(curr) {
            Node* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        
        return prev;
    }
    
    Node* addOne(Node* head) {
        head = reverseLL(head);
        
        int carryOver = 1;
        
        Node* curr = head;
        
        while(curr) {
            int sum = curr->data + carryOver;
            
            curr->data = sum%10;
            carryOver = sum/10;
            
            curr = curr->next;
        }
        
        head = reverseLL(head);
        
        while(carryOver) {
            int rem = carryOver%10;
            carryOver /= 10;
            
            Node* temp = (Node*) malloc(sizeof(Node));
            temp->data = rem;
            temp->next = head;
            head = temp;
        }
        
        return head;
    }
};