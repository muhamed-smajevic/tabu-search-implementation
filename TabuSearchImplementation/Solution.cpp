#include "stdafx.h"
#include "Solution.h"
#include "iostream"
#include <algorithm>
#include "fstream"


Solution::Solution()
{
	Colors = std::vector<int>(0, 0);
	_conflictNodes = std::vector<std::list<int>>(0);
}

Solution::Solution(GraphProblem * graphProblem)
{
	_graphProblem = graphProblem;

	Colors = std::vector<int>(graphProblem->getNumberOfNodes(), 0);
	_conflictNodes = std::vector<std::list<int>>(graphProblem->getNumberOfNodes());

}

int Solution::getFunctionValue()
{
	//count number of edges that are in conflict
	int numOfConflicts = 0;
	for (int i = 0; i < Colors.size(); i++)
	{
		numOfConflicts += _conflictNodes[i].size();
	}
	return numOfConflicts;
}

void Solution::printSolution()
{
	std::cout << "num of conflicts: " << this->getFunctionValue() << std::endl;
	for (int i = 0; i < this->Colors.size(); i++)
	{
		std::cout << "C(" << i << "):" << this->Colors[i] << " ";
	}

	std::cout << std::endl;
}

void Solution::printSolution2()
{
	for (int i = 0; i < _graphProblem->Adj.size(); i++)
	{
		std::cout << Colors[i] << " -> ";
		for (int j = 0; j < _graphProblem->Adj[i].size(); j++)
		{
			std::cout << Colors[_graphProblem->Adj[i][j]] << ", ";
		}
		std::cout << std::endl;
	}
}

void Solution::printConflicts()
{
	/*for (int i = 0; i <_conflictNodes.size(); i++)
	{
		std::cout << i << " -> ";
		for (int j = 0; j < _conflictNodes[i].size(); j++)
		{
			std::cout << _conflictNodes[i][j] << ", ";
		}
		std::cout << std::endl;
	}*/
}


void Solution::saveResultToFile(const char* problemName)
{
	std::ofstream o;

	std::string filepath;
	filepath = "results/";
	filepath += problemName;
	filepath += ".txt";

	o.open(filepath);

	o << "Order of colors" << std::endl;

	for (int i = 0; i < _graphProblem->Adj.size(); i++)
	{
		o << Colors[i] << " -> ";
		for (int j = 0; j < _graphProblem->Adj[i].size(); j++)
		{
			o << Colors[_graphProblem->Adj[i][j]] << ", ";
		}
		o << std::endl;
	}

	o << "num of conflicts: " << this->getFunctionValue() << std::endl;
	for (int i = 0; i < this->Colors.size(); i++)
	{
		o << "C(" << i << "):" << this->Colors[i] << " ";
	}

	o << std::endl;
}

//int Solution::getNumOfColors() const
//{
//	return _numOfColors;
//}

void Solution::setColor(int u, int color, bool skipCheckingConflicts = false)
{
	//TODO: check boundaries of array
	Colors[u] = color;


	if (skipCheckingConflicts)
		return;

	//checking conflicting edges for observed node
	this->setConflictNodes(u);
	this->cleanConflictNodes(u);
}



//void Solution::swapColors(int u, int v)
//{
//	int tmp = Colors[u];
//	Colors[u] = Colors[v];
//	Colors[v] = tmp;
//
//	this->setConflictNodes(u);
//	this->setConflictNodes(v);
//
//	this->cleanConflictNodes(u);
//	this->cleanConflictNodes(v);
//}

void Solution::setConflictNodes(int u)
{
	for (int i = 0; i < _graphProblem->Adj[u].size(); i++)
	{
		int edgeColor = Colors[_graphProblem->Adj[u][i]];

		if (Colors[u] == edgeColor) //conflict found
		{
			int v = _graphProblem->Adj[u][i];

			_conflictNodes[u].push_back(v);
			_conflictNodes[v].push_back(u);
		}
	}
}

void Solution::cleanConflictNodes(int u)
{
	std::list<std::list<int>::iterator> conflictsToRemove;

	for (auto it = _conflictNodes[u].begin(); it != _conflictNodes[u].end(); ++it) {

		if (Colors[*it] != Colors[u]) {
			conflictsToRemove.push_back(it);
		}
	}

	for (auto it = conflictsToRemove.begin(); it != conflictsToRemove.end(); ++it) {
		_conflictNodes[u].erase(*it);
	}
}

//void Solution::changeColor(int u, int color)
//{
//	Colors[u] = color;
//
//	//this->setConflictNodes(u);
//
//	//this->cleanConflictNodes(u);
//}


//THIS NEEDS TO BE IMPROVED
int Solution::getFirstAvailableColor(int u, int k, bool takeRandom)
{
	//if there is no conflict for node skip it
	
	//if (_conflictNodes[u].size() == 0)
	//	return -1;

	if (takeRandom) {
		int index = rand() % k;
		return index;
	}

	//choose new color that is different from adjacent nodes
	int smallestColor = 0;
	std::set<int> adjColors;

	std::vector<int> numOfConflictingColors(k + 1, 0);

	//insert colors in set and then take first smallest color that is not in the set
	for (int i = 0; i < _graphProblem->Adj[u].size(); i++)
	{
		int clr = Colors[_graphProblem->Adj[u][i]];
		//adjColors.emplace(clr);

		numOfConflictingColors[clr]++;
	}

	int min = numOfConflictingColors[0];
	int index = 0;
	for (int i = 0; i < numOfConflictingColors.size(); i++)
	{
		if (numOfConflictingColors[i] < min) {
			min = numOfConflictingColors[i];
			index = i;
		}
	}
	return index;


	//for (auto it = adjColors.begin(); it != adjColors.end(); ++it)
	//{
	//	if (smallestColor != *it)
	//	{
	//		return smallestColor;
	//	}

	//	smallestColor++;

	//	//impossible to find new color, choose random color
	//	if (smallestColor > k) {
	//		int index = rand() % k;
	//		return index;
	//	}

	//}

	//return smallestColor;
}

Solution::~Solution()
{
}
