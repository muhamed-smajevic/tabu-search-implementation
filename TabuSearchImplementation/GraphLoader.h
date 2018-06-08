#include "GraphProblem.h"
#include "Solution.h"

#pragma once
class GraphLoader
{
public:
	GraphLoader();

	//load graph from file
    GraphProblem loadGraph(const char *filename);
    
	~GraphLoader();
};

