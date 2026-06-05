#pragma once
#include <iostream>
#include <queue>

struct Node
{
	int data;
	Node* left, * right;
	explicit Node(int key)
		:data(key), left(nullptr), right(nullptr)
	{}
};

// Pre-order DFS: Root, Left, Right
void preOrderDFS(Node* node) {
	if (node == nullptr) return;

	std::cout << node->data << " ";
	preOrderDFS(node->left);
	preOrderDFS(node->right);
}

// In-order DFS: Left, Root, Right
void inOrderDFS(Node* node) {
	if (node == nullptr) return;

	inOrderDFS(node->left);
	std::cout << node->data << " ";
	inOrderDFS(node->right);
}

// Post-order DFS: Left, Right, Root
void postOrderDFS(Node* node) {
	if (node == nullptr) return;

	postOrderDFS(node->left);
	postOrderDFS(node->right);
	std::cout << node->data << " ";
}

// BFS: Level order traversal
void BFS(Node* root) {

	if (root == nullptr) return;
	std::queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* node = q.front();
		q.pop();
		std::cout << node->data << " ";
		if (node->left != nullptr) q.push(node->left);
		if (node->right != nullptr) q.push(node->right);
	}
}

Node* insert(Node* root, int key) {
	// If the tree is empty, create the root node
	if (root == nullptr) {
		root = new Node(key);
		return root;
	}
	// Create a queue for BFS (level order traversal)
	std::queue<Node*> q;
	q.push(root);

	// Do BFS until we find an empty place
	while (!q.empty()) {
		Node* node = q.front();
		q.pop();

		// If left child is empty, insert the new node here
		if (node->left == nullptr) {
			node->left = new Node(key);
			break;
		}
		else {
			q.push(node->left);
		}
		// If right child is empty, insert the new node here
		if (node->right == nullptr) {
			node->right = new Node(key);
			break;
		}
		else {
			q.push(node->right);
		}
	}
	return root;
}

bool searchDFS(Node* root, int value) {
	// Base case: If the tree is empty or we've reached a leaf node
	if (root == nullptr) return false;

	// If the node's data is equal to the value we are searching for
	if (root->data == value) return true;

	// Recursively search in the left and right subtrees
	bool left_res = searchDFS(root->left, value);
	bool right_res = searchDFS(root->right, value);

	return left_res || right_res;
}

Node* deleteNode(Node* root, int val) {
	if (root == nullptr) return nullptr;
	// Use a queue to perform BFS
	std::queue<Node*> q;
	q.push(root);
	Node* target = nullptr;

	// Find the target node
	while (!q.empty()) {
		Node* curr = q.front();
		q.pop();

		// Check for current node is the target node to delete
		if (curr->data == val) {
			target = curr;
			break;
		}
		// Add children to the queue
		if (curr->left) q.push(curr->left);
		if (curr->right) q.push(curr->right);
	}
	// If target node is not found, return the original tree
	if (target == nullptr) return root;

	// Find the deepest rightmost node and its parent
	std::pair<Node*, Node*> last = { nullptr, nullptr };
	std::queue<std::pair<Node*, Node*>> q1;
	q1.push({ root, nullptr });

	while (!q1.empty()) {
		auto curr = q1.front();
		q1.pop();

		// Update the last
		last = curr;

		if (curr.first->left)
			q1.push({ curr.first->left, curr.first });
		if (curr.first->right)
			q1.push({ curr.first->right, curr.first });
	}

	Node* lastNode = last.first;
	Node* lastParent = last.second;

	// Replace target's value with the last node's value
	target->data = lastNode->data;

	// Remove the last node
	if (lastParent) {
		if (lastParent->left == lastNode)lastParent->left = nullptr;
		else lastParent->right = nullptr;
		delete lastNode;
	}
	else {
		// If the last node was the root
		delete lastNode;
		return nullptr;
	}
	return root;
}

