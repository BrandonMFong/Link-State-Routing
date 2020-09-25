// Link-State-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Node.cpp"

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

	// Add connections 
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

	Node Nodes[7] = { Node1,Node2,Node3,Node4,Node5,Node6,Node7 };

	unsigned int size = sizeof(Nodes)/sizeof(Nodes[0]);
	for (int k = 0; k < size; k++)
	{
		Table NodeTable[Nodes[k].MAX];
		Nodes[k].GetTable(NodeTable);

		cout << "Node " << Nodes[k].ID << " is connected to:" << endl;
		for (int i = 0; i < Nodes[k].GetCapacity(); i++)
		{
			cout << "	- Node " << NodeTable[i].NodeID << ", distance: " << NodeTable[i].Weight << endl;
		}
	}
}
