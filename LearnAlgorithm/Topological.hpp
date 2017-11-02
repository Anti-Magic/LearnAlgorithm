// Created by Buwenjie
// 拓扑排序
// 1.从 DAG 图中选择一个 没有前驱（即入度为0）的顶点并输出。
// 2.从图中删除该顶点和所有以它为起点的有向边。
// 3.重复 1 和 2 直到当前的 DAG 图为空或当前图中不存在无前驱的顶点为止。后一种情况说明有向图中必然存在环。
#pragma once

#include <stdio.h>
#include <vector>
#include <algorithm> // std::swap
#include <forward_list>

class TopoNode {
public:
	int mValue;
	int mIndegree;
};

class AdjacencyTable {
public:
	AdjacencyTable(const std::vector<int>& values)
	: mSize(values.size())
	, mNodes(mSize)
	, mAdj(mSize) {
		for (int i = 0; i < values.size(); i++) {
			mNodes[i].mValue = values[i];
			mNodes[i].mIndegree = 0;
		}
	}

	inline size_t size() {
		return mSize;
	}

	void AddEdge(int idx1, int idx2) {
		mAdj[idx1].push_front(&mNodes[idx2]);
		mNodes[idx2].mIndegree += 1;
	}

	size_t mSize;
	std::vector<TopoNode> mNodes;
	std::vector<std::forward_list<TopoNode*>> mAdj;
};

void TopologicalSort(AdjacencyTable& table, std::vector<int>& result) {
	std::vector<bool> vis(table.size(), false);
	for (int i = 0; i < table.size(); i++) {
		std::forward_list<TopoNode*>* successor = nullptr;
		for (int j = 0; j < table.size(); j++) {
			if (table.mNodes[j].mIndegree == 0 && !vis[j]) {
				successor = &table.mAdj[j];
				vis[j] = true;
				result.push_back(table.mNodes[j].mValue);
				break;
			}
		}
		for (auto node : *successor) {
			node->mIndegree -= 1;
		}
	}
}

void test_Topological() {
	std::vector<int> data = { 1, 2, 3, 4, 5 };
	AdjacencyTable table(data);
	table.AddEdge(0, 1);
	table.AddEdge(0, 3);
	table.AddEdge(1, 2);
	table.AddEdge(1, 3);
	table.AddEdge(3, 2);
	table.AddEdge(3, 4);
	table.AddEdge(2, 4);

	std::vector<int> result;
	TopologicalSort(table, result);

	for (int v : result) {
		printf("%d ", v);
	}
	printf("\n");
}
