// Created by Buwenjie
// 1、任意选择1个顶点为初始点，把这个顶点加入树中
// 2、遍历所有不在树中的顶点，选择1个与树的距离最近的顶点u，把u加入树中，并把u与树连接的边加入结果集
//    （顶点与树的距离，定义为顶点与树中每个顶点的距离的最小值）
// 3、重复第2步，直到所有顶点都加入到了树中
#pragma once

#include <vector>
#include <memory>

namespace Prim {

class Edge {
public:
	Edge() {
	}

	Edge(int uu, int vv, int ww)
	: u(uu)
	, v(vv)
	, w(ww) {
	}

	int u;
	int v;
	int w;
};

// nVertices: 顶点数
// edges: 所有边
// result: 选择的边
// return: 最小生成树总的权值之和
int Prim(int nVertices, std::vector<Edge>& edges, std::vector<Edge>& result) {
	// 使用邻接矩阵建图，没有直接联通的2个顶点，距离为无穷大，使用INF表示
	const int INF = 0x7fffffff;
	std::vector<std::vector<int>> adjacencyMatrix(nVertices, std::vector<int>(nVertices, INF));
	for (auto& edge : edges) {
		adjacencyMatrix[edge.u][edge.v] = edge.w;
		adjacencyMatrix[edge.v][edge.u] = edge.w;
	}
	// 保存不在树中的顶点与树的最短连线
	std::vector<Edge> minEdgeToTree(nVertices);
	// 保存顶点是否已加入树中
	std::vector<bool> vis(nVertices, false);
	// 选择一个任意点为起始点，此处选择0点。把起始点加入树中
	vis[0] = true;
	// 更新不在树中的顶点与树的连线
	for (int j = 1; j < nVertices; j++) {
		minEdgeToTree[j].u = j;
		minEdgeToTree[j].v = 0;
		minEdgeToTree[j].w = adjacencyMatrix[j][0];
	}
	int wSum = 0;
	// 每次循环把一个顶点加入树中，共循环nVertices-1次
	for (int i = 1; i < nVertices; i++) {
		// 遍历所有不在树中的顶点，选择1个与树的距离最近的顶点u
		int w = INF;
		int u = -1;
		for (int j = 1; j < nVertices; j++) {
			if (!vis[j] && minEdgeToTree[j].w < w) {
				w = minEdgeToTree[j].w;
				u = j;
			}
		}
		// 把u加入树中，把u与树的连线加入结果集
		vis[u] = true;
		wSum += w;
		result.push_back(minEdgeToTree[u]);
		// 由于u加入了树中，不在树中的顶点与树的距离可能会更新
		for (int j = 1; j < nVertices; j++) {
			if (!vis[j] && adjacencyMatrix[j][u] < minEdgeToTree[j].w) {
				minEdgeToTree[j].v = u;
				minEdgeToTree[j].w = adjacencyMatrix[j][u];
			}
		}
	}
	return wSum;
}

}

void test_Prim() {
	using Prim::Edge;
	std::vector<Edge> edges = {
		Edge('A' - 'A', 'B' - 'A', 7),
		Edge('A' - 'A', 'D' - 'A', 5),
		Edge('B' - 'A', 'C' - 'A', 8),
		Edge('B' - 'A', 'D' - 'A', 9),
		Edge('B' - 'A', 'E' - 'A', 7),
		Edge('C' - 'A', 'E' - 'A', 5),
		Edge('D' - 'A', 'E' - 'A', 15),
		Edge('D' - 'A', 'F' - 'A', 6),
		Edge('E' - 'A', 'F' - 'A', 8),
		Edge('E' - 'A', 'G' - 'A', 9),
		Edge('F' - 'A', 'G' - 'A', 11)
	};
	std::vector<Edge> result;
	int nVertices = 7;
	int wSum = Prim::Prim(nVertices, edges, result);
	printf("wSum: %d\n", wSum);
	for (int i = 0; i < result.size(); i++) {
		printf("%c --- %c, w = %d\n", (result[i].u + 'A') & 0xff, (result[i].v + 'A') & 0xff, result[i].w);
	}
}
