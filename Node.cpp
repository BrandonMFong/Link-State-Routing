

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
};

// I need a list of the nodes in a structure that is easy to add and remove
class NodeList
{
	public:
		NodeList() {};

		void Add(Node* item)
		{
			// If the list is empty 
			if (List == nullptr)
			{
				List = new Item(item);
			}
			else
			{
				List->Add(item);
			}
		}
	private:
		class Item
		{
			public:

				// Constructors 
				Item() {}

				// init list
				Item(Node* C)
				{
					Left = nullptr; Right = nullptr; Current = C;
					//DeterminePosition();
				}

				// adding to an already existing list
				// Do I need this? 
				Item(Node* C, Item* L, Item* R)
				{
					Left = L; Right = R; Current = C;
					//DeterminePosition();
				}

				bool isFirst(){ return (Left == nullptr) ? true : false; }
				bool isLast(){ return (Right == nullptr) ? true : false; }

				// Adds at the end of the list
				void Add(Node* item)
				{
					Item* temp = this;

					// Get the last in the list 
					while (temp->Right != nullptr) temp = temp->Right;

					temp->Right = new Item(item); // Create the new object and put its address in the list 
					temp->Right->Left = temp;
				}
				
			private:
				/*bool isFirst = false;
				bool isLast = false;*/
				Item* Left = nullptr;
				Item* Right = nullptr;
				Node* Current = nullptr;
				/*void DeterminePosition()
				{
					isFirst = (Left == nullptr) ? true : false;
					isLast = (Right == nullptr) ? true : false;
				}*/
		};

		Item* List = nullptr; // this should be the first item in the list 
};

inline void Dijkstra(Node Nodes[])
{
}
