#include "datastructures/NeuralNetwork.h"
// #include "../include/datastructures/NeuralNetwork.h"
#include <iostream>

//Example usage for NeuralNetwork iterator.

int main()
{
  //First make a neuralnetwork and add some layers to it.

  NeuralNetwork nn;

  Layer* l1 = new InputLayer("input_1");
  Layer* l2 = new Conv1D("conv1D_1");
  Layer* l3 = new Conv1D("conv1D_2");
  Layer* l4 = new Dense("dense_1");
  Layer* l5 = new MaxPooling1D("pool_1");
  Layer* l6 = new Flatten("flat_1");

  nn.addLayer(l1);
  nn.addLayer(l2);
  nn.addLayer(l3);
  nn.addLayer(l4);
  nn.addLayer(l5);
  nn.addLayer(l6);

  nn.addEdge(l1,l2);
  nn.addEdge(l2,l3);
  nn.addEdge(l3,l4);
  nn.addEdge(l4,l5);
  nn.addEdge(l5,l6);

  //////////////////////////////////////////////////////

  //Now create an iterator

  NeuralNetwork::iterator i;
  NeuralNetwork::iterator j;

  i = nn.begin();
  j = nn.begin();

  if(i == j) std::cout << "They are equal." << std::endl;
  if(!(i != j)) std::cout << "They are not not equal." << std::endl;

  for(i = nn.begin(); i != nn.end(); i++)
  {
    std::cout << (*i).layer->identifier << std::endl;
  }

  std::cout << "Hey Hey Hey" << std::endl;

  delete l1;
  delete l2;
  delete l3;
  delete l4;
  delete l5;
  delete l6;
}
