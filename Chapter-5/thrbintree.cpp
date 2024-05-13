#include <iostream>

using namespace std;

// https://gist.github.com/Ajinkya-Sonawane/09075349e8b70ef9c02f7f6d61e757ab

struct Node {
    int data;
    Node* left;
    Node* right;
    bool leftThread; // 0 if left is a child, 1 if left is a thread
    bool rightThread; // 0 if right is a child, 1 if right is a thread

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        leftThread = false;
        rightThread = false;
    }
};

class ThreadedBinaryTree {
private:
    Node* root;
    Node* head; // Head of the threaded list

    void insert(Node*& node, int value) {
        if (node == nullptr) {
            node = new Node(value);
        } else if (value < node->data) {
            insert(node->left, value);
        } else {
            insert(node->right, value);
        }
    }

    void threadedTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        // Visit the leftmost node first
        threadedTraversal(node->left);

        // If the left child is null, we need to make it a thread
        if (node->left == nullptr) {
            node->leftThread = true;
            node->left = prevNode;
        }

        // If the previous node's right child is null, we need to make it a thread
        if (prevNode != nullptr && prevNode->right == nullptr) {
            prevNode->rightThread = true;
            prevNode->right = node;
        }

        prevNode = node; // Update prevNode to the current node

        // Visit the right child
        threadedTraversal(node->right);
    }

    Node* prevNode; // Used for threading

public:
    ThreadedBinaryTree() {
        root = nullptr;
        head = nullptr;
        prevNode = nullptr;
    }

    void insert(int value) {
        insert(root, value);
    }

    void makeThreaded() {
        prevNode = nullptr;
        threadedTraversal(root);

        // Find the head (leftmost node)
        Node* curr = root;
        while (curr->left != nullptr && curr->leftThread == false) {
            curr = curr->left;
        }
        head = curr;
    }

    void inorderTraversal() {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            if (curr->rightThread) {
                curr = curr->right;
            } else {
                curr = curr->left;
                while (curr != nullptr && curr->leftThread == false) {
                    curr = curr->right;
                }
            }
        }
        cout << endl;
    }

};

int main() {
    ThreadedBinaryTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    tree.makeThreaded();

    cout << "Inorder Traversal: ";
    tree.inorderTraversal();

    return 0;
}