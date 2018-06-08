#include "stdafx.h"
#include "TabuSearch.h"
#include <stdlib.h>
#include "iostream"

TabuSearch::TabuSearch(GraphProblem * graphProblem, TabuSearchConfiguration configuration)
{
	this->_graphProblem = graphProblem;
	this->_configuration = configuration;

	this->_bestSolution = Solution(graphProblem);
	this->_currentSolution = Solution(graphProblem);

	_tabuList = TabuList(graphProblem->Adj.size(), configuration.initialNumberOfColors, configuration.tabuLength);
	
	this->createInitialSolution();
}


Solution TabuSearch::getBestNeighbour(bool selectRandomColor)
{
	Solution bestSolution = _bestSolution;

	int bestCost = bestSolution.getFunctionValue();

	int u = -1;
	int selectedColor = -1;

	for (int i = 0; i < _graphProblem->getNumberOfNodes(); i++)
	{
		Solution newBestSolution = bestSolution;

		//choose color that is different than adjacent colors
		int newColor = newBestSolution.getFirstAvailableColor(i, _configuration.initialNumberOfColors -1, selectRandomColor);

		//skip non conflicting nodes
		if (newColor < 0)
			continue;

		//set new color to node
		newBestSolution.setColor(i, newColor, false);

		//calculate evaluation function
		int newCost = newBestSolution.getFunctionValue();
		//std::cout << "new cost: " << newCost << std::endl;


		//check if new value is better than old one and if move is not tabu
		if (newCost < bestCost && _tabuList.tabuMatrix[i][newColor] == 0) {
			u = i;
			selectedColor = newColor;

			std::cout << "new cost: " << newCost << ", old cost: " << bestCost << std::endl;

			bestCost = newCost;
			bestSolution = newBestSolution;

			std::cout << "seting tabu move, node: " << u << ", color: " << selectedColor << std::endl;
			//add move to tabu list

			_tabuList.decrementTabu();
			_tabuList.tabuMove(u, selectedColor);
			
		}
	}

	if (u != -1) {
		
	}

	return bestSolution;
}

void TabuSearch::createInitialSolution()
{
	//initialize empty solution
	_bestSolution = Solution(this->_graphProblem);

	
	//iterate through all nodes and assign random color c in 0,...,(k-1) interval
	for (int i = 0; i< _graphProblem->Adj.size(); i++)
	{
		int randColor = std::rand() % (_configuration.initialNumberOfColors - 1);
		_bestSolution.setColor(i, randColor, false);
	}

	//current solution is same as best solution in initialization
	_currentSolution = _bestSolution;
}

void TabuSearch::runTabuSearch()
{
	//calculate cost of initial solution
	int bestCost = _bestSolution.getFunctionValue();

	int numOfIterationsWithNoBetterCost = 0;
	//try to improve solution in next numberOfIterations steps
	for (int i = 0; i < _configuration.numberOfIterations; i++)
	{
		if (numOfIterationsWithNoBetterCost < 30) {
			//std::cout << "Min num of conflicts" << std::endl;

			//find bes neighbour solution 
			_currentSolution = this->getBestNeighbour(false);
		}
		else {
			//std::cout << "Random color" << std::endl;

			_currentSolution = this->getBestNeighbour(true);
		}
		
		//calculate cost of new solution
		int currentCost = _currentSolution.getFunctionValue();

		//if new cost is better take as new solution
		if (currentCost < bestCost)
		{
			std::cout << "(1) new best solution, curr cost:" << currentCost << ", old cost: " << bestCost << std::endl;

			_bestSolution = _currentSolution;
			bestCost = currentCost;

			numOfIterationsWithNoBetterCost --;
			//cost is defined as number of same color on edge
			//if number is zero all edge colors are different
			//if solution for given k is found terminate algorithm 
			if (currentCost == 0)
				return;
		}

		numOfIterationsWithNoBetterCost++;
	}

	//if solution is not found restart search with increased k
	this->runNewTabuSearch();
}

void TabuSearch::runNewTabuSearch()
{
	std::cout << std::endl;
	std::cout << "(2) NO SOLUTION FOUND FOR k=" << _configuration.initialNumberOfColors  << std::endl;
	
	//increase number of colors
	_configuration.initialNumberOfColors++;

	std::cout << "(2) RUNNING NEW SEARCH k=" << _configuration.initialNumberOfColors << std::endl;
	std::cout << std::endl;

	//reinstiate solutions
	this->_bestSolution = Solution(_graphProblem);
	this->_currentSolution = Solution(_graphProblem);

	//reinstatiate tabu list
	_tabuList = TabuList(_graphProblem->Adj.size(),_configuration.initialNumberOfColors, _configuration.tabuLength);

	//recreate initial solution
	this->createInitialSolution();

	//run tabu search
	this->runTabuSearch();
}

Solution TabuSearch::getSolution()
{
	return _bestSolution;
}

TabuSearch::~TabuSearch()
{
}
