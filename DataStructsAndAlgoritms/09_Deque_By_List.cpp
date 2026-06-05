#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev, * next;
    Node(int data) {
        this->data = data;
        prev = nullptr;
        next = nullptr;
    }
};

class Deque {
    Node* front, * rear;
    int size;
public:
    Deque() { front = nullptr; rear = nullptr; size = 0; }

    bool isEmpty() { return front == nullptr; }
    int getSize() { return size; }

    void insertFront(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) front = rear = newNode;
        else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        size++;
    }

    void insertRear(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) front = rear = newNode;
        else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    void deleteFront() {
        if (isEmpty()) cout << "UnderFlow\n";
        else {
            Node* temp = front;
            front = front->next;
            if (front) front->prev = nullptr;
            else rear = nullptr;
            delete temp;
            size--;
        }
    }

    void deleteRear() {
        if (isEmpty()) cout << "UnderFlow\n";
        else {
            Node* temp = rear;
            rear = rear->prev;
            if (rear) rear->next = nullptr;
            else front = nullptr;
            delete temp;
            size--;
        }
    }

    int getFront() { return isEmpty() ? -1 : front->data; }
    int getRear() { return isEmpty() ? -1 : rear->data; }

    void clear() {
        while (!isEmpty()) deleteFront();
    }
};

int main() {
    Deque dq;
    dq.insertRear(5);
    dq.insertRear(10);
    cout << "Rear: " << dq.getRear() << endl;
    dq.deleteRear();
    cout << "New Rear: " << dq.getRear() << endl;

    dq.insertFront(15);
    cout << "Front: " << dq.getFront() << endl;
    cout << "Size: " << dq.getSize() << endl;

    dq.deleteFront();
    cout << "New Front: " << dq.getFront() << endl;

    return 0;
}