
#include <iostream>

using namespace std;

typedef struct _stack
{
    void **array;
    unsigned int capacity, top;

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
      if (data == NULL)
      {
        return;
      }
      if ( isFull() != true )
      {
        array[top++] = data;
      }
      else
      {
        cout << "Stack is full!\n";
      }
    }

    void *pop()
    {
      void *data = NULL;
      if ( isEmpty() != true )
      {
        data = array[--top];
      }
      else
      {
        cout << "Stack is empty!\n";
      }

      return data;
    }
} Stack;

typedef struct _queue
{
  void **array;
  unsigned int capacity, front, rear, size;

  _queue(int _capacity)
  {
    capacity = _capacity;
    array = new void*[capacity];
    front = size = 0;
    rear = capacity - 1;
  }
  
  ~_queue()
  {
    delete[] array;
  }

  bool isEmpty() { return size == 0; }

  bool isFull() { return size == capacity; }

  void enqueue(void *data)
  {
    if (data == NULL)
    {
      return;
    }

    if ( isFull() == true )
    {
      cout << "Queue is full!\n";
      return;
    }

    rear = ++rear % capacity;
    array[rear] = data;
    ++size;
  }

  void *dequeue()
  {
    void *data = NULL;

    if ( isEmpty() == true ) 
    {
      cout << "Queue is empty!\n";
      return data;
    }

    data = array[front];
    front = ++front % capacity;
    --size;

    return data;
  }

} Queue;

int main()

{
    int *d1 = new int;
    *d1 = 10;
    int *d2 = new int;
    *d2 = 20;
    int *d3 = new int;
    *d3 = 30;
    int *d4 = new int;
    *d4 = 40;
    int *d5 = new int;
    *d5 = 50;
    int *d6 = new int;
    *d6 = 60;

    int *data;

    Stack s(3);

    s.push(d1);
    s.push(d2);
    s.push(d3);

    data = (int*)s.pop();
    if (data) cout << *data << "\n";
    data = (int*)s.pop();
    if (data) cout << *data << "\n";
    data = (int*)s.pop();
    if (data) cout << *data << "\n";
    data = (int*)s.pop();

    cout << "**************\n";

    Queue q(3);

    q.enqueue(d1);
    q.enqueue(d2);
    q.enqueue(d3);
    q.enqueue(d4);
    
    data = (int*)q.dequeue();
    if (data) cout << *data << "\n";
    data = (int*)q.dequeue();
    if (data) cout << *data << "\n";
    data = (int*)q.dequeue();
    if (data) cout << *data << "\n";
    data = (int*)q.dequeue();

    q.enqueue(d4);
    q.enqueue(d5);
    q.enqueue(d6);

    data = (int*)q.dequeue();
    if (data) cout << *data << "\n";

    q.enqueue(d1);
    q.enqueue(d2);

    data = (int*)q.dequeue();
    if (data) cout << *data << "\n";
    data = (int*)q.dequeue();
    if (data) cout << *data << "\n";
    data = (int*)q.dequeue();
    if (data) cout << *data << "\n";
    data = (int*)q.dequeue();

    cout << "**************\n";

    delete d1, d2, d3, d4, d5, d6;

	return 0;
}
