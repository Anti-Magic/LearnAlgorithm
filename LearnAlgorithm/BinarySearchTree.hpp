// Created by Buwenjie
#pragma once

#include <vector>

class BinarySearchTreeNode {
public:
	BinarySearchTreeNode(int value, BinarySearchTreeNode* parent = nullptr)
	: mValue(value)
	, mParent(parent)
	, mLeft(nullptr)
	, mRight(nullptr) {
	}
	int mValue;
	BinarySearchTreeNode* mParent;
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

	BinarySearchTreeNode* root() {
		return mRoot;
	}

	// 插入
	void insert(int value) {
		if (mRoot == nullptr) {
			mRoot = new BinarySearchTreeNode(value);
		}
		else {
			BinarySearchTreeNode* p = mRoot;
			while (true) {
				if (value <= p->mValue) {
					if (p->mLeft == nullptr) {
						p->mLeft = new BinarySearchTreeNode(value, p);
						break;
					}
					else {
						p = p->mLeft;
					}
				}
				else {
					if (p->mRight == nullptr) {
						p->mRight = new BinarySearchTreeNode(value, p);
						break;
					}
					else {
						p = p->mRight;
					}
				}
			}
		}
	}

	// 删除节点
	// 为了容易理解，if分支比较多
	void remove(BinarySearchTreeNode* node) {
		// 如果node没有孩子，则直接删除
		if (node->mLeft == nullptr && node->mRight == nullptr) {
			transplant(node, nullptr);
		}
		// 如果node只有一个孩子，则用这个孩子替代node的位置
		else if (node->mLeft != nullptr && node->mRight == nullptr) {
			transplant(node, node->mLeft);
		}
		else if (node->mLeft == nullptr && node->mRight != nullptr) {
			transplant(node, node->mRight);
		}
		// 如果有2个孩子
		else {
			// node的后继y（y一定在node的右子树中，且y是右子树的最小值，所以y肯定没有左孩子）
			BinarySearchTreeNode* y = successor(node);
			// 如果y是node的右孩子，则直接用y替代node
			// 替换后，把node的左孩子设为y的左孩子(y原本没有左孩子)，y的右孩子不变
			if (y == node->mRight) {
				transplant(node, y);
				y->mLeft = node->mLeft;
				y->mLeft->mParent = y;
			}
			// y不是node的右孩子
			else {
				// 先用y的右孩子代替y（上面说过，y是没有左孩子的），这时y已经相当于没有孩子的节点了
				transplant(y, y->mRight);
				// 再用y代替node，把node的2个孩子设为y的孩子
				transplant(node, y);
				y->mLeft = node->mLeft;
				y->mLeft->mParent = y;
				y->mRight = node->mRight;
				y->mRight->mParent = y;
			}
		}
		delete node;
	}

	// 中序遍历
	void inorderWalk(BinarySearchTreeNode* node, std::vector<int>& v) {
		if (node == nullptr) {
			return;
		}
		inorderWalk(node->mLeft, v);
		v.push_back(node->mValue);
		inorderWalk(node->mRight, v);
	}

	// 查找
	BinarySearchTreeNode* search(int v) {
		BinarySearchTreeNode* p = mRoot;
		while (p != nullptr && p->mValue != v) {
			if (v < p->mValue) {
				p = p->mLeft;
			}
			else {
				p = p->mRight;
			}
		}
		return p;
	}

	// 最小值
	BinarySearchTreeNode* minimum(BinarySearchTreeNode* p) {
		while (p->mLeft != nullptr) {
			p = p->mLeft;
		}
		return p;
	}

	// 最大值
	BinarySearchTreeNode* maximum(BinarySearchTreeNode* p) {
		while (p->mRight != nullptr) {
			p = p->mRight;
		}
		return p;
	}

	// 前驱
	BinarySearchTreeNode* predecessor(BinarySearchTreeNode* node) {
		if (node->mLeft != nullptr) {
			return maximum(node->mLeft);
		}
		BinarySearchTreeNode* parent = node->mParent;
		while (parent != nullptr && node == parent->mLeft) {
			node = parent;
			parent = node->mParent;
		}
		return parent;
	}

	// 后继
	BinarySearchTreeNode* successor(BinarySearchTreeNode* node) {
		if (node->mRight != nullptr) {
			return minimum(node->mRight);
		}
		// node没有右子树，说明在当前子树中，node是最大值，这时需要沿着parent向上找
		// 直到node是parent的左孩子，这时parent就是后继
		// 设最终的结果为R，因为R的右子树都大于R，R的左子树都小于R，且node为当前子树的最大值
		// 所以当前子树的根节点是R的左孩子
		BinarySearchTreeNode* parent = node->mParent;
		while (parent != nullptr && node == parent->mRight) {
			node = parent;
			parent = node->mParent;
		}
		return parent;
	}

private:
	// 释放
	void freeNode(BinarySearchTreeNode* node) {
		if (node == nullptr) {
			return;
		}
		freeNode(node->mLeft);
		freeNode(node->mRight);
		delete node;
	}

	// 用des节点替换src节点
	void transplant(BinarySearchTreeNode* src, BinarySearchTreeNode* des) {
		if (src->mParent == nullptr) {
			mRoot = des;
		}
		else {
			if (src == src->mParent->mLeft) {
				src->mParent->mLeft = des;
			}
			else {
				src->mParent->mRight = des;
			}
		}
		if (des != nullptr) {
			des->mParent = src->mParent;
		}
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
	// inorder
	std::vector<int> res;
	tree.inorderWalk(tree.root(), res);
	for (auto v : res) {
		printf("%d ", v);
	}
	printf("\n");
	// search
	std::vector<int> search = { 7, 10, 3 };
	for (auto v : search) {
		auto p = tree.search(v);
		if (p != nullptr) {
			printf("%d found\n", v);
		}
		else {
			printf("%d not found\n", v);
		}
	}
	// min max
	printf("minimum %d\n", tree.minimum(tree.root())->mValue);
	printf("maximum %d\n", tree.maximum(tree.root())->mValue);
	// predecessor
	printf("predecessor:\n");
	for (auto v : data) {
		auto p = tree.predecessor(tree.search(v));
		if (p == nullptr) {
			printf("%d null\n", v);
		}
		else {
			printf("%d %d\n", v, p->mValue);
		}
	}
	// successor
	printf("successor:\n");
	for (auto v : data) {
		auto p = tree.successor(tree.search(v));
		if (p == nullptr) {
			printf("%d null\n", v);
		}
		else {
			printf("%d %d\n", v, p->mValue);
		}
	}
	// remove
	for (auto v : data) {
		tree.remove(tree.search(v));
		res.clear();
		tree.inorderWalk(tree.root(), res);
		for (auto v : res) {
			printf("%d ", v);
		}
		printf("\n");
		tree.insert(v);
	}
}
