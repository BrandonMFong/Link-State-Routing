// Link-State-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Node.cpp"

int main()
{

	// Initiliaze nodes 
	Node Node1(1); // Node 1
	Node Node2(2); // Node 2
	Node Node3(3); // Node 3
	Node Node4(4); // Node 4
	Node Node5(5); // Node 5
	Node Node6(6); // Node 6
	Node Node7(7); // Node 7


	Node1.AddConnection(&Node2, 5);
	Node1.AddConnection(&Node3, 10);
	Node1.AddConnection(&Node4, 15);

	Table Node1Table[Node1.MAX];
	Node1.GetTable(Node1Table);

	cout << "Node " << Node1.ID << " is connected to:" << endl;
	for (int i = 0; i < Node1.GetCapacity(); i++)
	{
		cout << "	- Node " << Node1Table[i].NodeID << ", distance: " << Node1Table[i].Weight << endl;
	}
}
