#include "../include/NeuralNetwork.h"

int main()
{
  NeuralNetwork net;

  Layer l1("cool");
  Layer l2("thing");
  Layer l3("this");
  Layer l4("is");
  Layer l5("bro");

  net.addLayer(&l1);
  net.addLayer(&l2);
  net.addLayer(&l3);
  net.addLayer(&l4);
  net.addLayer(&l5);

  net.addEdge("cool","thing");
  net.addEdge("thing","this");
  net.addEdge("this", "is");
  net.addEdge("is", "bro");

  net.BFSPrint();
  net.DFSPrint(&l1);
}
