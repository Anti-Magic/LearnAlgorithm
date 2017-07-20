// Created by Buwenjie
// 堆排序
// 主要有2种思路
// 1是使用辅助空间建立最小堆，然后依次从堆上删除，放回原数组。（也就是先放入优先队列中，再依次pop出来）
// 2是直接把原数组调整为最大堆，然后把堆上删除的元素放到数组末尾，然后heapSize - 1
// 在排序这个需求上，显然第二种较优

// 堆的几个性质（起始下标为0）
// 1、下标 >= heapSize/2 时，为叶子节点。反之为非叶子节点
#pragma once

#include <stdio.h>
#include <vector>
#include <algorithm> // std::swap

inline int HeapLeftChildIndex(int idx) {
	return idx * 2 + 1;
}

inline int HeapRightChildIndex(int idx) {
	return idx * 2 + 2;
}

inline int HeadParentIndex(int idx) {
	return (idx - 1) / 2;
}

void HeapDown(std::vector<int>& data, int heapSize, int idxCur) {
	int l = HeapLeftChildIndex(idxCur);
	int r = HeapRightChildIndex(idxCur);
	// 当前节点的值如果小于左孩子或右孩子的值，则当前节点与较大值交换，即当前节点下沉
	int idx = idxCur;
	int max = data[idxCur];
	if (l < heapSize && data[l] > max) {
		idx = l;
		max = data[l];
	}
	if (r < heapSize && data[r] > max) {
		idx = r;
		max = data[r];
	}
	if (idx != idxCur) {
		std::swap(data[idxCur], data[idx]);
		// 递归继续下沉
		HeapDown(data, heapSize, idx);
	}
}

// HeapDown的非递归版本
void HeapDown2(std::vector<int>& data, int heapSize, int idxCur) {
	while (idxCur < heapSize) {
		int l = HeapLeftChildIndex(idxCur);
		int r = HeapRightChildIndex(idxCur);
		int idx = idxCur;
		int max = data[idxCur];
		if (l < heapSize && data[l] > max) {
			idx = l;
			max = data[l];
		}
		if (r < heapSize && data[r] > max) {
			idx = r;
			max = data[r];
		}
		if (idx != idxCur) {
			std::swap(data[idxCur], data[idx]);
			idxCur = idx;
		}
		else {
			break;
		}
	}
}

void HeapSort(std::vector<int>& data) {
	// 从下层往上，依次调用HeapDown，使整个数组变为合法的最大堆
	int heapSize = data.size();
	for (int i = heapSize / 2 - 1; i >= 0; i--) {
		HeapDown2(data, heapSize, i);
	}
	while (heapSize > 1) {
		// 从堆顶删除元素，放到数组末尾，然后heapSize - 1
		std::swap(data[0], data[heapSize - 1]);
		heapSize -= 1;
		// 末尾的元素现在在堆顶，使其下沉，调整为合法的最大堆
		HeapDown2(data, heapSize, 0);
	}
}


void test_HeapSort() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	HeapSort(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
