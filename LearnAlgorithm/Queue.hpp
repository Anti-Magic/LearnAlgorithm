// Created by Buwenjie
// 队列。使用链表实现
#pragma once

#include <stdio.h>
#include <vector>
#include "LinkedList.hpp"

class Queue {
public:
	void push(int v) {
		mData.insertBack(v);
	}

	int pop() {
		int res = top();
		mData.remove(0);
		return res;
	}

	int top() {
		return mData.get(0);
	}

	inline int size() {
		return mData.size();
	}

private:
	LinkedList mData;
};


void test_Queue() {
	std::vector<int> data = { 1, 2, 3, 4, 5 };
	Queue q;
	for (int v : data) {
		q.push(v);
	}
	while (q.size() > 0) {
		printf("%d\n", q.pop());
	}
}
