// Link-State-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "dikjstra.h"
#include "json.hpp"
#include <sstream>
using json = nlohmann::json;
using namespace std;

// Recall that in Link state routing all switches send out a broadcast of all links
// So we assume we know every node and its connection 
int jsonToInt(json in)
{
	stringstream str(in.dump());
	int num = 0;
	str >> num;
	return num;
}

int main()
{
	std::ifstream i("Net.json");
	json j;
	i >> j;
	NodeList Nodes = NodeList();

	cout << "Reading Network config...\n\n";

	// init router 
	for (auto& N : j["Nodes"]) 
	{
		// the same code as range for
		for (auto& n : N["Node"].items()) 
		{
			if (n.key() == "ID")
			{
				Node node(n.value());
				Nodes.Add(node);
				cout << "	Including Node " << node.ID << endl;
			}
		}
	}

	cout << "	Establishing connections" << endl;

	// establish connections
	for (auto& N : j["Nodes"]) 
	{
		// the same code as range for
		int ID;
		json Connections;
		bool CaughtID = false, CaughtConnections = false;
		for (auto& n : N["Node"].items()) 
		{
			if (n.key() == "ID")
			{
				cout << "		Caught ID" << endl;
				ID = n.value();
				CaughtID = true;
			}
			if (n.key() == "Connections") // how do I determine the ID? 
			{
				cout << "		Caught Connections" << endl;
				Connections = n;
				CaughtConnections = true;
			}
		}

		// Process the information
		if (CaughtID && CaughtConnections)
		{
			cout << "		Connection for node " << ID << endl;
			for (auto& Connection : Connections["Connections"].items())
			{
				json Conn = Connection.value();
				cout << "			Caught connection, ID is " << Conn["ID"] << ", and its weight " << Conn["Weight"] << endl;

				// Get ID
				int numID = jsonToInt(Conn["ID"]);

				// Get Weight
				int numWeight = jsonToInt(Conn["Weight"]);

				Nodes.GetNodeByID(ID)->AddConnection(Nodes.GetNodeByID(numID), numWeight);
			}
		}
	}

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
