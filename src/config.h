#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include "json.hpp"
#include "Node.h"
#include <string.h>
#include <sstream>
using json = nlohmann::json;
using namespace std;

int jsonToInt(json in)
{
	stringstream str(in.dump());
	int num = 0;
	str >> num;
	return num;
}

NodeList JsonToNodeList(string filename)
{
	std::ifstream i(filename);
	json j;
	i >> j;
	NodeList Nodes = NodeList();

	cout << "Reading Network config...\n\n";

	// init router 
	for (auto& N : j["Nodes"])
	{
		// the same code as range for
		for (auto& n : N["Node"].items())
		{
			if (n.key() == "ID")
			{
				Node node(n.value());
				Nodes.Add(node);
				cout << "	Including Node " << node.ID << endl;
			}
		}
	}

	cout << "	Establishing connections" << endl;

	// establish connections
	for (auto& N : j["Nodes"])
	{
		// the same code as range for
		int ID;
		json Connections;
		bool CaughtID = false, CaughtConnections = false;
		for (auto& n : N["Node"].items())
		{
			if (n.key() == "ID")
			{
				cout << "		Caught ID" << endl;
				ID = n.value();
				CaughtID = true;
			}
			if (n.key() == "Connections") // how do I determine the ID? 
			{
				cout << "		Caught Connections" << endl;
				Connections = n;
				CaughtConnections = true;
			}
		}

		// Process the information
		if (CaughtID && CaughtConnections)
		{
			cout << "		Connection for node " << ID << endl;
			for (auto& Connection : Connections["Connections"].items())
			{
				json Conn = Connection.value();
				cout << "			Caught connection, ID is " << Conn["ID"] << ", and its weight " << Conn["Weight"] << endl;

				// Get ID
				int numID = jsonToInt(Conn["ID"]);

				// Get Weight
				int numWeight = jsonToInt(Conn["Weight"]);

				Nodes.GetNodeByID(ID)->AddConnection(Nodes.GetNodeByID(numID), numWeight);
			}
		}
	}

	return Nodes;
}
#endif