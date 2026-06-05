// C++ implementation of De-queue using circular array
#include <iostream>
using namespace std;

class MyDeque {
private:
    int* arr;
    int front, size, capacity;

public:
    // Constructor to initialize the deque
    MyDeque(int c) {
        arr = new int[c];
        capacity = c;
        size = 0;
        front = 0;
    }

    // Delete element from the front
    int deleteFront() {
        // Empty deque
        if (size == 0)
            return -1;
        int res = arr[front];

        // Move front index circularly
        front = (front + 1) % capacity;
        size--;
        return res;
    }

    // Insert element at the front
    void insertFront(int x) {
        // Full deque
        if (size == capacity)
            return;

        // Move front index circularly
        front = (front - 1 + capacity) % capacity;
        arr[front] = x;
        size++;
    }

    // Insert element at the rear
    void insertRear(int x) {
        // Full deque
        if (size == capacity)
            return;

        // Calculate rear index
        int rear = (front + size) % capacity;
        arr[rear] = x;
        size++;
    }

    // Delete element from the rear
    int deleteRear() {
        // Empty deque
        if (size == 0)
            return -1;
        int rear = (front + size - 1) % capacity;
        size--;
        return arr[rear];
    }

    // Get the front element
    int frontEle() {
        return arr[front];
    }

    // Get the rear element
    int rearEle() {
        // Calculate rear index
        int rear = (front + size - 1) % capacity;
        return arr[rear];
    }
};

int main() {
    // Create deque with capacity 4
    MyDeque dq(4);

    // Insert at rear
    dq.insertRear(10);
    cout << dq.frontEle() << " " << dq.rearEle() << endl;

    // Insert at front
    dq.insertFront(20);
    cout << dq.frontEle() << " " << dq.rearEle() << endl;
    dq.insertFront(30);
    cout << dq.frontEle() << " " << dq.rearEle() << endl;

    // Delete from rear
    dq.deleteRear();
    cout << dq.frontEle() << " " << dq.rearEle() << endl;
    dq.insertRear(40);
    cout << dq.frontEle() << " " << dq.rearEle() << endl;
    dq.deleteRear();
    cout << dq.frontEle() << " " << dq.rearEle() << endl;

    return 0;
}