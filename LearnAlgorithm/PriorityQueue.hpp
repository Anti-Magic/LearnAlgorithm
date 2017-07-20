// Created by Buwenjie
// 最大堆实现的优先队列
#pragma once

#include <stdio.h>
#include <vector>
#include <algorithm> // std::swap

class PriorityQueue {
public:
	void push(int v) {
		mData.push_back(v);
		HeapUp(size() - 1);
	}

	int top() {
		return mData[0];
	}

	int pop() {
		int res = mData[0];
		std::swap(mData[0], mData[size() - 1]);
		mData.pop_back();
		HeapDown(0);
		return res;
	}

	inline int size() {
		return mData.size();
	}

private:
	inline int LeftChildIndex(int idx) {
		return idx * 2 + 1;
	}

	inline int RightChildIndex(int idx) {
		return idx * 2 + 2;
	}

	inline int ParentIndex(int idx) {
		return (idx - 1) / 2;
	}

	void HeapDown(int idxCur) {
		while (idxCur < size()) {
			int l = LeftChildIndex(idxCur);
			int r = RightChildIndex(idxCur);
			int idx = idxCur;
			int max = mData[idxCur];
			if (l < size() && mData[l] > max) {
				idx = l;
				max = mData[l];
			}
			if (r < size() && mData[r] > max) {
				idx = r;
				max = mData[r];
			}
			if (idx != idxCur) {
				std::swap(mData[idxCur], mData[idx]);
				idxCur = idx;
			}
			else {
				break;
			}
		}
	}

	void HeapUp(int idxCur) {
		while (idxCur > 0) {
			int p = ParentIndex(idxCur);
			if (mData[idxCur] > mData[p]) {
				std::swap(mData[idxCur], mData[p]);
				idxCur = p;
			}
			else {
				break;
			}
		}
	}

	std::vector<int> mData;
};

void test_PriorityQueue() {
	PriorityQueue q;
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	for (int v : data) {
		q.push(v);
	}
	while (q.size() > 0) {
		printf("%d ", q.pop());
	}
	printf("\n");
}
