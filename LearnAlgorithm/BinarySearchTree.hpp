// Created by Buwenjie
#pragma once

#include <vector>

class BinarySearchTreeNode {
public:
	BinarySearchTreeNode(int value)
	: mValue(value)
	, mLeft(nullptr)
	, mRight(nullptr) {
	}
	int mValue;
	BinarySearchTreeNode* mLeft;
	BinarySearchTreeNode* mRight;
};

class BinarySearchTree {
public:
	BinarySearchTree()
	: mRoot(nullptr) {
	}

	~BinarySearchTree() {
		freeNode(mRoot);
	}

	void insert(int value) {
		if (mRoot == nullptr) {
			mRoot = new BinarySearchTreeNode(value);
		}
		else {
			BinarySearchTreeNode* p = mRoot;
			while (true) {
				if (value <= p->mValue) {
					if (p->mLeft == nullptr) {
						p->mLeft = new BinarySearchTreeNode(value);
						break;
					}
					else {
						p = p->mLeft;
					}
				}
				else {
					if (p->mRight == nullptr) {
						p->mRight = new BinarySearchTreeNode(value);
						break;
					}
					else {
						p = p->mRight;
					}
				}
			}
		}
	}

	void inorderWalk(std::vector<int>& v) {
		inorderWalkNode(mRoot, v);
	}

private:
	void inorderWalkNode(BinarySearchTreeNode* node, std::vector<int>& v) {
		if (node == nullptr) {
			return;
		}
		inorderWalkNode(node->mLeft, v);
		v.push_back(node->mValue);
		inorderWalkNode(node->mRight, v);
	}

	void freeNode(BinarySearchTreeNode* node) {
		if (node == nullptr) {
			return;
		}
		freeNode(node->mLeft);
		freeNode(node->mRight);
		delete node;
	}

	BinarySearchTreeNode* mRoot;
};

#include <stdio.h>
void test_BinarySearchTree() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	BinarySearchTree tree;
	for (auto v : data) {
		tree.insert(v);
	}
	std::vector<int> res;
	tree.inorderWalk(res);
	for (auto v : res) {
		printf("%d ", v);
	}
	printf("\n");
}
