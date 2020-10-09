

#include <iostream>
#include <fstream>      // std::ifstream
#include "json.hpp" // Use when it is ready to be parameterized

// Priority is to establish the algorithm then do the configuration 

using namespace std;
using json = nlohmann::json;
using ifstream = std::ifstream;

typedef struct Table
{
	int NodeID, Weight;
};

static const int MaxNodesInNetwork = 7;
static const int MAX = 10; // Max connectin a node can have on a network 

class Node
{
	public:
		int ID;


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
// Outer layer should be able to read the list 
// Inner layer should only know how to organize
// the outer layer does not care how nodes are organized
class NodeList
{
	public:
		NodeList() {};

		void Add(Node* item)
		{
			// If the list is empty 
			if (List == nullptr)List = new Item(item);
			else List->Add(item);
		}

		//Get the node by index
		// 0 index is true 
		Node GetByIndex(int index)
		{
			if (GetSize() >= index)
			{
				Item* temp = List;
				for (int i = 0; i < index; i++)
				{
					temp = temp->GetRight();
				}
				return *temp->GetNode();
			}
		}

		Node GetNodeByID(int ID)
		{
			Node* results = new Node(); // return value 
			Item* temp = List; // temp 

			for (int i = 0; i < GetSize(); i++)
			{
				if (temp->GetNode()->ID == ID) { results = temp->GetNode(); break; }
				else { temp = temp->GetRight(); }
			}

			return *results;
		}

		void RemoveNodeByID(int ID)
		{
			Node* results = new Node(); // return value 
			Item* temp = List; // temp 

			for (int i = 0; i < GetSize(); i++)
			{
				// If I found the item with the correct node id, then take that out of the list and close it
				// I need to remove the item from memory
				if (temp->GetNode()->ID == ID) 
				{ 
					// I am wondering if there is a more efficient way to determine if the temp var is the first or last

					// Removing item pointed by temp 
					// If the neighbors of temp are not null, then get that var and rewrite their node pointers
					// if there is only one
					if ((temp->GetLeft() == nullptr) && (temp->GetRight() == nullptr))
					{
						delete temp;
						break; 
					}
					// The case where the deleted node is the first item and I need to reset the item 
					else if (temp->GetLeft() == nullptr)
					{
						List = temp->GetRight();
						// Remove current node 
						delete temp;
						break;
					}
					// If the node to delete is the last one, then I need to set the right point of the n-1 node to null, where n is the size of this array 
					else if (temp->GetRight() == nullptr)
					{
						temp->GetLeft()->SetRight(nullptr);
						// Remove current node 
						delete temp;
						break;
					}
					else
					{
						temp->GetLeft()->SetRight(temp->GetRight());
						temp->GetRight()->SetLeft(temp->GetLeft());
						// Remove current node 
						delete temp;
						break;
					}
				}
				else { temp = temp->GetRight(); }
			}
		}

		// deal with this later 
		NodeList operator=(const NodeList&)
		{
			NodeList temp = NodeList();
			temp.List = List;
			return temp;
		}

		// I think I need to actually calculate the size 
		int GetSize() 
		{ 
			int i = 0;
			if(List != nullptr) // if the list isn't empty, otherwise just return 0 without going through list
			{
				i = 1; // if List isn't empty, there is atleast one
				Item* temp = List;
				while (temp->GetRight() != nullptr) { i++; temp = temp->GetRight(); }
			}
			//size = i; // Reassigning 
			return i; 
		}

		void Copy(NodeList original)
		{
			Item* temp =  original.List;
			while (1)
			{
				Add(temp->GetNode());
				if (temp->GetRight() == nullptr) break;
				else { temp = temp->GetRight(); }
			}
		}

	private:
		//int size;
		class Item
		{
			public:

				// Constructors 
				Item() {}

				// Destructor 
				/*~Item()
				{
					delete[]Left;
					delete[]Right;
					delete[]Current;
				}*/

				// init list
				Item(Node* C)
				{
					Left = nullptr; Right = nullptr; Current = C;
				}

				// adding to an already existing list
				// Do I need this? 
				Item(Node* C, Item* L, Item* R)
				{
					Left = L; Right = R; Current = C;
				}

				bool isFirst(){ return (Left == nullptr) ? true : false; }
				bool isLast(){ return (Right == nullptr) ? true : false; }

				// Get
				Item* GetRight() { return Right; }
				Item* GetLeft() { return Left; }
				Node* GetNode() { return Current; }

				// Set
				void SetRight(Item* value) { Right = value; }
				void SetLeft(Item* value) { Left = value; }

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
				Item* Left = nullptr;
				Item* Right = nullptr;
				Node* Current = nullptr;
		};

	//protected:
		Item* List = nullptr; // this should be the first item in the list 
};

struct Path
{
	Node CurrentNode;
	int ShortestDistance;
	Node* PreviousNode;
};

// Should Source/Destination be the index values for the array or node IDs? 
// Should be Node IDs 
inline void Dijkstra(NodeList Nodes, int Source, int Destination)
{
	NodeList* VisitedNodes = new NodeList();  // Visited Node array 
	NodeList* UnvisitedNodes = new NodeList(); // Unvisited Node array 
	Path PathTable[MAX]; // using ten to be safe 

	// Init table values 
	for (int i = 0; i < Nodes.GetSize(); i++)
	{
		PathTable[i].CurrentNode = Nodes.GetByIndex(i).ID;
		PathTable[i].ShortestDistance = MAX + 1;// infinity is usually represented by the number of nodes+1
		PathTable[i].PreviousNode = nullptr;
	}

	UnvisitedNodes->Copy(Nodes); // Copy over nodes

	int CurrentNode = Source;
	while (1)
	{
		cout << "\nSize of Visited array: " << VisitedNodes->GetSize() << endl;
		cout << "Size of Unvisited array: " << UnvisitedNodes->GetSize() << endl;

		Node WorkingNode = UnvisitedNodes->GetNodeByID(CurrentNode); // Init working node to source 
		cout << "Current working node: " << WorkingNode.ID << endl;

		// Calculate shortest path 
		Table* WorkingNodeTable = new Table[MAX];
		WorkingNode.GetTable(WorkingNodeTable);

		// Go through each entry of the table
		for (int k = 0; k < (sizeof(PathTable) / sizeof(PathTable[0])); k++)
		{
			// for each entry in the table, go through each of the current node's connection and see if the lowest distance is recorded 
			// Recall number of table values should be the same size as the # of connection a node has 
			for (int i = 0; i < WorkingNode.GetNumberOfConnections(); i++)
			{
				// evaluate node connection and update table 
				// is the previous node of the table the node that was recently removed from the unvisited nodes? 
				// make sure we are working on the right nodes of both tables
				// catch if the weight is less than the working node
				// I also need to note the previous connection
				if ((PathTable[k].CurrentNode.ID == WorkingNodeTable[i].NodeID) && (PathTable[k].ShortestDistance > WorkingNodeTable[i].Weight))
				{

				}
			}
		}


		// Remove from unvisted and add to visited 
		VisitedNodes->Add(&UnvisitedNodes->GetNodeByID(CurrentNode));
		UnvisitedNodes->RemoveNodeByID(CurrentNode);
	}

}
