#include "vector"
#include "GraphProblem.h"
#include "list"

#pragma once
class Solution
{
private:
	GraphProblem * _graphProblem;

	std::vector<std::list<int>> _conflictNodes;

	void setConflictNodes(int u);
	void cleanConflictNodes(int u);
public:
	Solution();
	Solution(GraphProblem *graphProblem);

	//return value of evaluation function which is number of edges that have same color
	int getFunctionValue();

	void printSolution();
	void printSolution2();
	void printConflicts();

	void saveResultToFile(const char* problemName);

	//assign color to node u
	void setColor(int u, int color, bool skipCheckingConflicts);
	
	int getFirstAvailableColor(int u, int k, bool takeRandom);
	
	//vector representing color to node, index of vector is taken as node and value is color
	std::vector<int> Colors;


	//void changeColor(int u, int color);
	//int getNumOfColors() const;
	//void swapColors(int u, int v);


	~Solution();
};

