#include "NeuralNetwork.h"

void NeuralNetwork::NeuralNetwork();
{

}
void NeuralNetwork::~NeuralNetwork()
{
  std::vector<LayerNode>::iterator i;
  std::vector<LayerEdge>::iterator j;

  for(i=layers.begin(); i!=layers.end(); i++)
  {
    for(j=i->edges.begin(); j!=i->edges.end(); j++)
    {
      delete j;
    }
    delete i;
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

LayerNode* NeuralNetwork::findNode(string ID)
{
  std::vector<LayerNode>::iterator i;

  for(i=Layers.begin(); i!=Layers.end(); i++)
  {
    if(i->layer->identifier == ID)
      return &(*i);
  }

  return NULL;
}

void NeuralNetwork::addLayer(Layer* layer)
{
  LayerNode* newLayer = new LayerNode;
  newLayer->l = layer;

  layers.push_back(*newLayer);
}
void NeuralNetwork::addEdge(string ID_1, string ID_2)
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

  LayerNode* start = &(input.front());

  std::list<LayerNode*> nodeList;
  std::vector<LayerEdge>::iterator i;

  start->visited = true;
  nodeList.push_back(start);

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

        cout << i->l->layer->identifier;
      }
    }
  }
}
void NeuralNetwork::DFSPrint(LayerNode* start)
{
  if(!LayerNode->visited)
  {
    cout << LayerNode->layer->identifier;
    LayerNode->visited = true;
  }

  std:vector<LayerEdge>::iterator i;

  for(i=start->edges.begin(); i!=start->edges.end(); i++)
  {
    if(!i->l->visited)
      DFSPrint(i->l);
  }
}
