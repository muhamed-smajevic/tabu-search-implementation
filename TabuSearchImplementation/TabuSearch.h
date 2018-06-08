#include "GraphProblem.h"
#include "TabuSearchConfiguration.h"
#include "Solution.h"
#include "TabuList.h"

#pragma once
class TabuSearch
{
private:
	GraphProblem *_graphProblem;

	Solution _bestSolution;
	Solution _currentSolution;

	TabuList _tabuList;
	TabuSearchConfiguration _configuration;


	Solution getBestNeighbour(bool selectRandomColor);

	void createInitialSolution();

public:
	TabuSearch(GraphProblem *graphProblem,
			   TabuSearchConfiguration configuration);
	
	void runTabuSearch();
	void runNewTabuSearch();

	Solution getSolution();
	~TabuSearch();
};

