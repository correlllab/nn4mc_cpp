#ifndef _NEURAL_NETWORK_H__
#define _NEURAL_NETWORK_H__

#include <iostream>
#include <vector>
#include "Weights.h"
#include "Layer.h"
#include <string>
#include <list>

struct LayerNode;

struct LayerEdge //Struct for edges in graph.
{
  struct LayerNode* l; //Pointer to the LayerNode endpoint of the edge.

  LayerEdge()
  {
    l=NULL;
  }
};


struct LayerNode //Struct for each node in the graph representing a layer in the nerual network.
{
  Layer* layer; //Pointer to layer object which contains all the metadata.
  std::vector<LayerEdge> edges; //Output edges of the node.
  std::vector<LayerNode*> inputs; //Input edges of the node.
  bool visited;

  LayerNode()
  {
    layer=NULL;
    visited=false;
  }
};

class NeuralNetwork
{
  private:
    std::vector<LayerNode*> layers; //All layers in graph
    std::vector<LayerNode> input; //Input layers for graph.
    std::list<LayerNode*> BFS; //List with BFS order of nodes.

    void setUnvisited();
    LayerNode* findNode(std::string ID);
    void DFS(LayerNode* start);

  public:
    NeuralNetwork();
    ~NeuralNetwork();

    void addLayer(Layer* layer);
    void addEdge(Layer* l1, Layer* l2);

    void BFSPrint();
    void DFSPrint();
};

#endif
