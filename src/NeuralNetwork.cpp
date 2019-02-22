#include "../include/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{

}
NeuralNetwork::~NeuralNetwork()
{
  std::vector<LayerNode>::iterator i;
  std::vector<LayerEdge>::iterator j;
  LayerNode* lPtr;
  LayerEdge* ePtr;

  for(i=layers.begin(); i!=layers.end(); i++)
  {
    for(j=i->edges.begin(); j!=i->edges.end(); j++)
    {
      ePtr = &(*j);
      delete ePtr;
    }
    lPtr = &(*i);
    delete lPtr;
  }
}

void NeuralNetwork::setUnvisited()
{
  std::vector<LayerNode>::iterator i;

  for(i=layers.begin(); i!=layers.end(); i++)
  {
    i->visited = false;
  }
}

LayerNode* NeuralNetwork::findNode(std::string ID)
{
  std::vector<LayerNode>::iterator i;

  for(i=layers.begin(); i!=layers.end(); i++)
  {
    if(i->layer->identifier == ID)
      return &(*i);
  }

  return NULL;
}

void NeuralNetwork::addLayer(Layer* input_layer)
{
  LayerNode* newLayer = new LayerNode;
  newLayer->layer = input_layer;

  layers.push_back(*newLayer);
}
void NeuralNetwork::addEdge(std::string ID_1, std::string ID_2)
{
  LayerNode* layer_1 = findNode(ID_1);
  LayerNode* layer_2 = findNode(ID_2);

  LayerEdge* newEdge = new LayerEdge;

  newEdge->l = layer_2;

  layer_1->edges.push_back(*newEdge);
}

void NeuralNetwork::BFSPrint()
{
  setUnvisited();

  LayerNode* start = &(layers.front()); //Should change to input
  std::list<LayerNode*> nodeList;
  std::vector<LayerEdge>::iterator i;

  start->visited = true;
  nodeList.push_back(start);

  std::cout << start->layer->identifier << std::endl;

  while(!nodeList.empty())
  {
    start=nodeList.front();
    nodeList.pop_front();

    for(i=start->edges.begin(); i!=start->edges.end(); i++)
    {
      if(i->l->visited == false)
      {
        i->l->visited = true;
        nodeList.push_back(i->l);

        std::cout << i->l->layer->identifier<<std::endl;
      }
    }
  }

}

void NeuralNetwork::DFSPrint(LayerNode* start)
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
      DFSPrint(i->l);
  }
}
