#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct _node
{
	int key;
	struct _node *left, *right;
	_node(int _key)
	{
		key = _key;
		left = right = NULL;
	}

} Node;

// incase of a binary search tree LCA shall lie between k1 and k2
// k1 < LCA->key < k2
// TODO handle case when k1 and/or k2 is not present
// TODO hadnle case when root is equal to k1 or k2
Node *findLCA(Node *root, int k1, int k2)
{
	if (!root) return NULL;

	if ( root->key < k1 && root->key < k2) return findLCA(root->right, k1, k2);

	if ( root->key > k1 && root->key > k2) return findLCA(root->left, k1, k2);

	return root; 
}

int main(int argc, char **argv)
{
	Node *root = new Node(10);

	root->left = new Node(5); 
	root->right = new Node(15);

	root->left->left = new Node(3);

	root->right->left = new Node(14);
	root->right->right = new Node(20);

	root->right->right->left = new Node(17);

	int k1, k2;
	if (argc == 3)
	{
		k1 = atoi(argv[1]);
		k2 = atoi(argv[2]);
	}
	else
	{
		cin >> k1 >> k2;
	}

	Node *LCA = findLCA(root, k1, k2);
	if (LCA) cout << LCA->key << endl;
	else cout << "Key(s) not found!\n";

	// delete nodes

	delete root->right->right->left;

	delete root->right->left;
	delete root->right->right;

	delete root->left->left;

	delete root->left;
	delete root->right;

	delete root;

	return 0;
}
