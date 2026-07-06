class Node {
  public:
    int data;
    Node* next;

    Node(int new_data) {
        data = new_data;
        next = nullptr;
    }
};

class myQueue {

  public:
    myQueue() {
        // Initialize your data members
    }
    
    Node* head = NULL;
    int length = 0;

    bool isEmpty() {
        // check if the queue is empty
        return head == NULL;
    }

    void enqueue(int x) {
        // Adds an element x at the rear of the queue
        Node* temp = (Node*) malloc(sizeof(Node));
        temp->data = x;
        temp->next = NULL;
        
        if(!head) {
            head = temp;
        } else {
            Node* curr = head;
            while(curr->next) {
                curr = curr->next;
            }
            curr->next = temp;
        }
        length++;
    }

    void dequeue() {
        // Removes the front element of the queue
        if(isEmpty()) return;
        
        head = head->next;
        length--;
    }

    int getFront() {
        // Returns the front element of the queue
        // If queue is empty, return -1
        
        if(isEmpty()) return -1;
        
        return head->data;
    }

    int size() {
        // Returns the current size of the queue.
        return length;
    }
};
