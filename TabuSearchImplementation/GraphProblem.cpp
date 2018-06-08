#include "stdafx.h"
#include "GraphProblem.h"
#include "algorithm"
#include "iostream"

GraphProblem::GraphProblem(int numberOfNodes)
{
	Adj = std::vector<std::vector<int>>(numberOfNodes);
}

GraphProblem::GraphProblem(char * filename)
{
	//read from file
}

void GraphProblem::addNode()
{
	Adj.push_back(std::vector<int>());
}

void GraphProblem::addEdge(int u, int v)
{
	Adj[u].push_back(v);
	Adj[v].push_back(u);

	std::sort(Adj[u].begin(), Adj[u].end());
	std::sort(Adj[v].begin(), Adj[v].end());
}


int GraphProblem::getNumberOfNodes() const
{
	return Adj.size();
}

void GraphProblem::printGraph()
{
	for (int i = 0; i < Adj.size(); i++)
	{
		std::cout << i << " -> ";
		for (int j = 0; j < Adj[i].size(); j++)
		{
			std::cout << Adj[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

GraphProblem::~GraphProblem()
{
}
