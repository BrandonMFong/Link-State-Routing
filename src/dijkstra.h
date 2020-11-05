#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Node.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="Table"></param>
/// <param name="TableSize"></param>
/// <param name="SourceNodeID">The working node outside this function</param>
/// <param name="DestinationNodeIndex">index to the vector on the table </param>
/// <param name="TotalDistance"></param>
/// <returns></returns>
inline int GetDistance(struct Path Table[], int TableSize, int SourceNodeID, int DestinationNodeIndex, int TotalDistance)
{
	Path row = Table[DestinationNodeIndex];// current vertex 
	int Distance = TotalDistance + row.Vector.GetWeightToNode(*row.Vector.GetNodeConnectionById(SourceNodeID));

	// If ID is not 0
	if (SourceNodeID != 0)
	{
		// Go through the table to find the sourcenode's row and pass its index to the table
		for (int i = 0; i < TableSize; i++)
		{
			if ((Table[i].Vector.ID == SourceNodeID) && (Table[i].PreviousNode->ID != 0))
			{
				// Passing previous node of source node to SourceNodeID because we are assuming the sourcenode is a node we visited
				// Therefore it should already have a previousNode marked in the table array 
				Distance = GetDistance(Table, TableSize, Table[i].PreviousNode->ID, i, Distance);
			}
		}
	}
	return Distance;
}

// First print backwards
inline void PrintShortestPath(struct Path Table[], int size, int i)
{
	Path row = Table[i];
	cout << row.Vector.ID;
	if (row.PreviousNode->ID != 0) // If there is still more
	{
		for (int k = 0; k < size; k++)
		{
			if (Table[k].Vector.ID == row.PreviousNode->ID)
			{
				cout << " <- ";
				PrintShortestPath(Table, size, k);
			}
		}
	}
}

/// <summary>
/// Gets the path type var and puts the path in order in a nodelist object
/// </summary>
/// <param name="Table"></param>
/// <param name="size"></param>
/// <param name="SourceID"></param>
/// <param name="DestinationID"></param>
/// <returns></returns>
inline NodeList GetPathFromTable(struct Path Table[], int size, int SourceID, int DestinationID)
{
	// init list on result variable 
	// we want to reverse the order of the path tabel so we can print out the path from beginning to end
	// that order will be in here, result var
	// we need to have a method that inserts a node before an index in the list, i.e. InsertBefore()
	NodeList * result = new NodeList();
	Node* PreviousVertex = new Node();
	int i = 0;
	while (1)
	{
		for (i = 0; i < size; i++)
		{
			if (DestinationID == Table[i].Vector.ID)
			{
				result->InsertBefore(Table[i].Vector, *PreviousVertex); // this might cause issues
				*PreviousVertex = Table[i].Vector; 
				DestinationID = Table[i].PreviousNode->ID;
				break;
			}
		}
		if (SourceID == Table[i].Vector.ID)break; // if we are at the end 
	}
	return *result;
}

// Should Source/Destination be the index values for the array or node IDs? 
// Should be Node IDs 
/// <summary>
/// should return path table
/// </summary>
inline NodeList Dijkstra(NodeList Nodes, int SourceID, int Destination)
{
	NodeList* VisitedNodes = new NodeList();  // Visited Node array 
	NodeList* UnvisitedNodes = new NodeList(); // Unvisited Node array 
	Path PathTable[MAX]; // using ten to be safe 
	int NumNodes = Nodes.GetSize();

	// Init table values with all nodes from nodelist param 
	for (int i = 0; i < NumNodes; i++)
	{
		PathTable[i].Vector = Nodes.GetByIndex(i);
		if (PathTable[i].Vector.ID == SourceID) { PathTable[i].ShortestDistance = 0; }// if current node entree, then put 0 distance 
		else { PathTable[i].ShortestDistance = Infinity; }// init infinity
		PathTable[i].PreviousNode = new Node();
	}

	UnvisitedNodes->Copy(Nodes); // Copy all nodes to the array that tracks unvisited nodes

	int WorkingNodeID = SourceID; // Init Working Node ID

	int DestinationIndex = MAX;

	// Traverse the connections  
	while (1)
	{
		Node WorkingNode = *UnvisitedNodes->GetNodeByID(WorkingNodeID); // Get working node by ID

		cout << "\nSize of Visited array: " << VisitedNodes->GetSize() << endl;
		cout << "Size of Unvisited array: " << UnvisitedNodes->GetSize() << endl;
		cout << "Current working node: " << WorkingNode.ID << endl;

		/* Calculate shortest path */

		// Get working node's connection table
		Table* WorkingNodeTable = new Table[MAX];
		WorkingNode.GetTable(WorkingNodeTable);
		int WorkingTableNumConnections = WorkingNode.GetNumberOfConnections();


		Path ShorterPath = { *(new Node()), Infinity, nullptr };  // Keep a the closer node because we will visit the closest node next
		// Go through each entry of the node's table and compare with working node's connections
		for (int k = 0; k < NumNodes; k++)// table
		{
			for (int i = 0; i < WorkingTableNumConnections; i++)// connection
			{
				// if row is a connection on working node AND we haven't visited this, calculate distance from source to this node
				// k holds the num row of the working node's connection in the table
				if ((PathTable[k].Vector.ID == WorkingNodeTable[i].NodeID) && !VisitedNodes->Contains(PathTable[k].Vector))// connection in table
				{
					// remember k has the current index to the current row we are looking at

					int TempDistance = GetDistance(PathTable, NumNodes, WorkingNode.ID, k, 0);

					if (PathTable[k].ShortestDistance > TempDistance) // if we found a new short path through current working node
					{
						PathTable[k].ShortestDistance = TempDistance;

						// Instead of giving the address to the pointer, give it the value
						*PathTable[k].PreviousNode = *Nodes.GetNodeByID(WorkingNodeID); // we visited this vector by Working node
					}
					break;
				}
			}

			// Since we are going through the whole table regardless, figure out the next node to evaluate
			// if we didn't visit this yet AND it has the shortest distance from the start vertex in the table (ie shortest distance from the start vertex)
			// also make sure we aren't considering the distance from the source to the source
			if ((PathTable[k].ShortestDistance > 0) && (PathTable[k].Vector.ID != WorkingNodeID))
			{
				if (!VisitedNodes->Contains(PathTable[k].Vector) && (PathTable[k].ShortestDistance < ShorterPath.ShortestDistance))
				{
					ShorterPath = PathTable[k];
					DestinationIndex = k; // Save this row index in case this is the final node 
				}
			}
		}

		VisitedNodes->Add(*UnvisitedNodes->GetNodeByID(WorkingNodeID)); // Mark visited
		UnvisitedNodes->RemoveNodeByID(WorkingNodeID);

		// if the next node to evaluate is the destination, stop algorithm 
		if (Destination == ShorterPath.Vector.ID) break;
		else WorkingNodeID = ShorterPath.Vector.ID; // Get next node to look at 
	}

	NodeList SourceToDestination = GetPathFromTable(PathTable, NumNodes, SourceID, Destination); // Destination ID? 

	return SourceToDestination;
}

#endif