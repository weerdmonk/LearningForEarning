
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

/*
 * Instead of using double pointer
 * return the updated pointer
 * and store it.
 *
 * root = update(root);
 */
Node *insert2(Node *root, int key)
{
	if (root == NULL)
	{
		return new Node(key);
	}

	if (key < root->key) root->left = insert2(root->left, key);
	else if (key > root->key) root->right = insert2(root->right, key);

	return root;
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

/* 
 * dumber approach
 * complexity = O(n ^ 2)
 *
 */
int height(Node *root)
{
	if (root == NULL) return 0;

	int lh = height(root->left);
	int rh = height(root->right);

	return (lh > rh) ? lh + 1 : rh + 1;
}

void printLvl(Node *root, int lvl)
{
	if (root == NULL) return;

	if (lvl == 1)  cout << root->key << " ";
	else
	{
		printLvl(root->left, lvl - 1);
		printLvl(root->right, lvl - 1);
	}
}

void printLvlOrder(Node *root)
{
	if (root == NULL) return;

	int h = height(root);
	for (int i = 1; i <= h; i++)
	{
		printLvl(root, i);
		cout << "\n";
	}
}

/*
 * smarter approach - use queue
 * complexity = O(n)
 * 
 * pseudo code:
 * 1. create a queue
 * 2. enque root node
 * 3. while queue is not empty
 *     1. current node = deque a node
 *     2. print current node's key
 *     3. enque left then right children of current node
 */

int size(Node *root)
{
	if (root == NULL) return 0;

	int lsize = size(root->left);
	int rsize = size(root->right);

	return lsize + rsize + 1;
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

	//Node *root = new Node(7);

	//root->left = new Node(5);
	//root->right = new Node(12);

	//root->left->left = new Node(1);
	//root->left->right =	 new Node(6);

	//root->right->right = new Node(20);

	Node *root = NULL;
	//insert(&root, 7);
	//insert(&root, 5);
	//insert(&root, 12);
	//insert(&root, 1);
	//insert(&root, 6);
	//insert(&root, 20);

	root = insert2(root, 7);
	root = insert2(root, 5);
	root = insert2(root, 12);
	root = insert2(root, 1);
	root = insert2(root, 6);
	root = insert2(root, 20);

	//inorder(root);
	cout << "Size = " << size(root) << "\n\n";
	printLvlOrder(root);

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
