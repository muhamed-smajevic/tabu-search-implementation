#include "stdafx.h"
#include "GraphLoader.h"
#include "iostream"
#include "fstream"
#include "string"

GraphLoader::GraphLoader()
{
}

GraphProblem GraphLoader::loadGraph(const char * filename)
{
	//load graph from file
	std::ifstream f(filename);

	std::string line;

	GraphProblem graph(0);

	char a = 'a';
	int nodes, edges;
	int u, v;
	
	while (!f.eof()) {

		f >> a;
		if (a == 'c')
			getline(f, line);
		
		if (a == 'p')
		{
			f >> line >> nodes >> edges;
			graph = GraphProblem(nodes);
		}
	   
		if (a == 'e') {
			f >> u >> v;

			graph.addEdge(u-1, v-1);
		}
	}

	return graph;
}

GraphLoader::~GraphLoader()
{
}
