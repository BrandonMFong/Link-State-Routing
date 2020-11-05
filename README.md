# Link-State-Routing
Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph, which may represent, for example, road networks. It was conceived by computer scientist Edsger W. Dijkstra in 1956 and published three years later.

This project implements Dijkstra's algorithm in c++.  Assuming the network is already established and connections have already been broadcasted across the nodes, such that each node knows its neighbors and their connections. The algorithm will figure out the shortest path from Node A to Node B, where A and B are the node IDs.

## Setup
This program relies on an already established network which can be explicitly written out in confg\Net.json.
```
{
  "Nodes": [
    {
      "Node": {
        "ID": <ID OF THE SELECTED NODE>,
        "Connections": [
          {
            "ID": <ID OF THE NODE ITS CONNECTED TO>,
            "Weight": <THE WEIGHT TO THIS NODE>
          },
          {
            "ID": <ID OF THE NODE ITS CONNECTED TO>,
            "Weight": <THE WEIGHT TO THIS NODE>
          },
          ... // you can repeat this for as many connections this node has
        ]
      }
    },
    ... // you can repeat this for as many nodes in this network
  ]
}
```
# Test 1
## Graph 
![Graph](https://github.com/BrandonMFong/Link-State-Routing/blob/main/res/LinkGraph.png)

## Program 
![Dijkstra program](https://github.com/BrandonMFong/Link-State-Routing/blob/main/res/PathFrom3To4.PNG)

# Author
Brandon Fong
