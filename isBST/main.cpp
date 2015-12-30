
#include <iostream>

using namespace std;

typedef struct _btNode
{
	struct _btNode *left, *right;
	int key;

	_btNode(int data) { left = right = NULL; key = data; }

} BTNode;

bool isBST(BTNode *root)
{
	if (!root) return true;
	bool isLeftBst = true, isRightBst= true, isBst = true;

	if (root->left)
	{
		isBst = root->left->key < root->key;
		isLeftBst = isBST(root->left);
	}
	if (root->right)
	{
		isBst &= root->right->key > root->key;
		isRightBst = isBST(root->right);
	}
	return ( isBst && isLeftBst && isRightBst );
}

bool isBST2(BTNode *root)
{
	static BTNode *prev = NULL;

	if (root)
	{
		if (!isBST2(root->left)) return false;

		if (prev != NULL && root->key <= prev->key) return false;

		prev = root;

		
		return isBST2(root->right);
	}

	return true;
}

int main()
{

	BTNode *root = new BTNode(7);

	root->left = new BTNode(5);
	root->right = new BTNode(12);

	root->left->left = new BTNode(1);
	root->left->right = new BTNode(3);

	root->right->left = new BTNode(9);

	cout << isBST2(root) << endl;

	// delete tree

	delete root->right->left;

	delete root->left->left;
	delete root->left->right;

	delete root->left;
	delete root->right;	

	delete root;

	return 0;
}
