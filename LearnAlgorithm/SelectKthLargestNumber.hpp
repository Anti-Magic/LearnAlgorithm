// Created by Buwenjie
// 数组中第K大的数（下标以0开始，应该说是第K+1大的）
// 2种做法

// 方法1：最坏时间是O(n)
// step1：按照每组5个数分组，分为ceil(n/5)组。每组使用插入排序，找到中位数（也就是下标第三个数）。
// step2：把每组的中位数组成一个新的数组，再取这个新数组的中位数x
// step3：利用快速排序的思路，使用x作为划分点，递归划分原数组。如果x的下标是K，则x就是结果。如果x的下标小于K，则递归划分左侧，否则右侧。

// 方法2：直接使用方法1的step3。期望时间是O(n)，最坏是O(n^2)

#pragma once

#include <stdio.h>
#include <vector>
#include <algorithm> // std::min std::swap

namespace SelectKthLargestNumber {

// 方法1
// 插入排序
void InsertionSort(std::vector<int>& data, int low, int high) {
	for (int i = low + 1; i <= high; i++) {
		// 当前要插入的值v
		int v = data[i];
		// 从位置i-1向前遍历，大于v的后移一个位置
		int j = i - 1;
		while (j >= low && data[j] > v) {
			data[j + 1] = data[j];
			j -= 1;
		}
		// v插入到空出的位置中
		data[j + 1] = v;
	}
}

// 跟快速排序一样，递归划分
int Partition(std::vector<int>& data, int low, int high, int k) {
	if (low >= high) {
		return data[low];
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
	if (i == k) {
		return v;
	}
	else if (i > k) {
		return Partition(data, low, i, k);
	}
	else {
		return Partition(data, i + 1, high, k);
	}
}

int SelectKthLargestNumber(std::vector<int>& data, int k) {
	// 划分为ceil(n/5)组
	int groupCount = static_cast<int>(std::ceil(data.size() / 5.0));
	// 每组插入排序，并把中位数保存到medians
	std::vector<int> medians(groupCount);
	for (int i = 0; i < groupCount; i++) {
		int low = i * 5;
		int high = std::min(static_cast<int>(data.size() - 1), i * 5 + 4);
		InsertionSort(data, low, high);
		medians[i] = data[(high - low) / 2];
	}
	// 找到medians数组的中位数med
	InsertionSort(medians, 0, groupCount - 1);
	int med = medians[groupCount / 2];
	// 把med放到下标为0的位置，因为Partition是用这个位置的数来划分的
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == med) {
			std::swap(data[i], data[0]);
			break;
		}
	}
	// 划分data数组寻找第K大的数
	return Partition(data, 0, data.size() - 1, k);
}

// 方法2
int RandomizedSelectKthLargestNumber(std::vector<int>& data, int k) {
	return Partition(data, 0, data.size() - 1, k);
}

}

void test_SelectKthLargestNumber() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	printf("%d\n", SelectKthLargestNumber::SelectKthLargestNumber(data, 0));
	printf("%d\n", SelectKthLargestNumber::RandomizedSelectKthLargestNumber(data, 5));
}
