#ifndef _NEURAL_NETWORK_H__
#define _NEURAL_NETWORK_H__

#include<iostream>
#include<vector>
#include "Weights.h"
#include "Layer.h"

struct LayerEdge
{
  LayerNode* l;

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

  LaerNode()
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
    LayerNode* findNode(string ID);
  public:
    NeuralNetwork();
    ~NeuralNetwork();

    void addLayer(Layer* layer);
    void addEdge(strind ID_1, string ID_2);

    void BFSPrint();
    void DFSPrint();
};

#endif
