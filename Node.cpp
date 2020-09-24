

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
		InitConnect();
	};

	Node(int val)
	{
		ID = val;
		InitConnect();
	};

	int GetCapacity() { return Capacity; }

	void AddConnection(Node* n, int weight)
	{
		if (Capacity != MAX)
		{
			Connect[Capacity] = new Connection(n, weight);
			Capacity++;
		}
	};

	void GetTable(Table* Table)
	{

		for (int i = 0; i < Capacity; i++)
		{
			Table[i].NodeID = Connect[i]->GetID();
			Table[i].Weight = Connect[i]->GetWeight();
		}
	}

	// This is a static approach
	int GetNumberOfConnections() { return Capacity; }

private:
	int Capacity = 0;
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

	Connection* Connect[MAX];

	void InitConnect() { for (int i = 0; i < MAX; i++) { Connect[i] = new Connection(); } }
};
