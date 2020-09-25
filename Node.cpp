

#include <iostream>
#include <fstream>      // std::ifstream
#include "json.hpp" // Use when it is ready to be parameterized

// Priority is to establish the algorithm then do the configuration 

using namespace std;
using json = nlohmann::json;
using ifstream = std::ifstream;

//#define MAXCONNECTIONS 10;

typedef struct Table
{
	int NodeID, Weight;
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
			InitConnections();
		};

		Node(int val)
		{
			ID = val;
			InitConnections();
		};

		void AddConnection(Node* n, int weight)
		{
			if (Capacity != MAX)
			{
				Connections[Capacity] = new Connection(n, weight);
				Capacity++;
			}
		};

		void GetTable(Table* Table)
		{

			for (int i = 0; i < Capacity; i++)
			{
				Table[i].NodeID = Connections[i]->GetID();
				Table[i].Weight = Connections[i]->GetWeight();
			}
		}

		// This is a static approach
		int GetNumberOfConnections() { return Capacity; }

	private:
		int Capacity = 0; // Number of connections to this node
		class Connection
		{
			public:
				Connection(Node* n, int weight) { Neighbor = n; Weight = weight; }
				Connection() { Neighbor = 0; Weight = 0; }

				int GetWeight() { return Weight; }

				int GetID() { return Neighbor->ID; }
			private:
				Node* Neighbor;
				int Weight;
		};

		// List of connections connected to the port
		Connection* Connections[MAX];
		void InitConnections() { for (int i = 0; i < MAX; i++) { Connections[i] = new Connection(); } }

		// This object will contain the shortest distance from source and previous vertex 
		Connection* Path = new Connection();
};


inline void Dijkstra(Node Nodes[], int size, int source, int destination)
{
	const int ArrSize = 7;
	int VisitedNodeIDs[Node::MAX * ArrSize]; // Static hard coded, solution make a dynamic array class but let's not worry about that right now 

	int WorkingIndex = source;
	for (int i = 0; i < size; i++)
	{
		Node WorkingNode = Nodes[WorkingIndex];
		for (int k = 0; k < WorkingNode.GetNumberOfConnections(); k++)
		{

		}
	}
	
}
