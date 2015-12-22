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

Node *findLCA(Node *root, int k1, int k2)
{
	// if root is NULL, tree is empty. return NULL
	if (!root) return NULL;

	// if root's key matches either of the keys return root as LCA
	// inorder to report presence of anyone of the keys
	if ( root->key == k1 || root->key == k2) return root;

	// if root's key doesnot match any key then recurse left and right
	Node *leftLCA = findLCA(root->left, k1, k2);
	Node *rightLCA = findLCA(root->right, k1, k2);

	// if left and right subtrees contain the keys root is LCA
	if (leftLCA && rightLCA) return root;

	// either of left or right subtree can have the keys
	if (!leftLCA) return rightLCA;
	else return leftLCA;
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
