#ifndef _NEURAL_NETWORK_H__
#define _NEURAL_NETWORK_H__

#include <iostream>
#include <vector>
#include "weights.h"
#include "Layer.h"
#include <string>
#include <list>

struct LayerEdge;
struct LayerNode;
class nn_iterator;

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
  LayerNode& operator=(const LayerNode& a){
      // Copying edges:
      std::copy(a.edges.begin(), a.edges.end(), back_inserter(edges));
      visited= a.visited;
      layer = a.layer;
  }
};

class NeuralNetwork
{
  typedef nn_iterator iterator;

  private:
    friend class nn_iterator;
  public:
    std::vector<LayerNode*> layers; //All layers in graph
    std::vector<LayerNode*> input; //Input layers for graph.

    std::vector<LayerNode*> nodes_ord; //Ordered list of nodes.
    std::vector<Weight*> weights; //Weights

    LayerNode* findNode(std::string ID); //Finds node in graph
    void DFS(LayerNode* start); //Call to recursive DFS

    int idx_n; //Current index for nodes_ord.
    int idx_w; //Current index for weights.

  public:
    NeuralNetwork(); //Constructor
    ~NeuralNetwork(); //Destructor

    void addLayer(Layer* layer); //Adds a layer
    void addEdge(Layer* start, Layer* end); //Adds an edge from start to end.

    void reset(); //Resets indices and visited boolean.
    void BFS(); //BFS traversal and builds ordered layer and weight vector
    void DFSPrint(); //Recursive DFS

    LayerNode* getNextNode(); //Returns next layer
    Weight* getNextWeight(); //Returns next weight
    iterator begin();
    iterator end();

    void fixedToFloat(int width, int size);
};

class nn_iterator
{
  public:
    typedef LayerNode value_type;
    typedef LayerNode& reference;
    typedef LayerNode* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef void difference_type; //Doesnt really make sense in this case to have anything else.

    nn_iterator(NeuralNetwork* nn_, LayerNode* node_) : nn(nn_), node(node_) {}
    nn_iterator() {}

    nn_iterator& operator++(); //Prefix, increment return.
    nn_iterator operator++(int dummy); //Postfix, return increment.
    reference operator*() {return *node;} //Needs to be diferent
    // pointer operator->() {return nn;} //Needs to be diferent
    nn_iterator& operator=(const nn_iterator &rhs) {nn = rhs.nn; node = rhs.node; return *this;}
    bool operator==(const nn_iterator &rhs) {return (nn == rhs.nn && node == rhs.node);}
    bool operator!=(const nn_iterator &rhs) {return (nn != rhs.nn || node != rhs.node);}

  private:
    NeuralNetwork* nn;
    LayerNode* node //Start
    std::list<LayerNode*> nodeList; //Node queue
};

nn_iterator operator++() //Prefix
{
  std::vector<LayerEdge>::iterator i;

  if(node == nn->input[0]) //Only if this is the beginning.
  {
    for(int i=0; i<nn->input.size(); i++) //Add the input layers first
    {
      input[i]->visited = true;
      nodeList.push_back(input[i]);
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
    return this;
  }
  else
  {
    node = NULL;
    return this;
  }
}

nn_iterator operator++(int dummy) //Postfix, not sure this is right.
{
  nn_iterator copy = *this; //Confused about this because of the way assignment operator works.
  std::vector<LayerEdge>::iterator i;

  if(node == nn->input[0]) //Only if this is the beginning.
  {
    for(int i=0; i<nn->input.size(); i++) //Add the input layers first
    {
      input[i]->visited = true;
      nodeList.push_back(input[i]);
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
    return copy;
  }
  else
  {
    node = NULL;
    return copy;
  }
}

#endif
