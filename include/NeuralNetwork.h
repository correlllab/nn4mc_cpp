#ifndef _NEURAL_NETWORK_H__
#define _NEURAL_NETWORK_H__

#include <iostream>
#include <vector>
#include "Weights.h"
#include "Layer.h"
#include <string>
#include <list>

struct LayerNode;

struct LayerEdge
{
  struct LayerNode* l;

  LayerEdge()
  {
    l=NULL;
  }
};


struct LayerNode
{
  Layer* layer;
  std::vector<LayerEdge> edges;
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
    std::vector<LayerNode*> layers;
    std::vector<LayerNode> input;

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
