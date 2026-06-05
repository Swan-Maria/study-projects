#pragma once
#include <iostream>

struct Node
{
	int data;
	Node* left, * right;
	explicit Node(int key)
		:data(key), left(nullptr), right(nullptr)
	{
	}
};

Node* insert(Node* node, int key) 
{
    if (node == nullptr)
        return new Node(key);

    if (node->data == key)
        return node;

    if (node->data < key)
        node->right = insert(node->right, key);
    else
        node->left = insert(node->left, key);

    return node;
}

Node* search(Node* root, int key) 
{
    if (root == nullptr || root->data == key)
        return root;

    if (root->data < key)
        return search(root->right, key);

    return search(root->left, key);
}

Node* getSuccessor(Node* curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr)
        curr = curr->left;
    return curr;
}

Node* deleteNode(Node* root, int key) 
{
    if (root == nullptr)
        return root;

    // If key to be searched is in a subtree
    if (root->data > key)
        root->left = deleteNode(root->left, key);
    else if (root->data < key)
        root->right = deleteNode(root->right, key);

    // If root matches with the given key
    else {

        // Cases when root has 0 children
        // or only right child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // When root has only left child
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // When both children are present
        Node* succ = getSuccessor(root);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
    }
    return root;
}