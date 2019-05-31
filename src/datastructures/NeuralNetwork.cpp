#include "datastructures/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
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

  if(input_layer->isInput() == true)
    this->input.push_back(newLayer);

  layers.push_back(newLayer);
}

void NeuralNetwork::addEdge(Layer* start, Layer* end)
{
  LayerNode* layer_1 = findNode(start->identifier);
  LayerNode* layer_2 = findNode(end->identifier);

  LayerEdge* newEdge = new LayerEdge;

  newEdge->l = layer_2;

  layer_1->edges.push_back(*newEdge);
  layer_2->inputs.push_back(layer_1);
}

nn_iterator NeuralNetwork::begin() //Returns and iterator to first input layer.
{
  return nn_iterator(this,input[0]);
}

nn_iterator NeuralNetwork::end() //Returns iterator with layernode as null to indicate end.
{
  return nn_iterator(this, NULL);
}

// Width is total word length (i.e. 32 bits)
// Size is number of bits needed for integer part
void NeuralNetwork::fixedToFloat(int width, int size)
{
  int mask = (1<<width-size)-1; //Not necessary here but needed in generation.
  int fraction = 1<<width-size;

  BFS();
  Weight* w;
  Tensor<double>* t;
  w = getNextWeight();

  float pt;
  while(w != NULL)
  {
    t = w->get_weight_tensor();

    for(int i = 0; i<t->num_elements; i++)
    {
      (*t)[i] = int(t->value_at(i))<<(width-size);
    }

    w = getNextWeight();
  }
}

/////////////////////////////////////////////////////////////

nn_iterator& nn_iterator::operator++() //Prefix
{
  std::vector<LayerEdge>::iterator i;

  if(node == nn->input[0]) //Only if this is the beginning.
  {
    for(int i=0; i<nn->input.size(); i++) //Add the input layers first
    {
      nn->input[i]->visited = true;
      nodeList.push_back(nn->input[i]);
    }
  }

  if(!nodeList.empty())
  {
    node = nodeList.front();
    nodeList.pop_front();

    // this->nodes_ord.push_back(start); //Adding node order data.
    // this->weights.push_back(start->layer->w); //Adding weight data.
    // this->weights.push_back(start->layer->b); //Adding bias data.

    for(i=node->edges.begin(); i!=node->edges.end(); i++)
    {
      if(i->l->visited == false)
      {
        i->l->visited = true;
        nodeList.push_back(i->l);

        //std::cout << i->l->layer->identifier<<std::endl;
      }
    }
    return *this;
  }
  else
  {
    node = NULL;
    return *this;
  }
}

nn_iterator nn_iterator::operator++(int dummy) //Postfix, not sure this is right.
{
  nn_iterator copy = *this; //Confused about this because of the way assignment operator works.
  std::vector<LayerEdge>::iterator i;

  if(node == nn->input[0]) //Only if this is the beginning.
  {
    for(int i=1; i<nn->input.size(); i++) //Add the input layers first
    {
      nn->input[i]->visited = true;
      nodeList.push_back(nn->input[i]);
    }
  }

  if(!nodeList.empty())
  {
    // node = nodeList.front();
    nodeList.pop_front();

    // this->nodes_ord.push_back(start); //Adding node order data.
    // this->weights.push_back(start->layer->w); //Adding weight data.
    // this->weights.push_back(start->layer->b); //Adding bias data.

    for(i=node->edges.begin(); i!=node->edges.end(); i++)
    {
      if(i->l->visited == false)
      {
        i->l->visited = true;
        nodeList.push_back(i->l);

        //std::cout << i->l->layer->identifier<<std::endl;
      }
    }
    node = nodeList.front();
    // std::cout << node->layer->identifier << std::endl;
    return copy;
  }
  else
  {
    node = NULL;
    return copy;
  }
}
