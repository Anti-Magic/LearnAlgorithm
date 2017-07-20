// Created by Buwenjie
// 连续子数组最大的和。2种实现方法
#pragma once

#include <stdio.h>
#include <vector>
#include <algorithm> // std::max

// 动态规划 O(n)
int MaxSubArray(std::vector<int>& arr) {
	int sum = arr[0];
	int max = sum > 0 ? sum : 0;
	for (int i = 1; i < arr.size(); i++) {
		// sum保存的是到i-1为止，最大的和
		// 很明显sum[i] = max(arr[i], arr[i] + sum[i-1])
		sum = sum > 0 ? sum + arr[i] : arr[i];
		max = sum > max ? sum : max;
	}
	return max;
}

/* 
 * 算法导论上的分治法 O(nlogn)
 * 把整个数组分成左右2段，最大的和可能在左边一段、或右边一段、或跨越2段
 */
// 计算跨越2段的最大和
int FindMaxCrossSubArray(std::vector<int>& arr, int low, int high) {
	int mid = low + (high - low) / 2;
	// [n1, mid]最大和
	int sum = 0;
	int max_leftOfMid = 0;
	for (int i = mid; i >= 0; i--) {
		sum += arr[i];
		if (sum > max_leftOfMid) {
			max_leftOfMid = sum;
		}
	}
	// [mid+1, n2]最大和
	sum = 0;
	int max_rightOfMid = 0;
	for (int i = mid + 1; i <= high; i++) {
		sum += arr[i];
		if (sum > max_rightOfMid) {
			max_rightOfMid = sum;
		}
	}
	return max_leftOfMid + max_rightOfMid;
}
// 递归分成2段，分到只剩一个元素的时候，最大和就是这个元素或0
int MaxSubArrayWork(std::vector<int>& arr, int low, int high) {
	if (high == low) {
		return arr[low] > 0 ? arr[low] : 0;
	}
	int mid = low + (high - low) / 2;
	int max_left = MaxSubArrayWork(arr, low, mid);
	int max_right = MaxSubArrayWork(arr, mid + 1, high);
	int max_cross = FindMaxCrossSubArray(arr, low, high);
	return std::max(std::max(max_left, max_right), max_cross);
}
int MaxSubArray2(std::vector<int>& arr) {
	return MaxSubArrayWork(arr, 0, arr.size() - 1);
}


void test_MaxSubArray() {
	std::vector<int> arr = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	printf("%d\n", MaxSubArray(arr));
	printf("%d\n", MaxSubArray2(arr));
}
