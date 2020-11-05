// Link-State-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "dijkstra.h"
#include "config.h"
#include "Node.h"
#include <sstream>
using namespace std;

// Recall that in Link state routing all switches send out a broadcast of all links
// So we assume we know every node and its connection 

int main()
{
	NodeList Nodes = JsonToNodeList("config\\NetTwo.json");

	cout << endl;
	unsigned int size = Nodes.GetSize();

	for (int k = 0; k < size; k++)
	{
		Table* NodeTable = new Table[MAX];
		Nodes.GetByIndex(k).GetTable(NodeTable);

		cout << "Node " << Nodes.GetByIndex(k).ID << " is connected to:" << endl;
		for (int i = 0; i < Nodes.GetByIndex(k).GetNumberOfConnections(); i++)
		{
			cout << "	- Node " << NodeTable[i].NodeID << ", distance: " << NodeTable[i].Weight << endl;
		}
	}

	// Prompt user
	int Source, Destination; // These values will hold Node IDs
	cout << "\n\nNow let's figure out the shortest path to whatever you want" << endl;
	cout << "Input source Node ID from the following: " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "Node " << Nodes.GetByIndex(i).ID << endl;
	}
	cout << "\nSo: ";
	cin >> Source;
	cout << "Now Destination!" << endl;
	cout << "So: ";
	cin >> Destination;

	cout << "We want to find the shortest path from node " << Source << " to " << Destination << endl;

	NodeList NodePath = Dijkstra(Nodes, Source, Destination);

	cout << "\nPath from Node " << Source << " to " << Destination << " is: " << endl;
	NodePath.PrintPath(); 
}
