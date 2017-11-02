// Created by Buwenjie
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

int Prim2(int nVertices, std::vector<Edge>& edges, std::vector<Edge>& result) {
	std::vector<std::vector<int>> adjacencyMatrix(nVertices, std::vector<int>(nVertices, -1));
	for (auto& edge : edges) {
		adjacencyMatrix[edge.u][edge.v] = edge.w;
		adjacencyMatrix[edge.v][edge.u] = edge.w;
	}
	std::vector<int> vertSet;
	std::vector<bool> isVertInSet(nVertices, false);

	int wSum = 0;

	vertSet.push_back(0);
	isVertInSet[0] = true;
	while (vertSet.size() < nVertices) {
		int v = -1;
		int w = 0x7fffffff;
		for (int u : vertSet) {
			for (int j = 0; j < nVertices; j++) {
				if (adjacencyMatrix[u][j] >= 0 && adjacencyMatrix[u][j] < w && !isVertInSet[j]) {
					v = j;
					w = adjacencyMatrix[u][j];
				}
			}
		}
		vertSet.push_back(v);
		isVertInSet[v] = true;
		wSum += w;
	}
	return wSum;
}

int Prim(int nVertices, std::vector<Edge>& edges, std::vector<Edge>& result) {
	const int inf = 0x7fffffff;
	std::vector<std::vector<int>> adjacencyMatrix(nVertices, std::vector<int>(nVertices, inf));
	for (auto& edge : edges) {
		adjacencyMatrix[edge.u][edge.v] = edge.w;
		adjacencyMatrix[edge.v][edge.u] = edge.w;
	}
	std::vector<Edge> ws(nVertices);
	std::vector<bool> vis(nVertices, false);
	vis[0] = true;
	for (int u = 1; u < nVertices; u++) {
		ws[u].u = u;
		ws[u].v = 0;
		ws[u].w = adjacencyMatrix[u][0];
	}
	int wSum = 0;
	for (int i = 1; i < nVertices; i++) {
		int w = inf;
		int u = -1;
		for (int j = 1; j < ws.size(); j++) {
			if (!vis[j] && ws[j].w < w) {
				w = ws[j].w;
				u = j;
			}
		}
		vis[u] = true;
		wSum += w;
		result.push_back(ws[u]);
		for (int j = 1; j < ws.size(); j++) {
			if (!vis[j] && adjacencyMatrix[j][u] < ws[j].w) {
				ws[j].v = j;
				ws[j].w = adjacencyMatrix[j][u];
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
