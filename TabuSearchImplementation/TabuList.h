#include "vector"

#pragma once
class TabuList
{
private:
	int tabuLenght;
public:
	TabuList();
	TabuList(int numberOfNodes, int numberOfColors, int tabuLenght);
	
	//set tabu move
	void tabuMove(int u, int v);

	void decrementTabu();

	~TabuList();

	std::vector<std::vector<int>> tabuMatrix;
};

