// Created by Buwenjie
// 最小生成树 Kruskal算法
// 1、对所有边升序排序
// 2、遍历所有边，如果这条边两端连接的2个顶点没有联通，则选择这条边
//   （如何判断2个顶点是否联通，这里的代码使用的并查集）
// 3、重复第2步，直到选择了(nVertices-1)条边为止
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

// nVertices: 顶点数
// edges: 所有边
// result: 选择的边
// return: 最小生成树总的权值之和
int Kruskal(int nVertices, std::vector<Edge>& edges, std::vector<Edge>& result) {
	// 并查集，gruop[x]表示顶点x所属的组号
	std::vector<int> group(nVertices);
	for (int i = 0; i < nVertices; i++) {
		group[i] = i;
	}
	// 获取x根节点的组号
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

	// 对所有边按权值升序排序
	std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
		return e1.w < e2.w;
	});

	int wSum = 0;
	for (auto& edge : edges) {
		// 如果u和v这2个顶点没有联通，则选择这条边
		int uGroup = findGroupID(edge.u);
		int vGroup = findGroupID(edge.v);
		if (uGroup != vGroup) {
			wSum += edge.w;
			result.push_back(edge);
			group[uGroup] = vGroup;
			// 如果已经选择了nVertices-1条边，则算法结束
			if (result.size() >= nVertices - 1) {
				break;
			}
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
