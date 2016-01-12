
#include <iostream>

using namespace std;

typedef struct _stack
{
    void **array;
    int capacity, top;

    _stack(int size)
    {
        capacity = size;
        array = new void*[capacity];
        top = 0;
    }

    ~_stack()
    {
        delete[] array;
    }

    bool isEmpty() { return top == 0; }

    bool isFull() { return top == capacity; }

    void push(void *data)
    {
        if ( !isFull() )
            array[top++] = data;
        else
            cout << "Stack is full!\n";
    }

    void *pop()
    {
        void *data = NULL;
        if ( !isEmpty() )
            data = array[--top];
        else
            cout << "Stack is empty!\n";

        return data;
    }
} Stack;

int main()

{
    int *d1 = new int;
    *d1 = 10;
    int *d2 = new int;
    *d2 = 20;
    int *d3 = new int;
    *d3 = 30;

    Stack s(3);

    s.push(d1);
    s.push(d2);
    s.push(d3);

    int *data;

    data = (int*)s.pop();
    if (data) cout << *data << "\n";
    data = (int*)s.pop();
    if (data) cout << *data << "\n";
    data = (int*)s.pop();
    if (data) cout << *data << "\n";
    data = (int*)s.pop();

    delete d1, d2, d3;

	return 0;
}
