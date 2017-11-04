// Created by Buwenjie
// 最短路 Dijkstra算法
// 跟最小生成树的Prim算法类似，是求单源最短路的常用算法
// 从图中选择若干条边，最终构成一棵以起点为根节点的树
// 1、把起点加入树中
// 2、遍历所有不在树中的顶点，选择1个与树的距离最近的顶点u，把u加入树中，保存u的前驱顶点
//    （顶点与树的距离，定义为顶点与树中每个顶点的距离的最小值）
// 3、u加入树中后，从起始点经过u点到达其他顶点的距离可能更近，如果更近则更新距离与前驱
// 4、重复第2，3步，直到所有顶点都加入到了树中
#pragma once

#include <vector>
#include <memory>

namespace Dijkstra {

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
// distances: 最短路径的距离
// paths: 最短路径
void Dijkstra(int nVertices, std::vector<Edge>& edges, int v0, 
	std::vector<int>& distances, std::vector<std::vector<int>>& paths) {
	distances.resize(nVertices);
	paths.resize(nVertices);
	// 使用邻接矩阵建图，没有直接联通的2个顶点，距离为无穷大，使用INF表示
	const int INF = 0x7fffffff;
	std::vector<std::vector<int>> adjacencyMatrix(nVertices, std::vector<int>(nVertices, INF));
	for (auto& edge : edges) {
		adjacencyMatrix[edge.u][edge.v] = edge.w;
		adjacencyMatrix[edge.v][edge.u] = edge.w;
	}
	for (int i = 0; i < nVertices; i++) {
		adjacencyMatrix[i][i] = 0;
	}
	// 保存顶点是否已加入树中
	std::vector<bool> vis(nVertices, false);
	std::vector<int> prev(nVertices, -1);
	vis[v0] = true;
	for (int u = 0; u < nVertices; u++) {
		distances[u] = adjacencyMatrix[u][v0];
		if (u != v0 && distances[u] < INF) {
			prev[u] = v0;
		}
		else {
			prev[u] = -1;
		}
	}
	for (int i = 1; i < nVertices; i++) {
		int w = INF;
		int u = -1;
		for (int j = 0; j < distances.size(); j++) {
			if (!vis[j] && distances[j] < w) {
				w = distances[j];
				u = j;
			}
		}
		if (u >= 0) {
			vis[u] = true;
			for (int j = 0; j < distances.size(); j++) {
				if (!vis[j] && adjacencyMatrix[u][j] < INF && distances[u] + adjacencyMatrix[u][j] < distances[j]) {
					distances[j] = distances[u] + adjacencyMatrix[u][j];
					prev[j] = u;
				}
			}
		}
	}
	for (int i = 0; i < nVertices; i++) {
		if (distances[i] < INF) {
			int v = i;
			while (v != -1) {
				paths[i].push_back(v);
				v = prev[v];
			}
			std::reverse(paths[i].begin(), paths[i].end());
		}
	}
}

}

void test_Dijkstra() {
	using Dijkstra::Edge;
	std::vector<Edge> edges = {
		Edge(0, 1, 7),
		Edge(0, 2, 9),
		Edge(0, 5, 14),
		Edge(1, 2, 10),
		Edge(1, 3, 15),
		Edge(2, 3, 11),
		Edge(2, 5, 2),
		Edge(3, 4, 6),
		Edge(4, 5, 9)
	};
	std::vector<int> distances;
	std::vector<std::vector<int>> paths;
	int nVertices = 7;
	int v0 = 0;
	Dijkstra::Dijkstra(nVertices, edges, v0, distances, paths);
	for (int i = 0; i < nVertices; i++) {
		printf("%d -> %d dist: %d\n", v0 + 1, i + 1, distances[i]);
		printf("path: ");
		if (paths[i].size() > 0) {
			printf("%d", paths[i][0] + 1);
			for (int j = 1; j < paths[i].size(); j++) {
				printf(" -> %d", paths[i][j] + 1);
			}
		}
		printf("\n\n");
	}
}
