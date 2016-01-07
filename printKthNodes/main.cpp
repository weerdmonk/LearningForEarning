
#include <iostream>

using namespace std;

typedef struct _Node
{
	struct _Node *left, *right;
	int key;

	_Node(int data) { left = right = NULL; key = data; }

} Node;

void insert(Node **root, int key)
{
	if (*root == NULL)
	{
		Node *tmp = new Node(key);
		*root = tmp;
		return;
	}

	if (key > (*root) ->key) insert(&((*root)->right), key);
	else if (key < (*root)->key) insert(&((*root)->left), key);
}

void inorder(Node *root)
{
	if (root == NULL) return;

	inorder(root->left);
	cout << root->key << "\n";
	inorder(root->right);
}

void deleteTree(Node *root)
{
	if (root == NULL) return;

	deleteTree(root->left);
	deleteTree(root->right);

	delete root;
}

void printKthNodes(Node *root, Node *from, int k)
{
	if (root == NULL) return;
	static bool shouldCount = false;

	if (k == 0)
	{
		cout << root->key << "\n";
		return;
	}

	if (root == from) shouldCount = true;

	if (shouldCount)
	{
		printKthNodes(root->left, from, k - 1);
		printKthNodes(root->right, from, k - 1);

	}
	else
	{
		printKthNodes(root->left, from, k);
		printKthNodes(root->right, from, k);
	}
}

void printKthNodes(Node *root, Node *from, int k)
{
	if (root == NULL) return;

}

int main()
{
/*	
 *               7
 *              / \
 *             5   12
 *            / \   \
 *           1   6   20
 *            \
 *             3
 */

	Node *root = new Node(7);

	Node *from = root->left = new Node(5);
	
	root->right = new Node(12);

	root->left->left = new Node(1);
	root->left->right = new Node(6);

	root->right->right = new Node(20);

	root->left->left->right = new Node(3);

	//Node *root = NULL;
	//insert(&root, 7);
	//insert(&root, 5);
	//insert(&root, 12);
	//insert(&root, 1);
	//insert(&root, 6);
	//insert(&root, 20);

	printKthNodes(root, from, 2);

	/* delete the tree */
	deleteTree(root);


	return 0;
}
