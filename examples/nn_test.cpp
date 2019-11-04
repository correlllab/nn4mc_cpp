#include "datastructures/NeuralNetwork.h"
#include <vector>

int main()
{
  //Example usage for simple neural net.
  NeuralNetwork net;

  // Input l1;
  // l1.identifier = input_1;
  // Conv1D l2;
  // l2.identifier = conv1D_1;
  // Conv1D l3;
  // l3.identifier = conv1D_2;
  // Dense l4;
  // l4.identifier = dense_1;
  // MaxPooling1D l5;
  // l5.identifier = pool_1;
  // Flatten l6;
  // l6.identifier = flat_1;

  Layer* l1 = new InputLayer("input_1");
  Layer* l2 = new Conv1D("conv1D_1");
  Layer* l3 = new Conv1D("conv1D_2");
  Layer* l4 = new Dense("dense_1");
  Layer* l5 = new MaxPooling1D("pool_1");
  Layer* l6 = new Flatten("flat_1");

  net.addLayer(l1);
  net.addLayer(l2);
  net.addLayer(l3);
  net.addLayer(l4);
  net.addLayer(l5);
  net.addLayer(l6);

  net.addEdge(l1,l2);
  net.addEdge(l2,l3);
  net.addEdge(l3,l4);
  net.addEdge(l4,l5);
  net.addEdge(l5,l6);

  //////////////////////////////////////////
  NeuralNetwork::iterator it;
  //Getting Weights
  net.reset();
  //No weights exist yet
  // std::cout << "WEIGHTS: " << std::endl;
  //
  // for(it = net.begin(); it != net.end(); it++)
  // {
  //   std::cout << it->layer->w->identifier << std::endl;
  // }

  //////////////////////////////////////////
  //Geting Layers
  net.reset();

  std::cout << "LAYERS: " << std::endl;

  for(it = net.begin(); it != net.end(); it++)
  {
    std::cout << it->layer->identifier << std::endl;
  }

  ///////////////////////////////////////////
  //Gettings Edges
  net.reset();

  std::cout << "EDGES: " << std::endl;

  std::vector<LayerNode*>::iterator i;
  for(it = net.begin(); it != net.end(); it++)
  {
    std::cout << "Inputs for " << it->layer->identifier << std::endl;
    for(i = it->inputs.begin(); i != it->inputs.end(); i++)
    {
      std::cout << (*i)->layer->identifier << std::endl;
    }
    std::cout << std::endl;
  }

  delete l1;
  delete l2;
  delete l3;
  delete l4;
  delete l5;
  delete l6;
}
