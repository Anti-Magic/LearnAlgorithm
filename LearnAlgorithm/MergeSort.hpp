// Created by Buwenjie
// 归并排序
#pragma once

#include <stdio.h>
#include <vector>

void MergeSortWork(std::vector<int>& data, int leftA, int rightB, std::vector<int>& buf) {
	// 分成2段分别排序
	int rightA = leftA + (rightB - leftA) / 2;
	int LeftB = rightA + 1;
	if (rightA > leftA) { // 元素数量 <= 1，此时当然是有序的
		MergeSortWork(data, leftA, rightA, buf);
	}
	if (rightB > LeftB) {
		MergeSortWork(data, LeftB, rightB, buf);
	}
	// 把2段已排序好的合并，使用buf做辅助空间
	int i = leftA;
	int j = LeftB;
	int k = 0;
	while (i <= rightA && j <= rightB) {
		if (data[i] < data[j]) {
			buf[k++] = data[i++];
		}
		else {
			buf[k++] = data[j++];
		}
	}
	while (i <= rightA) {
		buf[k++] = data[i++];
	}
	while (j <= rightB) {
		buf[k++] = data[j++];
	}
	// 合并完成，把buf的内容拷贝回data
	for (i = 0; i < k; i++) {
		data[leftA + i] = buf[i];
	}
}

void MergeSort(std::vector<int>& data) {
	if (data.size() <= 1) {
		return;
	}
	std::vector<int> buf(data.size());
	MergeSortWork(data, 0, data.size() - 1, buf);
}


void test_MergeSort() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	MergeSort(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
