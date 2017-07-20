// Created by Buwenjie
// 桶排序
// 有若干个桶，把元素均匀的放在每个桶中，每个桶内的元素分别排序，然后所有桶合并
#pragma once

#include <stdio.h>
#include <vector>
#include <algorithm> // std::min, std::max

// bucketNum为桶的数量，大于0的任意值都可以
void BucketSortWork(std::vector<int>& data, int bucketNum) {
	std::vector<std::vector<int>> buckets(bucketNum);
	int min = data[0];
	int max = data[0];
	for (int v : data) {
		min = std::min(min, v);
		max = std::max(max, v);
	}
	// 每个桶的步长。例如把[0,8]放在3个桶中，每个桶分别放[0,2], [3,5], [6,8]
	double step = 1.0 * (max - min + 1) / bucketNum;
	for (int v : data) {
		int idx = static_cast<int>((v - min) / step);
		auto& bucket = buckets[idx];
		bucket.push_back(v);
		// 插入排序
		int i = bucket.size() - 2;
		while (i >= 0 && bucket[i] > v) {
			bucket[i + 1] = bucket[i];
			i -= 1;
		}
		bucket[i + 1] = v;
	}
	// 按顺序放回原数组
	int i = 0;
	for (auto& bucket : buckets) {
		for (int v : bucket) {
			data[i++] = v;
		}
	}
}

void BucketSort(std::vector<int>& data) {
	BucketSortWork(data, 5);
}


void test_BucketSort() {
	std::vector<int> data = { 3, 1, 5, 7, 6, 2, 9, 4, 8 };
	BucketSort(data);
	for (int v : data) {
		printf("%d ", v);
	}
	printf("\n");
}
