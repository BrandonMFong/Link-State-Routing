// Link-State-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>      // std::ifstream
#include "json.hpp" // Use when it is ready to be parameterized

// Priority is to establish the algorithm then do the configuration 

using namespace std;
using json = nlohmann::json;
using ifstream = std::ifstream;

//#define MAXCONNECTIONS 10;

struct Table
{
	int NodeID, Distance;
};

class Node
{
	public:
		int ID;
		static const int MAX = 10;

		// Constructors
		Node() 
		{
			ID = 0;
			InitConnect();
		}; 

		Node(int val)
		{
			ID = val;
			InitConnect();
		};

		int GetCapacity() { return Capacity; }

		void AddConnection(Node * n, int distance)
		{
			if (Capacity != MAX)
			{
				Connect[Capacity] = new Connection(n, distance);
				Capacity++;
			}
		};

		void GetTable(struct Table* Table)
		{

			for (int i = 0; i < Capacity; i++)
			{
				Table[i].NodeID = Connect[i]->GetID();
				Table[i].Distance = Connect[i]->GetDistance();
			}
		}

		// This is a static approach
		int GetNumberOfConnections() { return Capacity; }

	private:
		int Capacity = 0;
		class Connection
		{
			public:
				Connection(Node* n, int distance) { Neighbor = n; Distance = distance; }
				Connection() { Neighbor = 0; Distance = 0; }

				int GetDistance() { return Distance; }

				int GetID() { return Neighbor->ID; }
			private:
				Node * Neighbor;
				int Distance;
		};

		Connection * Connect[MAX];

		void InitConnect() { for (int i = 0; i < MAX; i++) { Connect[i] = new Connection(); } }
};

int main()
{
	// Test the first two nodes 
	Node Node1(1); // Node 1
	Node Node2(2); // Node 2
	Node Node3(3); // Node 3

	Node1.AddConnection(&Node2, 5);
	Node1.AddConnection(&Node3, 10);

	struct Table Node1Table[Node1.MAX];
	Node1.GetTable(Node1Table);

	cout << "Node " << Node1.ID << " is connected to:" << endl;
	for (int i = 0; i < Node1.GetCapacity(); i++)
	{
		cout << "	- Node " << Node1Table[i].NodeID << ", distance: " << Node1Table[i].Distance << endl;
	}
}
