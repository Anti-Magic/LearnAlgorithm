// Created by Buwenjie
// 计数排序
// 因为这里用std::vector<int>作为hash表保存元素出现的次数，所以数组元素必须都为正整数
#pragma once

#include <stdio.h>
#include <vector>

void CountingSortWork(std::vector<int>& data, int maxValue) {
	std::vector<int> count(maxValue + 1);
	std::vector<int> sorted(data.size());
	// 统计每个元素出现的次数
	for (int v : data) {
		count[v] += 1;
	}
	// 统计数值小于等于i的元素的数量
	for (int i = 1; i <= maxValue; i++) {
		count[i] += count[i - 1];
	}
	// 逆序遍历原数组
	// 如果有N个元素小于等于V，那么V最终就在数组的第N个位置，下标为N-1
	for (int i = data.size() - 1; i >= 0; i--) {
		int v = data[i];
		int lessOrEqu = count[v];
		sorted[lessOrEqu - 1] = v;
		// 把一个元素放置到合适的位置后，剩余的数量要减1
		count[v] -= 1;
	}
	// 把排好的结果拷贝回原数组
	data = std::move(sorted);
}

void CountingSort(std::vector<int>& data) {
	int maxValue = 0;
	for (int v : data) {
		maxValue = v > maxValue ? v : maxValue;
	}
	CountingSortWork(data, maxValue);
}


void test_CountingSort() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	CountingSort(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
