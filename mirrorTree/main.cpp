
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

int height(Node *root)
{
	if (root == NULL) return 0;

	int lh = height(root->left);
	int rh = height(root->right);

	return (lh > rh) ? lh + 1 : rh + 1;
}

int size(Node *root)
{
	if (root == NULL) return 0;

	int lsize = size(root->left);
	int rsize = size(root->right);

	return lsize + rsize + 1;
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

void mirror(Node *root)
{
	if (root == NULL) return;

	Node *swp = NULL;

	mirror(root->left);
	mirror(root->right);

	swp = root->left;
	root->left = root->right;
	root->right = swp;
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

	cout << "Size = " << size(root) << "\n\n";
	printLvlOrder(root);
	cout << "\nmirroring tree...\n";
	mirror(root);
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
