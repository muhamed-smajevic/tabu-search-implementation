// TabuSearchImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "TabuSearch.h"
#include "GraphLoader.h"

int main()
{
	//this is to show how to load problem from file
	GraphProblem g = GraphLoader().loadGraph("problems/le450_5b.col");


	//this is to show how to create graph
	//GraphProblem graphProblem(10);
	//graphProblem.addEdge(0, 1); graphProblem.addEdge(0, 3); graphProblem.addEdge(0, 8);
	//graphProblem.addEdge(1, 2); graphProblem.addEdge(1, 4); 
	//graphProblem.addEdge(2, 5); graphProblem.addEdge(2, 9);
	//graphProblem.addEdge(3, 5); graphProblem.addEdge(3, 7); 
	//graphProblem.addEdge(4, 6); graphProblem.addEdge(4, 7); 
	//graphProblem.addEdge(5, 6); 
	//graphProblem.addEdge(6, 8); 
	//graphProblem.addEdge(7, 9); 
	//graphProblem.addEdge(8, 9);

	//this is to configure tabu search parameters
	TabuSearchConfiguration conf;
	conf.numberOfIterations = 100;
	conf.initialNumberOfColors = 5; 
	conf.tabuLength = 7;


	TabuSearch tabuSearch = TabuSearch(&g, conf);
	tabuSearch.runTabuSearch();

	std::cout << "\nGRAPh: " << std::endl;
	g.printGraph();

	std::cout << "\nFINAL SOLUTION COLORS: " << std::endl;
	tabuSearch.getSolution().printSolution2();

	tabuSearch.getSolution().printSolution();

	//this is to show how to save result to file
	tabuSearch.getSolution().saveResultToFile("le450_5b");

	std::cout << "\nCOMPLETED" << std::endl;

	int a;
	std::cin >> a;
    return 0;
}

