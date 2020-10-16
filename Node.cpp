

#include <iostream>
#include <fstream>      // std::ifstream
#include "json.hpp" // Use when it is ready to be parameterized

#define Infinity 100

using namespace std;
using json = nlohmann::json;
using ifstream = std::ifstream;

typedef struct Table // this could also be in the object 
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

		Node* GetNodeConnectionById(int ID)
		{
			for (int i = 0; i < Capacity; i++)
			{
				if (ID == Connections[i]->GetNode()->ID) return Connections[i]->GetNode();
			}
		}

		void Copy(Node original)
		{
			ID = original.ID; // Copy ID
			Table* OGTable = new Table[MAX];
			original.GetTable(OGTable);

			// Go through original's table and copy them over
			for (int i = 0; i < original.GetNumberOfConnections(); i++)
			{
				AddConnection(original.GetNodeConnectionById(OGTable[i].NodeID), OGTable[i].Weight);
			}
		}

		int GetWeightToNode(Node Node)
		{
			int weight = 0;
			for (int i = 0; i < Capacity; i++)
			{
				if (Connections[i]->GetNode() == Node)weight = Connections[i]->GetWeight();
			}
			return weight;
		}

	private:
		int Capacity = 0; // Number of connections to this node
		class Connection
		{
		public:
			Connection(Node* n, int weight) { Neighbor = n; Weight = weight; }
			Connection() { Neighbor = 0; Weight = 0; }

			int GetWeight() { return Weight; }

			int GetID() { return Neighbor->ID; }

			//Should be node instead of neighbor
			Node* GetNode() { return Neighbor; }
			private:
				Node* Neighbor;
				int Weight;
		};

		// List of connections connected to the port
		Connection* Connections[MAX];
		void InitConnections() { for (int i = 0; i < MAX; i++) { Connections[i] = new Connection(); } }

};

inline bool operator==(const Node& x, const Node& y)
{
	return x.ID == y.ID;
}
inline bool operator==(const Node * x, const Node& y)
{
	return x->ID == y.ID;
}

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
			else return *(new Node());
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

		bool Contains(Node Node)
		{
			bool found = false;
			Item* temp = List; // temp 

			for (int i = 0; i < GetSize(); i++)
			{
				if (temp->GetNode()->ID == Node.ID) { found = true; break; }
				else { temp = temp->GetRight(); }
			}
			return found;
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

// This will hold distance from Source to Vector
// Source node is external to this data 
struct Path
{
	Node Vector;
	int ShortestDistance;
	Node* PreviousNode;
};

/// <summary>
/// 
/// </summary>
/// <param name="Table"></param>
/// <param name="TableSize"></param>
/// <param name="SourceNodeID">The working node outside this function</param>
/// <param name="DestinationNodeIndex">index to the vector on the table </param>
/// <param name="TotalDistance"></param>
/// <returns></returns>
inline int GetDistance(struct Path Table[],int TableSize,int SourceNodeID,int DestinationNodeIndex,int TotalDistance)
{
	Path row = Table[DestinationNodeIndex];// current vertex 
	int Distance = TotalDistance 
		+ ((row.ShortestDistance == Infinity) ? 0 : row.ShortestDistance) 
		+ row.Vector.GetWeightToNode(*row.Vector.GetNodeConnectionById(SourceNodeID));

	// If ID is not 0
	if (SourceNodeID != 0)
	{
		// Go through the table to find the sourcenode's row and pass its index to the table
		for (int i = 0; i < TableSize; i++)
		{
			if (Table[i].Vector.ID == SourceNodeID)
			{
				Distance += GetDistance(Table, TableSize, Table[i].PreviousNode->ID, i, Distance); // TODO make sure this backtracks
			}
		}
	}
	return Distance;
}

//inline bool WasVisited(NodeList* VisitedNodes, struct Path Path)
//{
//	return false;
//}

// Should Source/Destination be the index values for the array or node IDs? 
// Should be Node IDs 
inline void Dijkstra(NodeList Nodes, int SourceID, int Destination)
{
	NodeList* VisitedNodes = new NodeList();  // Visited Node array 
	NodeList* UnvisitedNodes = new NodeList(); // Unvisited Node array 
	Path PathTable[MAX]; // using ten to be safe 
	int NumNodes = Nodes.GetSize();
	//Path* PathTablex = (struct Path*)malloc(Nodes.GetSize());

	// Init table values with all nodes from nodelist param 
	for (int i = 0; i < NumNodes; i++)
	{
		PathTable[i].Vector = Nodes.GetByIndex(i);
		if(PathTable[i].Vector.ID == SourceID){ PathTable[i].ShortestDistance = 0; }// if current node entree, then put 0 distance 
		else { PathTable[i].ShortestDistance = Infinity; }// init infinity
		PathTable[i].PreviousNode = new Node();
	}

	UnvisitedNodes->Copy(Nodes); // Copy all nodes to the array that tracks unvisited nodes

	int WorkingNodeID = SourceID; // Init Working Node ID

	// Traverse the connections  
	while (1)
	{
		Node WorkingNode = UnvisitedNodes->GetNodeByID(WorkingNodeID); // Get working node by ID

		cout << "\nSize of Visited array: " << VisitedNodes->GetSize() << endl;
		cout << "Size of Unvisited array: " << UnvisitedNodes->GetSize() << endl;
		cout << "Current working node: " << WorkingNode.ID << endl;

		/* Calculate shortest path */

		// Get working node's connection table
		Table* WorkingNodeTable = new Table[MAX];
		WorkingNode.GetTable(WorkingNodeTable);


		Path ShorterPath = {*(new Node()), Infinity, nullptr};  // Keep a the closer node because we will visit the closest node next
		// Go through each entry of the node's table and compare with working node's connections
		for (int k = 0; k < NumNodes; k++)// table
		{
			for (int i = 0; i < WorkingNode.GetNumberOfConnections(); i++)// connection
			{
				// if row is a connection on working node AND we haven't visited this, calculate distance from source to this node
				if ((PathTable[k].Vector.ID == WorkingNodeTable[i].NodeID) && !VisitedNodes->Contains(PathTable[k].Vector))// connection in table
				{
					// remember k has the current index to the current row we are looking at
					PathTable[k].ShortestDistance = GetDistance(PathTable,NumNodes,WorkingNode.ID,k,0); // Update distance from node to vector
					PathTable[k].PreviousNode = &Nodes.GetNodeByID(WorkingNodeID); // we visited this vector by Working node
					if (PathTable[k].ShortestDistance < ShorterPath.ShortestDistance) ShorterPath = PathTable[k];// Find the next node to evaluate
				}
			}
		}

		VisitedNodes->Add(&UnvisitedNodes->GetNodeByID(WorkingNodeID)); // Mark visited
		UnvisitedNodes->RemoveNodeByID(WorkingNodeID); 

		// if the next node to evaluate is the destination, stop algorithm 
		if (Destination == ShorterPath.Vector.ID) break;
		else WorkingNodeID = ShorterPath.Vector.ID; // Get next node to look at 
	}
}
