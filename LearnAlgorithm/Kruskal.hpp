// Created by Buwenjie
#pragma once

#include <vector>
#include <algorithm>

namespace Kruskal {

class Edge {
public:
	Edge(int uu, int vv, int ww)
	: u(uu)
	, v(vv)
	, w(ww) {
	}

	int u;
	int v;
	int w;
};

int Kruskal(int nVertices, std::vector<Edge>& edges, std::vector<Edge>& result) {
	std::vector<int> group(nVertices);
	for (int i = 0; i < nVertices; i++) {
		group[i] = i;
	}

	auto findGroupID = [&group](int x) {
		int p = x;
		while (p != group[p]) {
			p = group[p];
		}
		int root = p;

		p = x;
		while (p != group[p]) {
			int p_old = p;
			p = group[p];
			group[p_old] = root;
		}

		return root;
	};

	std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
		return e1.w < e2.w;
	});

	int wSum = 0;
	for (auto& edge : edges) {
		int uGroup = findGroupID(edge.u);
		int vGroup = findGroupID(edge.v);
		if (uGroup != vGroup) {
			wSum += edge.w;
			result.push_back(edge);
			group[uGroup] = vGroup;
		}
	}
	return wSum;
}

}

void test_Kruskal() {
	using Kruskal::Edge;
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
	int wSum = Kruskal::Kruskal(nVertices, edges, result);
	printf("wSum: %d\n", wSum);
	for (int i = 0; i < result.size(); i++) {
		printf("%c --- %c, w = %d\n", (result[i].u + 'A') & 0xff, (result[i].v + 'A') & 0xff, result[i].w);
	}
}
