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
    std::vector<LayerNode> layers;
    std::vector<LayerNode> input;

    void setUnvisited();
    LayerNode* findNode(std::string ID);

  public:
    NeuralNetwork();
    ~NeuralNetwork();

    void addLayer(Layer* layer);
    void addEdge(std::string ID_1, std::string ID_2);

    void BFSPrint();
    void DFSPrint(LayerNode* start);
};

#endif
