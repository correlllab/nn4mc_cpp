Tutorials
==========


Getting Started
=================

The first step after the installation is done is to create a build folder and build our first example to make sure you are setup! Go to the root `nn4mc` folder and create a `build/` folder.

::

 cd path/to/nn4mc
 mkdir build
 cd build

Now, you are ready to make your first example project. We recommend to add your hdf5 files under the `data/` folder to keep your version of the repository clean. However, you are free to store that file wherever you'd like (inside or outside the folder, as long as you can provide the path). We added some sample hdf5 files under `data/`. To test your installation do the following:

::

 cd build
 cmake ..
 make

The sample code will generate many executables under `build/`, the one we recommend testing because it covers all the necessary components is called `generator_test_file`. Run it by typing in the command line:

::

 ./generator_test_file

If this works, it will generate code in the root folder with the file name specified. By default, this filename is called: `example_out/` and is located at the root folder of `nn4mc`. 

The code contained in the generated file is ready to be dragged and dropped into an IDE, for example, the Arduino IDE as seen below. 


Using your HDF5 File
=====================

The example code contained under `examples/generator_test_actual_file.cpp` contains all the necessary components to create your C files. Here is an example on how to use this library on hdf5 files. In this example we generate the code necessary to implement lenet in a microcontroller:

::

 #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include "parser/HDF5Parser.h"
 #include "datastructures/tensor.h"
 #include "generator/weight_generator.h"
 #include "datastructures/weights.h"
 #include "generator/layer_generator.h"
 #include "generator/code_generator.h"

 #include "datastructures/Layer.h"
 #include "datastructures/NeuralNetwork.h"

 int main()
 {

    HDF5Parser P("../data/lenet.hdf5");
    P.parse();
    NeuralNetwork* nn = P.get_neural_network();
    nn->BFS();
    nn->reset();

    CodeGenerator* code_gen = new CodeGenerator(nn, "../templates/esp32", "../example_out");
    code_gen->generate();
    code_gen->dump();

    delete nn;
    return 0;
 }

In the future, we expect to remove some of these necessary lines of code in a way that the end-user does not have to declare so many pointers. 


Using Generated Code 
======================

Arduino
--------

First, open a new sketch in Arduino, then, open all the files that were generated using nn4mc in Arduino.

The following code is an example of what it would take to get `nn4mc` to work on your Arduino code. In this example, we allocate and send to the neural network an input of ones. This code looks as follows:

First, create the prototypes for the functions that we will be using from `nn4mc`:

::

  void buildLayers();
  float * fwdNN(float* data);


In the setup function after we begin our serial port, we call the function `buildLayers()`. This function will initialize all the layers and create the necessary components for our feed forward. 

:: 

  void setup() {
      Serial.begin(115200); // feel free to adjust this as desired
      buildLayers();

  }

In the loop function, after we collect our input, we call `fwdNN(input)`, which is the function that will output a pointer. This pointer will contain the output data from the neural network. You can access this output as a regular array, for example, output[0] indicates the first element in the output layer and so forth. In the following example, we have a neural network whose input layer is is of size `(None, 10, 1)` and output size `(3)`.

::

  void loop() {
        
        float * input= (float*)malloc(10*sizeof(float));
        for (int i=0; i<10; i++) input[i] = 1.0;

        float * output;
        
        output = fwdNN(input);

        for (int i=0; i<3; i++) {
            Serial.print(output[i]);
            Serial.print(" ");
        }
        
        Serial.println();

        free(output); // output needs to be freed for best performance. Please do not free input.  
        delay(1);
      }
