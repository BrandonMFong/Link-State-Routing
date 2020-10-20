// Link-State-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "dikjstra.h"


// Recall that in Link state routing all switches send out a broadcast of all links
// So we assume we know every node and its connection 

int main()
{
	// Following figure 18.9 from text 
	// Ref res/LinkGraph.png
	// Initiliaze nodes 
	Node Node1(1); // Node 1
	Node Node2(2); // Node 2
	Node Node3(3); // Node 3
	Node Node4(4); // Node 4
	Node Node5(5); // Node 5
	Node Node6(6); // Node 6
	Node Node7(7); // Node 7

	// Set connections 
	// Node 1
	Node1.AddConnection(&Node5, 9);
	// Node 2
	Node2.AddConnection(&Node3, 3);
	Node2.AddConnection(&Node5, 6);
	Node2.AddConnection(&Node6, 8);
	// Node 3 
	Node3.AddConnection(&Node2, 3);
	Node3.AddConnection(&Node4, 11);
	Node3.AddConnection(&Node6, 2);
	// Node 4
	Node4.AddConnection(&Node3, 11);
	Node4.AddConnection(&Node7, 3);
	// Node 5 
	Node5.AddConnection(&Node1, 9);
	Node5.AddConnection(&Node2, 6);
	// Node 6
	Node6.AddConnection(&Node2, 8);
	Node6.AddConnection(&Node3, 2);
	Node6.AddConnection(&Node7, 5);
	// Node 7
	Node7.AddConnection(&Node4, 3);
	Node7.AddConnection(&Node6, 5);

	// Organize in array 
	NodeList Nodes = NodeList();
	Nodes.Add(Node1);
	Nodes.Add(Node2);
	Nodes.Add(Node3);
	Nodes.Add(Node4);
	Nodes.Add(Node5);
	Nodes.Add(Node6);
	Nodes.Add(Node7);

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

	Dijkstra(Nodes, Source, Destination);

}
