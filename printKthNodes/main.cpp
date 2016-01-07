
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

/* more precisely print children at kth depth */
void printKthChildren(Node *root, int k)
{
	if ( root == NULL || k  < 0 ) return;

	if (k == 0)
	{
		cout << root->key << "\n";
		return;
	}
	printKthChildren(root->left, k - 1);
	printKthChildren(root->right, k - 1);
}

/* print nodes at k distance  */
/*
 * if target node is found in subtree
 * 	//return the position of parent relative to child node
 * 	return distance of parent relative to child node
 * else
 * 	return -1 as guard value if target node is not found
 *
 * 
 */
int printKthNodes(Node *root, Node *from, int k)
{
	// parent node is leaf node so return guard value
	if (root == NULL) return -1;

	// base case, target node is found
	if (root == from ) 
	{
		printKthChildren(root, k);
		// as this node is target node, its calling parent is at distance 1
		return 1;
	}

	// if current node is not target node recurse left subtree
	int distLeft = printKthNodes(root->left, from, k);
	if (distLeft != -1) // target node was found on left subtree
	{
		if (distLeft == k) // current node is at k distance from target node so print it
		{
			cout << root->key << "\n";
		}
		else // current is not at k distance from target node so either parent should be printed or a node in the right subtree
		{
			// lets check the right subtree with new k = k - (distance of current node from target + distance of right child)
			// so new k = k - (distLeft - 1)
			printKthChildren(root->right, k - distLeft - 1);
		}
		// return distance of current node from target plus one (as parent is at distance one from current node)
		return distLeft++;
	}

	// if target node was not found in left subtree recurse right subtree
	int distRight = printKthNodes(root->right, from, k);
	if (distRight != -1) // target node was fount on right subtree
	{
		if ( distRight == k ) // current is at distance k from target node, so print it
		{
			cout << root->key << "\n";
		}
		else // current is not distance k from target node so either parent should be printed of a nodee in the left subtree
		{
			// lets check ;eft subtree with new k
			printKthChildren(root->right, k - distRight - 1);
		}
		// return distance of current node from target plus one (as parent is at distance one from current node)
		return distRight++;
	}

	// gaurd value as we have not encountered target node yet
	return -1;
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
