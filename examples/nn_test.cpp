#include "../include/NeuralNetwork.h"

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

  Layer* l1 = new Input();
  l1->identifier = input_1;
  Layer* l2 = new Conv1D("Hi");
  l2->identifier = "conv1D_1";
  Layer* l3 = new Conv1D();
  l3->identifier = conv1D_2;
  Layer* l4 = new Dense();
  l4->identifier = dense_1;
  Layer* l5 = new MaxPooling1D();
  l5->identifier = pool_1;
  Layer* l6 = new Flatten();
  l6->identifier = flat_1;

  net.addLayer(&l1);
  net.addLayer(&l2);
  net.addLayer(&l3);
  net.addLayer(&l4);
  net.addLayer(&l5);
  net.addLayer(&l6);

  net.addEdge(&l1,&l2);
  net.addEdge(&l2,&l3);
  net.addEdge(&l3,&l4);
  net.addEdge(&l4,&l5);
  net.addEdge(&l5,&l6);

  net.BFS();
  //std::cout << std::endl;
  //net.DFSPrint();
  LayerNode* temp = net.getNextLayer();

  while(temp!=NULL)
  {
    std::cout << temp->layer->identifier << std::endl;
    temp = net.getNextLayer();
  }
}
