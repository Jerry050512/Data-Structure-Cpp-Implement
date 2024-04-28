#include <iostream>

using namespace std;

// Node structure
struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }

    ~Node()
    {
        // Recursive destruction of child nodes
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }
};

// Binary Tree class
class BinaryTree
{
private:
    Node *root;

public:
    BinaryTree()
    {
        root = nullptr;
    }

    // Insert a new node
    void insert(int value)
    {
        root = insertNode(root, value);
    }

    // Helper function to insert a new node
    Node *insertNode(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }

        return node;
    }

    // Inorder traversal
    void inorderTraversal()
    {
        inorderTraversalHelper(root);
        cout << endl;
    }

    // Helper function for inorder traversal
    void inorderTraversalHelper(Node *node)
    {
        if (node != nullptr)
        {
            inorderTraversalHelper(node->left);
            cout << node->data << " ";
            inorderTraversalHelper(node->right);
        }
    }

    void preorderTraversal()
    {
        preorderTraversalHelper(root);
        cout << endl;
    }

    void preorderTraversalHelper(Node *node)
    {
        if (node != nullptr)
        {
            cout << node->data << " ";
            preorderTraversalHelper(node->left);
            preorderTraversalHelper(node->right);
        }
    }

    void postorderTraversal()
    {
        postorderTraversalHelper(root);
        cout << endl;
    }

    void postorderTraversalHelper(Node *node)
    {
        if (node != nullptr)
        {
            postorderTraversalHelper(node->left);
            postorderTraversalHelper(node->right);
            cout << node->data << " ";
        }
    }
};

int main()
{
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);

    cout << "Inorder Traversal: ";
    tree.inorderTraversal(); // Output: Inorder Traversal: 1 3 4 5 7

    cout << "Preorder Traversal: ";
    tree.preorderTraversal();

    cout << "Postorder Traversal: ";
    tree.postorderTraversal();

    return 0;
}