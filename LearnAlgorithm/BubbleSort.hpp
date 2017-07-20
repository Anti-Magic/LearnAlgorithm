// Created by Buwenjie
// 冒泡排序
#pragma once

#include <stdio.h>
#include <vector>

void BubbleSort(std::vector<int>& data) {
	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = 0; j < data.size() - 1 - i; j++) {
			if (data[j] > data[j + 1]) {
				std::swap(data[j], data[j + 1]);
			}
		}
	}
}


void test_BubbleSort() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	BubbleSort(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
