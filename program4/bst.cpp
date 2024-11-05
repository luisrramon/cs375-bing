// Luis Ramon
#include <iostream>
using namespace std;

struct BST
{
    int key;        // data stored in the node
    BST* left;      // pointer to left child
    BST* right;     // pointer to right child
    BST* p;         // pointer to parent

    // Constructor to initialize node with key & set pointers to null
    BST(int value)
    {
        key = value;
        left = nullptr;
        right = nullptr;
        p = nullptr;
    }
};

void inOrder(BST* node, int depth)
{
    if (node != nullptr)
    {
        inOrder(node->left, depth + 1); // traverse left subtree
        cout << node->key << ": " << depth << endl; // print node's key and its depth
        inOrder(node->right, depth + 1); // traverse right subtree
    }
}
BST* search(BST* node, int k)
{
    if (node == nullptr || k == node->key)
    {
        return node;
    }
    if (k < node->key)
    {
        return search(node->left, k); // continue search in the left subtree of node
    }
    else
    {
        return search(node->right, k); // search continues in the right subtree of node
    }
}
// takes in a binary search tree T and a node z
void insert(BST*& root, int key)
{
    BST* z = new BST(key); // create new node with the key

    BST* y = nullptr; // y tracks the parent node
    BST* x = root; // x is the current node being examined

    // traverse tree to find appropriate position for new node
    while ( x != nullptr)
    {
        y = x;
        if (z->key < x->key) // move to the left child
        {
            x = x->left;
        }
        else // move to the right child
        {
            x=x->right;
        }
        
    }
    z->p = y; // set parent of the new node
    if (y == nullptr)
    {
        root = z; // if the tree is empty, make the new node the root
    }
    else if (z->key < y->key)
    {
        y->left = z; // attach as the left child
    }
    else
    {
        y->right = z; // attach as the right child
    }
}
BST* treeMinimum(BST* x)
{
    // traverse to the leftmost node, which the minimum
    while(x->left != nullptr)
    {
        x = x->left;
    }
    return x;
}
void transplant(BST*& root, BST* u, BST* v)
{
    if (u->p == nullptr) // u is root
    {
        root = v;
    }
    else if (u == u->p->left) // u is left child
    {
        u->p->left = v;
    }
    else // u is right child
    {
        u->p->right = v;
    }
    if (v != nullptr)
    {
        v->p = u->p; // update parent of v if v is not null
    }
}

void deletion(BST*& root, BST* z)
{
    if (z->left == nullptr) // case 1: no left child
    {
        transplant(root, z, z->right); 
    }
    else if (z->right == nullptr) // case 2: no right child
    {
        transplant(root, z, z->left);
    }
    else // case 3: two children
    {
        BST* y = treeMinimum(z->right); // find the minimum node in the right subtree
        if (y->p != z) // if y is not the direct child of z
        {
            transplant(root, y, y->right);
            y->right = z->right; // link y's right subtree to z's right child
            y->right->p = y;   // update parent pointer
        }
        transplant(root, z, y); // replace z with y
        y->left = z->left; // link y's left subtree to z's left child
        y->left->p = y; // update parent pointer
    }
}

int main(int argc, char *argv[])
{
    int numstoInsert;
    cin >> numstoInsert; // read number of nodes to insert

    BST* root = nullptr;

    // insert nodes into the BST
    for (int i=0; i < numstoInsert; i++)
    {
        int val;
        cin >> val;
        insert(root, val);
    }

    int numstoDelete;
    cin >> numstoDelete;
    
    // delete nodes from the BST
    for (int i = 0; i < numstoDelete; i++)
    {
        int val;
        cin >> val;
        BST* nodeToDelete = search(root, val); // find node to delete
        if (nodeToDelete != nullptr)
        {
            deletion(root, nodeToDelete); // perform deletion
        }
    }

    // print out all keys in BST in sorted order with their depths
    inOrder(root, 0);

    return 0;
}
