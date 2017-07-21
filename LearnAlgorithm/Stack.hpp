// Created by Buwenjie
// 栈
#pragma once

#include <stdio.h>
#include <vector>

class Stack {
public:
	void push(int v) {
		mData.push_back(v);
	}

	int pop() {
		int res = top();
		mData.pop_back();
		return res;
	}

	int top() {
		return mData[size() - 1];
	}

	inline int size() {
		return mData.size();
	}

private:
	std::vector<int> mData;
};


void test_Stack() {
	std::vector<int> data = { 1, 2, 3, 4, 5 };
	Stack s;
	for (int v : data) {
		s.push(v);
	}
	while (s.size() > 0) {
		printf("%d\n", s.pop());
	}
}
