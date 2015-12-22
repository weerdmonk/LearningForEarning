
#include <iostream>

using namespace std;

typedef struct _Node
{
	struct _Node *next;
	int data;
} Node;

Node* Xor(Node *m, Node *n)
{
	return reinterpret_cast<Node*>(reinterpret_cast<unsigned long>(m) ^ reinterpret_cast<unsigned long>(n));
}

void insert(Node** head, int x)
{
	Node *temp = new Node;
	temp->data = x;

	temp->next = Xor(NULL, *head);

	if ( *head != NULL )
	{
		Node *next = Xor(NULL, (*head)->next);
		(*head)->next = Xor(temp, next);
	}
	*head = temp;
}

void print(Node *head)
{
	Node *prev, *curr, *next;
	prev = NULL;
	curr = head;

	while(curr)
	{
		cout << " " << curr->data << " ";

		next = Xor(prev, curr->next);
		prev = curr;
		curr = next;
	}
	cout << endl;
}

int main()
{
	Node *head = NULL;
	insert(&head, 10);
	insert(&head, 20);
	insert(&head, 30);
	insert(&head, 40);
	insert(&head, 50);
	print(head);

	return 0;
}
