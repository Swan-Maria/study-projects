#include <iostream>
#include <vector>
using namespace std;

class Queue {
    vector<int> q;

public:
    bool isEmpty() { return q.empty(); }

    void enqueue(int x) {
        q.push_back(x);
    }

    void dequeue() {
        if (!isEmpty()) q.erase(q.begin());
    }

    int getFront() {
        return isEmpty() ? -1 : q.front();
    }

    void display() {
        for (int x : q) cout << x << " ";
        cout << "\n";
    }
};

int main() {
    Queue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    cout << q.getFront() << endl;
    q.dequeue();
    q.enqueue(4);
    q.display();
}