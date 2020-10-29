#pragma once


#include <iostream>
#include <fstream>      // std::ifstream
#include "json.hpp" // Use when it is ready to be parameterized

#define Infinity 100

using namespace std;
using json = nlohmann::json;
using ifstream = std::ifstream;

class Node;

typedef struct Table // this could also be in the object 
{
	int NodeID, Weight;
};


static const int MaxNodesInNetwork = 7;
static const int MAX = 10; // Max connectin a node can have on a network 

inline bool operator==(const Node* x, const Node& y);
inline bool operator==(const Node* x, const Node& y);

class Node
{
	public:
		int ID;


		// Constructors
		Node();

		Node(int val);

		void AddConnection(Node* n, int weight);


		void GetTable(Table* Table);

		// This is a static approach
		int GetNumberOfConnections();

		Node* GetNodeConnectionById(int ID);

		void Copy(Node original);

		int GetWeightToNode(Node Node);

		void InitConnections();

	private:
		int Capacity = 0; // Number of connections to this node
		class Connection
		{
			public:
				Connection(Node* n, int weight);
				Connection();

				int GetWeight();

				int GetID();

				//Should be node instead of neighbor
				Node* GetNode();
			private:
				Node* Neighbor;
				int Weight;
		};

		// List of connections connected to the port
		Connection* Connections[MAX];
};

class Item
{
	public:

		// Constructors 
		Item();

		// init list
		Item(Node C);

		// adding to an already existing list
		// Do I need this? 
		Item(Node C, Item* L, Item* R);

		bool isFirst();
		bool isLast();

		// Get
		Item* GetRight();
		Item* GetLeft();
		Node GetNode();

		// Set
		void SetRight(Item* value);
		void SetLeft(Item* value);

		// Adds at the end of the list
		void Add(Node item);

	private:
		Item* Left = nullptr;
		Item* Right = nullptr;
		Node Current = *new Node();
};

// I need a list of the nodes in a structure that is easy to add and remove
// Outer layer should be able to read the list 
// Inner layer should only know how to organize
// the outer layer does not care how nodes are organized
class NodeList : private Item
{
	public:
		NodeList();

		void Add(Node item);

		//Get the node by index
		// 0 index is true 
		Node GetByIndex(int index);

		Node GetNodeByID(int ID);

		void RemoveNodeByID(int ID);

		// deal with this later 
		NodeList operator=(const NodeList&);

		// I think I need to actually calculate the size 
		int GetSize();

		void Copy(NodeList original);

		bool Contains(Node Node);

		/// <summary>
		/// Inserts 'insert' before 'before'
		/// </summary>
		/// <param name="insert"></param>
		/// <param name="NodeToBePushedUp"></param>
		void InsertBefore(Node insert, Node before);

		/// <summary>
		/// Prints the node list
		/// </summary>
		void PrintPath();

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

