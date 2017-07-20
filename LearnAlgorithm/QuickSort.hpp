// Created by Buwenjie
// 快速排序
#pragma once

#include <stdio.h>
#include <vector>

void QuickSortWork(std::vector<int>& data, int low, int high) {
	if (low >= high) {
		return;
	}
	int i = low;
	int j = high;
	int v = data[low];
	while (i < j) {
		// 从右边找一个小于v的放在左边
		while (i < j && data[j] >= v) {
			j -= 1;
		}
		if (i >= j) {
			break;
		}
		data[i] = data[j];
		// 从左边找一个大于v的放在右边
		while (i < j && data[i] <= v) {
			i += 1;
		}
		if (i >= j) {
			break;
		}
		data[j] = data[i];
	}
	data[i] = v;
	QuickSortWork(data, low, i);
	QuickSortWork(data, i+1, high);
}

void QuickSort(std::vector<int>& data) {
	QuickSortWork(data, 0, data.size() - 1);
}


void test_QuickSort() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	QuickSort(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
