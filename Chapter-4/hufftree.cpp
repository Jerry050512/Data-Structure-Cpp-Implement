#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;

    Node(char sym, int freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
};

class HuffmanTree {
private:
    Node* root;
    unordered_map<char, string> codes;

    void buildCodes(Node* node, string code) {
        if (!node) return;

        if (node->symbol != '\0') {
            codes[node->symbol] = code;
        } else {
            buildCodes(node->left, code + "0");
            buildCodes(node->right, code + "1");
        }
    }

public:
    HuffmanTree(const vector<pair<char, int>>& frequencies) {
        priority_queue<Node*, vector<Node*>, CompareFrequency> pq;

        for (const auto& pair : frequencies) {
            pq.push(new Node(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            Node* parent = new Node('\0', left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }

        root = pq.top();
        buildCodes(root, "");
    }

    string encode(const string& text) {
        string encoded;
        for (char c : text) {
            encoded += codes[c];
        }
        return encoded;
    }

    string decode(const string& encoded) {
        string decoded;
        Node* curr = root;
        for (char bit : encoded) {
            if (bit == '0') {
                curr = curr->left;
            } else {
                curr = curr->right;
            }

            if (curr->symbol != '\0') {
                decoded += curr->symbol;
                curr = root;
            }
        }
        return decoded;
    }

private:
    struct CompareFrequency {
        bool operator()(Node* a, Node* b) {
            return a->frequency > b->frequency;
        }
    };
};

int main() {
    vector<pair<char, int>> frequencies = {
        {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
    };

    HuffmanTree huffman(frequencies);

    string text = "abacadaeafb";
    string encoded = huffman.encode(text);
    cout << "Encoded text: " << encoded << endl;

    string decoded = huffman.decode(encoded);
    cout << "Decoded text: " << decoded << endl;

    return 0;
}