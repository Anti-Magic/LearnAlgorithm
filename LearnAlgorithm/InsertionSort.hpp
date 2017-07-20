// Created by Buwenjie
// 插入排序
#pragma once

#include <stdio.h>
#include <vector>

void InsertionSort(std::vector<int>& data) {
	for (int i = 1; i < data.size(); i++) {
		// 当前要插入的值v
		int v = data[i];
		// 从位置i-1向前遍历，大于v的后移一个位置
		int j = i - 1;
		while (j >= 0 && data[j] > v) {
			data[j + 1] = data[j];
			j -= 1;
		}
		// v插入到空出的位置中
		data[j + 1] = v;
	}
}


void test_InsertionSort() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	InsertionSort(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
