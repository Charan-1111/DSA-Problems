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
class myStack {

  public:
    myStack() {
        // Initialize your data members
    }
    
    Node* head = NULL;
    int length = 0;

    bool isEmpty() {
        // check if the stack is empty
        return head == NULL;
    }

    void push(int x) {
        // Adds an element x at the top of the stack
        Node* temp = (Node*) malloc(sizeof(Node));
        temp->data = x;
        temp->next = head;
        
        head = temp;
        length++;
    }

    void pop() {
        // Removes the top element of the stack
        if(isEmpty()) return;
        
        head = head->next;
        length--;
    }

    int peek() {
        // Returns the top element of the stack
        // If stack is empty, return -1
        if(isEmpty()) return -1;
        
        return head->data;
    }

    int size() {
        // Returns the current size of the stack.
        return length;
    }
};