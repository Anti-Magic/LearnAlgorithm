// Created by Buwenjie
// 链表
#pragma once

#include <stdio.h>

class LinkedListNode {
public:
	LinkedListNode(int v = 0) 
	: mValue(v)
	, mNext(nullptr) {
	}
	int mValue;
	LinkedListNode* mNext;
};

class LinkedList {
public:
	LinkedList() 
	: mSize(0) {
		mTail = mHead = new LinkedListNode();
	}

	~LinkedList() {
		free(mHead);
	}

	void insert(int v, int idx) {
		LinkedListNode* p1 = mHead;
		LinkedListNode* p2 = mHead->mNext;
		for (int i = 0; i < idx; i++) {
			p1 = p2;
			p2 = p2->mNext;
		}
		LinkedListNode* n = new LinkedListNode(v);
		n->mNext = p2;
		p1->mNext = n;
		mSize += 1;
	}

	void insertBack(int v) {
		LinkedListNode* n = new LinkedListNode(v);
		mTail->mNext = n;
		mTail = n;
		mSize += 1;
	}

	void remove(int idx) {
		LinkedListNode* p1 = mHead;
		LinkedListNode* p2 = mHead->mNext;
		for (int i = 0; i < idx; i++) {
			p1 = p2;
			p2 = p2->mNext;
		}
		p1->mNext = p2->mNext;
		delete p2;
		mSize -= 1;
	}

	int get(int idx) {
		LinkedListNode* p = mHead->mNext;
		for (int i = 0; i < idx; i++) {
			p = p->mNext;
		}
		return p->mValue;
	}

	inline int size() {
		return mSize;
	}

private:
	// 递归释放
	void free(LinkedListNode* n) {
		if (n == nullptr) {
			return;
		}
		free(n->mNext);
		delete n;
	}
	LinkedListNode* mHead;
	LinkedListNode* mTail;
	int mSize;
};


void test_LinkedList() {
	LinkedList list;
	list.insertBack(1);
	list.insertBack(3);
	list.insertBack(5);
	list.insertBack(7);
	list.insert(4, 2);
	list.remove(0);
	for (int i = 0; i < list.size(); i++) {
		printf("%d\n", list.get(i));
	}
}
