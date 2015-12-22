#include <iostream>

using namespace std;

typedef struct _node
{
	int data;
	struct _node *left, *right;
	bool rightThread, leftThread;

	_node(int val)
	{
		data = val;
		left = right = NULL;
		leftThread = rightThread = false;
	}
} Node;


void insert(Node **root, int val)
{
	while (*root != NULL)
	{
		Node *curr = *root;
		if (val < curr->data) root = &curr->left;
		else if (val > curr->data) root = &curr->right;
		else return;
	}

	Node *temp = new Node(val);
	*root = temp;
}

void insertThreaded(Node **root, int val)
{
	Node *temp = new Node(val);
	if ( *root == NULL )
	{
		*root = temp;
	}
	else
	{
		while (*root != NULL)
		{
			Node *curr = *root;
			if ( val < curr->data )
			{
				if ( curr->leftThread )
				{
					temp->left = curr->left;
					temp->leftThread = true;
					curr->left = temp;
					curr->leftThread = false;
					temp->right = curr;
					temp->rightThread=true;
				}
				else if ( curr->left == NULL )
				{
					temp->right = curr;
					temp->rightThread=true;
					curr->left = temp;
					curr = temp;
				}
				root = &curr->left;
			}
			else if ( val > curr->data )
			{
				if ( curr->rightThread )
				{
					temp->right = curr->right;
					temp->rightThread = true;
					curr->right = temp;
					curr->rightThread = false;
					temp->left = curr;
					temp->leftThread = true;
				}
				else if ( curr->right == NULL )
				{
					temp->left = curr;
					temp->leftThread = true;
					curr->right = temp;
					curr = temp;
				}
				root = &curr->right;
			}
			else return;
		}
	}
}

Node* leftMost(Node *n)
{
	if (n == NULL) return n;
	while( n->left && !n->leftThread ) n = n->left;
	return n;
}

Node* rightMost(Node *n)
{
	if (n == NULL) return n;
	while( n->right && !n->rightThread ) n = n->right;
	return n;
}

void inOrderThreaded(Node *root)
{
	Node *curr = leftMost(root);
	while(curr != NULL)
	{
		cout << curr->data << " ";
		if (curr->rightThread) curr = curr->right;
		else curr = leftMost(curr->right);
	}
	cout << "\n";
}

void reverseInorderThreaded(Node *root)
{
	Node *curr = rightMost(root);
	while(curr != NULL)
	{
	cout << curr->data << " ";
		if (curr->leftThread) curr = curr->left;
		else curr = rightMost(curr->left);
	}
	cout << "\n";

}

void inOrder(Node *root)
{
	if (root == NULL) return;

	inOrder(root->left);
	cout << root->data << " ";
	inOrder(root->right);
}

int main()
{
	Node *root = NULL;

	//insert(&root, 6);
	//insert(&root, 3);
	//insert(&root, 1);
	//insert(&root, 5);
	//insert(&root, 8);
	//insert(&root, 7);
	//insert(&root, 11);
	//insert(&root, 13);
	//insert(&root, 9);

	//inOrder(root);

	insertThreaded(&root, 6);
	insertThreaded(&root, 3);
	insertThreaded(&root, 1);
	insertThreaded(&root, 5);
	insertThreaded(&root, 8);
	insertThreaded(&root, 7);
	insertThreaded(&root, 11);
	insertThreaded(&root, 13);
	insertThreaded(&root, 9);
	insertThreaded(&root, 4);

	inOrderThreaded(root);
	cout << "\n";
	reverseInorderThreaded(root);

	return 0;
}
