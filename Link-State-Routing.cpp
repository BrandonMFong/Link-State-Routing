// Link-State-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Node.cpp"

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
	Node5.AddConnection(&Node6, 6);
	// Node 6
	Node6.AddConnection(&Node2, 8);
	Node6.AddConnection(&Node3, 2);
	Node6.AddConnection(&Node7, 5);
	// Node 7
	Node7.AddConnection(&Node4, 3);
	Node7.AddConnection(&Node6, 5);

	// Put in an array 
	Node Nodes[7] = { Node1,Node2,Node3,Node4,Node5,Node6,Node7 };

	NodeList Nlist = NodeList();
	Nlist.Add(&Node1);
	Nlist.Add(&Node2);
	Nlist.Add(&Node3);
	Nlist.Add(&Node4);
	Nlist.Add(&Node5);
	Nlist.Add(&Node6);
	Nlist.Add(&Node7);

	//// Print the network to user 
	//unsigned int size = sizeof(Nodes)/sizeof(Nodes[0]);
	//for (int k = 0; k < size; k++)
	//{
	//	Table NodeTable[Nodes[k].MAX];
	//	Nodes[k].GetTable(NodeTable);

	//	cout << "Node " << Nodes[k].ID << " is connected to:" << endl;
	//	for (int i = 0; i < Nodes[k].GetNumberOfConnections(); i++)
	//	{
	//		cout << "	- Node " << NodeTable[i].NodeID << ", distance: " << NodeTable[i].Weight << endl;
	//	}
	//}
	unsigned int size = Nlist.GetSize();

	// TODO index and print info
	for (int k = 0; k < size; k++)
	{
		Table NodeTable[Nodes[k].MAX];
		Nodes[k].GetTable(NodeTable);

		cout << "Node " << Nodes[k].ID << " is connected to:" << endl;
		for (int i = 0; i < Nodes[k].GetNumberOfConnections(); i++)
		{
			cout << "	- Node " << NodeTable[i].NodeID << ", distance: " << NodeTable[i].Weight << endl;
		}
	}

	// TODO: have the user input the source and destination and figure out the shortest path 
	int Source, Destination;
	cout << "\n\nNow let's figure out the shortest path to whatever you want" << endl;
	cout << "Input source Node ID from the following: ";
	for (int i = 0; i < size; i++)
	{
		cout << " " << Nodes[i].ID << " ";
	}
	cout << "\nSo: ";
	cin >> Source;
	cout << "Now Destination!" << endl;
	cout << "So: ";
	cin >> Destination;

	cout << "We want to find the shortest path from node " << Source << " to " << Destination << endl;

	// TODO implement algorithm 
	// For the algorithm let it assume that it has the list of nodes and their connection (which is already programmed in the node class)
	// We are assuming the Source and destination follow the Nodes indexing, ie, Source = 1 is Nodes[0]
}
