
#include <iostream>

using namespace std;

typedef struct _btNode
{
	struct _btNode *smaller, *larger;
	int key;

	_btNode(int data) { smaller = larger = NULL; key = data; }

} BTNode;

BTNode *append(BTNode *small, BTNode *large)
{
    if (small == NULL) return large;
    if (large == NULL) return small;

    BTNode *smallEnd = small->smaller;
    BTNode *largeEnd = large->smaller;

    smallEnd->larger = large;
    small->smaller = largeEnd;
    largeEnd->larger = small;
    large->smaller = smallEnd;
    
    return small;
}

BTNode *treeToList(BTNode *root)
{
    BTNode *smallerList, *largerList;
    // terminate recursion
    if (root == NULL) return NULL;

    // get smaller and larger lists
    smallerList = treeToList(root->smaller);
    largerList = treeToList(root->larger);

    // for append routine to work, to find the last node
    root->smaller = root;
    root->larger = root;

    // combine lists
    smallerList = append(smallerList, root);
    smallerList = append(smallerList, largerList);

    return smallerList;
}

void printList(BTNode *head)
{
    BTNode *crawl = head;
    while(crawl != NULL)
    {
        cout << crawl->key << "\n";
        crawl = crawl->larger;
        if (crawl == head) break;
    }
    return;
}

void deleteList(BTNode *head)
{
    BTNode *prev, *next;

    while (head != NULL)
    {
        prev = head->smaller;
        next = head->larger;
        if (prev == next) break;
        prev->larger = next;
        next->smaller = prev;
        delete head;
        head = prev;
    }

    delete prev;
}

int main()
{

	BTNode *root = new BTNode(7);

	root->smaller = new BTNode(5);
	root->larger = new BTNode(12);

	root->smaller->smaller = new BTNode(1);
	root->smaller->larger - new BTNode(6);

	root->larger->smaller = new BTNode(9);

    BTNode *head = treeToList(root);
    printList(head);
    deleteList(head);

	// delete the tree

	//delete root->larger->smaller;

	//delete root->smaller->smaller;
	//delete root->smaller->larger;

	//delete root->smaller;
	//delete root->larger;	

	//delete root;

	//return 0;
}
