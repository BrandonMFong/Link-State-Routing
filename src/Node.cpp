

#include <iostream>
#include <fstream>      // std::ifstream
#include "json.hpp" // Use when it is ready to be parameterized
#include "Node.h"


/* NODE CLASS START */
Node::Node()
{
	ID = 0;
	InitConnections();
};

Node::Node(int val)
{
	ID = val;
	InitConnections();
};

void Node::AddConnection(Node* n, int weight)
{
	if (Capacity != MAX)
	{
		Connections[Capacity] = new Connection(n, weight);
		Capacity++;
	}
};


void Node::GetTable(Table* Table)
{
	for (int i = 0; i < Capacity; i++)
	{
		Table[i].NodeID = Connections[i]->GetID();
		Table[i].Weight = Connections[i]->GetWeight();
	}
}

// This is a static approach
int Node::GetNumberOfConnections() { return Capacity; }

Node* Node::GetNodeConnectionById(int ID)
{
	for (int i = 0; i < Capacity; i++)
	{
		if (ID == Connections[i]->GetNode()->ID) return Connections[i]->GetNode();
	}
}

void Node::Copy(Node original)
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

int Node::GetWeightToNode(Node Node)
{
	int weight = 0;
	for (int i = 0; i < Capacity; i++)
	{
		if (Connections[i]->GetNode() == Node) weight = Connections[i]->GetWeight();
	}
	return weight;
}

Node::Connection::Connection(Node* n, int weight) { Neighbor = n; Weight = weight; }
Node::Connection::Connection() { Neighbor = 0; Weight = 0; }

int Node::Connection::GetWeight() { return Weight; }

int Node::Connection::GetID() { return Neighbor->ID; }

//Should be node instead of neighbor
Node* Node::Connection::GetNode() { return Neighbor; }
void Node::InitConnections() { for (int i = 0; i < MAX; i++) { Connections[i] = new Connection(); } }


inline bool operator==(const Node& x, const Node& y)
{
	return x.ID == y.ID;
}
inline bool operator==(const Node * x, const Node& y)
{
	return x->ID == y.ID;
}

/* NODE CLASS END */

/* NODELIST CLASS START */

// I need a list of the nodes in a structure that is easy to add and remove
// Outer layer should be able to read the list 
// Inner layer should only know how to organize
// the outer layer does not care how nodes are organized
NodeList::NodeList() {};

void NodeList::Add(Node item)
{
	// If the list is empty 
	if (List == nullptr)List = new Item(item);
	else List->Add(item);
}

//Get the node by index
// 0 index is true 
Node NodeList::GetByIndex(int index)
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

Node * NodeList::GetNodeByID(int ID)
{
	Node* results = new Node(); // return value 
	Item* temp = List; // temp 
	int size = GetSize();

	for (int i = 0; i < size; i++)
	{
		if (temp->GetNode()->ID == ID) { return temp->GetNode();}
		else { temp = temp->GetRight(); }
	}
	return results;
}

void NodeList::RemoveNodeByID(int ID)
{
	Node* results = new Node(); // return value 
	Item* temp = List; // temp 
	int size = GetSize();

	for (int i = 0; i < size; i++)
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
				List->SetLeft(nullptr);// Need to make sure list starts with a left null pointer
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
NodeList NodeList::operator=(const NodeList&)
{
	NodeList temp = NodeList();
	temp.List = List;
	return temp;
}

// I think I need to actually calculate the size 
int NodeList::GetSize()
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

void NodeList::Copy(NodeList original)
{
	Item* temp =  original.List;
	while (1)
	{
		Add(*temp->GetNode());
		if (temp->GetRight() == nullptr) break;
		else { temp = temp->GetRight(); }
	}
}

bool NodeList::Contains(Node Node)
{
	bool found = false;
	Item* temp = List; // temp 
	int size = GetSize();

	for (int i = 0; i < size; i++)
	{
		if (temp->GetNode()->ID == Node.ID) { found = true; break; }
		else { temp = temp->GetRight(); }
	}
	return found;
}

void NodeList::InsertBefore(Node insert, Node before)
{
	if (List == nullptr) List = new Item(insert); // If we are writing into an empty list 
	else
	{
		Item* temp = List; // temp 
		int size = GetSize();
		for (int i = 0; i < size; i++)
		{
			// I need to check the following
			// 1 - if the node I found is the first in the list.  Therefore I need to reset List pointer 
			// 2 - If the node I found is the last in the list or in the middle.  This would mean I need to rearrange pointers 
			// TODO implement 1 and 2
			if (temp->GetNode()->ID == before.ID)
			{
				Item* insertee = new Item(insert);
				if (temp->GetLeft() == nullptr) // case 1
				{
					temp->SetLeft(insertee); // Insert 
					Item* hold = temp;
					temp = temp->GetLeft(); // Switch to the 'before' node
					temp->SetLeft(nullptr); // initialize the first node on the list's left to null
					temp->SetRight(hold); // set its right pointer to the former first node

					List = insertee;
				}

				// in the case for dikjstra, we will never be in this scenario 
				else // case 2
				{
					Item* Right = temp;
					Item* Left = temp->GetLeft(); 

					// Put insert in the middle 
					Left->SetRight(insertee);
					Right->SetLeft(insertee);
					insertee->SetLeft(Left);
					insertee->SetRight(Right);

					List = insertee;
				}
				// recall we are inserting before, so we will never put anything after the last node for this method
				// that is reserved for insertafter
				break;
			}
			else temp = temp->GetRight();
		}
	}
}

void NodeList::PrintPath()
{
	int size = GetSize();
	for (int i = 0; i < size; i++)
	{
		cout << this->GetByIndex(i).ID;
		if (i != size-1) cout << " - > ";
	}
}
/* NODELIST CLASS END */

/* ITEM CLASS START */
Item::Item() {}

// init list
Item::Item(Node C)
{
	Left = nullptr; Right = nullptr; Current = C;
}

// adding to an already existing list
// Do I need this? 
Item::Item(Node C, Item* L, Item* R)
{
	Left = L; Right = R; Current = C;
}

bool Item::isFirst(){ return (Left == nullptr) ? true : false; }
bool Item::isLast(){ return (Right == nullptr) ? true : false; }

// Get
Item* Item::GetRight() { return Right; }
Item* Item::GetLeft() { return Left; }
Node * Item::GetNode() { return &Current; }

// Set
void Item::SetRight(Item* value) { Right = value; }
void Item::SetLeft(Item* value) { Left = value; }

// Adds at the end of the list
void Item::Add(Node item)
{
	Item* temp = this;

	// Get the last in the list 
	while (temp->Right != nullptr) temp = temp->Right;

	temp->Right = new Item(item); // Create the new object and put its address in the list 
	temp->Right->Left = temp;
}
/* ITEM CLASS END */