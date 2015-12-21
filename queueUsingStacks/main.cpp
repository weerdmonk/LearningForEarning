
#include <iostream>
#include <climits>

using namespace std;

class Stack
{
	int capacity;
	int *basePtr;
	int *stackPtr;
public:
	Stack(int size) { capacity = size; stackPtr = basePtr = new int[size]; }
	~Stack() { delete[] basePtr; }

	bool isEmpty() { return stackPtr == basePtr; }
	bool isFull() { return (stackPtr - basePtr) == capacity; }

	void push(int data)
	{
		if (!isFull()) *stackPtr++ = data;
		else cout << "Cannot push \"" << data << "\". Stack is full!\n";
	}

	int pop()
	{
		if (!isEmpty()) return *--stackPtr;
		else cout << "Cannot pop. Stack is empty!\n";
		return INT_MAX;
	}
};

class Queue
{
	int capacity;
	Stack s1, s2; // s1 is auxillary, s2 is primary

public:
	Queue(int size) : s1(size), s2(size), capacity(size) {}

	void enque(int data)
	{
		if (s1.isFull())
		{
			cout << "Cannot enqueue \"" << data << "\". Queue is full!\n";
			return;
		}
		else
			s2.push(data);
	}

	int deque()
	{
		if (!s2.isEmpty())
		{
			if (s1.isEmpty())
			{
				while(!s2.isEmpty())
				{
					s1.push(s2.pop);
				}
			}
			return s2.pop();

		}
		else cout << "Cannot dequeue. Queue is empty!\n";
		return INT_MAX;
	}
};

int main()
{
//	Stack s(5);
//	s.push(1);
//	s.push(2);
//	s.push(3);
//	s.push(4);
//	s.push(5);
//	s.push(6);
//	cout << s.pop() << endl;
//	cout << s.pop() << endl;
//	cout << s.pop() << endl;
//	cout << s.pop() << endl;
//	cout << s.pop() << endl;
//	cout << s.pop() << endl;

	Queue q(5);
	q.enque(1);
	q.enque(2);
	q.enque(3);
	q.enque(4);
	q.enque(5);
	cout << q.deque() << endl;
	cout << q.deque() << endl;
	cout << q.deque() << endl;
	cout << q.deque() << endl;
	cout << q.deque() << endl;
	cout << q.deque() << endl;

	return 0;
}
