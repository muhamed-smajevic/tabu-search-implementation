#include "vector"
#include "set"

#pragma once
class GraphProblem
{
public:
	GraphProblem(int numberOfNodes);
	GraphProblem(char *filename);

	//add new node to graph with no edges
	void addNode();
	
	//add edge to graph from node u to node v
	void addEdge(int u, int v);
	
	//adjacent matrix
	std::vector<std::vector<int>> Adj;

	//returns number of nodes
	int getNumberOfNodes() const;

	//print graph to screen
	void printGraph();

	~GraphProblem();
};

