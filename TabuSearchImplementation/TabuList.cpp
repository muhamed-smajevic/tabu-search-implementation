#include "stdafx.h"
#include "TabuList.h"


TabuList::TabuList()
{
}

TabuList::TabuList(int numberOfNodes, int numberOfColors, int tabuLenght)
{
	tabuMatrix = std::vector<std::vector<int>>(numberOfNodes);

	for (int i = 0; i < numberOfNodes; i++)
	{
		tabuMatrix[i] = std::vector<int>(numberOfColors);
	}

	this->tabuLenght = tabuLenght;
}

void TabuList::tabuMove(int u, int c)
{
	//add move to matrix, forbid next tabuLenght moves from seting color c to node u
	tabuMatrix[u][c] += tabuLenght;
}

void TabuList::decrementTabu()
{
	for (int i = 0; i < tabuMatrix.size(); i++)
	{
		for (int j = 0; j < tabuMatrix[i].size(); j++)
		{
			tabuMatrix[i][j] -= tabuMatrix[i][j] <= 0 ? 0 : 1;
		}
	}
}


TabuList::~TabuList()
{
}
