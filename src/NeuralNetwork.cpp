#include "../include/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
  idx_n = idx_w = 0;
}
NeuralNetwork::~NeuralNetwork()
{
  LayerNode* del;

  while(!layers.empty())
  {
    del = layers.back();
    layers.pop_back();
    delete del;
  }
}

void NeuralNetwork::setUnvisited()
{
  std::vector<LayerNode*>::iterator i;

  for(i=layers.begin(); i!=layers.end(); i++)
  {
    (*i)->visited = false;
  }

  idx_n = 0;
  idx_w = 0;
}

LayerNode* NeuralNetwork::findNode(std::string ID)
{
  std::vector<LayerNode*>::iterator i;

  for(i=layers.begin(); i!=layers.end(); i++)
  {
    if((*i)->layer->identifier == ID)
      return *i;
  }

  return NULL;
}

void NeuralNetwork::addLayer(Layer* input_layer)
{
  LayerNode* newLayer = new LayerNode;
  newLayer->layer = input_layer;

  layers.push_back(newLayer);
}

void NeuralNetwork::addEdge(Layer* l1, Layer* l2)
{
  LayerNode* layer_1 = findNode(l1->identifier);
  LayerNode* layer_2 = findNode(l2->identifier);

  LayerEdge* newEdge = new LayerEdge;

  newEdge->l = layer_2;

  layer_1->edges.push_back(*newEdge);
  layer_2->inputs.push_back(layer_1);
}

void NeuralNetwork::BFS()
{
  setUnvisited();

  LayerNode* start = layers.front(); //Should change to input
  std::list<LayerNode*> nodeList;
  std::vector<LayerEdge>::iterator i;

  start->visited = true;
  nodeList.push_back(start);

  //std::cout << start->layer->identifier << std::endl;

  while(!nodeList.empty())
  {
    start=nodeList.front();
    nodeList.pop_front();

    nodes_ord.push_back(start); //Adding node order data.
    //weights.push_back(start->layer->w); //Adding weight data.

    for(i=start->edges.begin(); i!=start->edges.end(); i++)
    {
      if(i->l->visited == false)
      {
        i->l->visited = true;
        nodeList.push_back(i->l);

        //std::cout << i->l->layer->identifier<<std::endl;
      }
    }
  }
  nodes_ord.push_back(NULL);
  //weights.push_back(NULL);
}

void NeuralNetwork::DFS(LayerNode* start)
{
  if(!(start->visited))
  {
    std::cout << start->layer->identifier<<std::endl;
    start->visited = true;
  }

  std::vector<LayerEdge>::iterator i;

  for(i=start->edges.begin(); i!=start->edges.end(); i++)
  {
    if(!i->l->visited)
      DFS(i->l);
  }
}

void NeuralNetwork::DFSPrint()
{
  setUnvisited();
  LayerNode* start = layers.front(); //Should change to input

  DFS(start);
}

LayerNode* NeuralNetwork::getNextLayer()
{
  if(nodes_ord[idx_n] != NULL)
    return nodes_ord[idx_n++];
  else
    return nodes_ord[idx_n];
}

Weights* NeuralNetwork::getNextWeight()
{
  if(nodes_ord[idx_w] != NULL)
    return weights[idx_w++];
  else
    return weights[idx_w];
}
