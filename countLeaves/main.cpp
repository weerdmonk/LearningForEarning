
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

int countLeaves(Node *root)
{
	if (root == NULL) return 0;

	else if ( (root->left == NULL) && (root->right == NULL) ) return 1;

	else return countLeaves(root->left) + countLeaves(root->right);
}

int main()
{
/*	
 *               7
 *              / \
 *             5   12
 *            / \   \
 *           1   6   20
 */

	Node *root = new Node(7);

	root->left = new Node(5);
	root->right = new Node(12);

	root->left->left = new Node(1);
	root->left->right =	 new Node(6);

	root->right->right = new Node(20);

	//Node *root = NULL;
	//insert(&root, 7);
	//insert(&root, 5);
	//insert(&root, 12);
	//insert(&root, 1);
	//insert(&root, 6);
	//insert(&root, 20);

	cout << countLeaves(root) << "\n";

	/* delete the tree */

	deleteTree(root);

	//delete root->right->left;

	//delete root->left->left;
	//delete root->left->right;

	//delete root->left;
	//delete root->right;	

	//delete root;

	return 0;
}
