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

class Node
{
	public:
		int ID;

		// Constructors
		Node() 
		{
			ID = 0;
			//Connect = 0;
		}; 

		Node(int val)
		{
			ID = val;
			//Connect = 0;
		};

		void AddConnection(Node * n, int distance)
		{
			if (Capacity != MaxConnections)
			{
				Connect = new Connection(n, distance);
				Capacity++;
			}
		};

		int GetDistance()
		{
			return Connect->GetDistance();
		}
	private:
		int Capacity = 0;
		int MaxConnections = 10;
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

		Connection * Connect = new Connection[MaxConnections];


};

int main()
{
	Node Node1(1); // Node 1
	Node Node2(2); // Node 2

	cout << "We have Node 1 with ID: " << Node1.ID << endl;
	cout << "We have Node 2 with ID: " << Node2.ID << endl;

	Node1.AddConnection(&Node2, 5);
	cout << "Node " << Node1.ID << " is connected to Node " << Node2.ID << " with a distance of " << Node1.GetDistance() << endl;

	Node2.AddConnection(&Node1, 5);
	cout << "Node " << Node2.ID << " is connected to Node " << Node1.ID << " with a distance of " << Node2.GetDistance() << endl;

}
