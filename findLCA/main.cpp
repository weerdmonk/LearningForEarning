#include <iostream>
using namespace std;

typedef struct _node
{
	int key;
	struct _node *left, *right;

} Node;

Node *findLCA(Node *root, int k1, int k2)
{
	// if root is NULL, tree is empty. return NULL
	if (!root) return NULL;

	// if root's key matches either of the keys return root as LCA
	// inorder to report presence of anyone of the keys
	if ( root->key == k1 || root->key == k2) return root;

	// if root's key doesnot match any key then recurse left and right
	Node *leftLCA = findLCA(root->left, k1, k2);
	Node *righttLCA = findLCA(root->right, k1, k2);

	// if left and right subtrees contain the keys root is LCA
	if (leftLCA && rightLCA) return root;

	// either of left or right subtree can have the keys
	if (!leftLCA) return rightLCA;
	else return leftLCA;
}



int main()
{


	return 0;
}
