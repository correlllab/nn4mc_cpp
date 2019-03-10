#include "../include/NeuralNetwork.h"

int main()
{
  NeuralNetwork net;

  Layer l1("this");
  Layer l2("thing");
  Layer l3("is");
  Layer l4("called");
  Layer l5("a");
  Layer l6("graph");

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

  net.addEdge(&l1,&l3);
  net.addEdge(&l1,&l6);

  net.BFSPrint();
  std::cout << std::endl;
  net.DFSPrint();
}
