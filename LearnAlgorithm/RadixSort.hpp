// Created by Buwenjie
// 基数排序
// 先按个位数的大小对数组排序，然后在前一步的基础上，再按照十位数排序。依次到最高位
// 每一步必须使用稳定排序，因为要保持前一步的结果。这里使用计数排序
#pragma once

#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm> // std::max, std::log10

// 计数排序。base为进制，digit为获取某一位的数字
void RadixCountingSort(std::vector<int>& data, int base, std::function<int(int)> digit) {
	std::vector<int> count(base);
	std::vector<int> sorted(data.size());
	// 统计每个元素出现的次数
	for (int v : data) {
		count[digit(v)] += 1;
	}
	// 统计数值小于等于i的元素的数量
	for (int i = 1; i < base; i++) {
		count[i] += count[i - 1];
	}
	// 逆序遍历原数组
	// 如果有N个元素小于等于V，那么V最终就在数组的第N个位置，下标为N-1
	for (int i = data.size() - 1; i >= 0; i--) {
		int v = data[i];
		int lessOrEqu = count[digit(v)];
		sorted[lessOrEqu - 1] = v;
		// 把一个元素放置到合适的位置后，剩余的数量要减1
		count[digit(v)] -= 1;
	}
	// 把排好的结果拷贝回原数组
	data = std::move(sorted);
}

// 2进制版
void RadixSort2(std::vector<int>& data) {
	// 按照32位计算
	for (int i = 0; i < 32; i++) {
		RadixCountingSort(data, 2, [=](int x) {
			return (x >> i) & 1;
		});
	}
}

// 10进制版
void RadixSort10(std::vector<int>& data) {
	// 计算最大的数字的位数
	int maxDigitNum = 1;
	for (int v : data) {
		maxDigitNum = std::max(static_cast<int>(std::log10(v) + 1), maxDigitNum);
	}
	// 从低位开始，依次取出每一位数字排序
	for (int i = 1; i <= maxDigitNum; i++) {
		RadixCountingSort(data, 10, [=](int x) {
			return x % static_cast<int>(std::pow(10, i)) / static_cast<int>(std::pow(10, i-1));
		});
	}
}


void test_RadixSort() {
	//std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	std::vector<int> data = { 342, 58, 576, 1234, 356 };
	RadixSort2(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
