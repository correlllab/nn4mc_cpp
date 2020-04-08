 %module example
 %{
    extern void buildLayers();
    extern float * fwdNN(float* data);
    #include "activation_func.h"
    #include "neural_network.h"
 %}

extern void buildLayers();
extern float * fwdNN(float* data);






