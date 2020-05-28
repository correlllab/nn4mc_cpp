Guide for Devs
=================

Main Structure of the Code
--------------------------

``nn4mc`` is composed by the following modules:

:data_structures: Contains `Tensors`, `Weights`, `Layers` and `NeuralNetwork`.  
:parser: Parses an incoming file to output a `NeuralNetwork` object.
:code_generator: Takes in a `NeuralNetwork` object to generate files with C/C++ code.

data_structues/Tensor
----------------------

`Tensor` objects are mostly used in this work when we need to store large arrays, especially of the `float` or `double` variable types that occupy lots of space. What makes a `Tensor` special is that any matrix or array that is converted into a tensor becomes part of a large sequence of characters and this object type makes us capable of converting to and from said sequence of characters. For example, instead of having `float arr[3] = {1.000, 1.000, 1.000}` we have a `tensor` that under the hood stores our array into a slightly more complicated verion but similar to `"1.00001.0001.000"` . To declare a `Tensor` we need two things: A `std::vector<int>` that indicates the sizes of each dimension in the tensor. Then, to assign numerical values at specific points in a `Tensor`, we use a pointer to the tensor and the assignment operator. Here is an example of how to declare and populate a `Tensor`.

::
  
   std::vector<int> dimensions;
   dimensions.push_back(5);
   dimensions.push_back(2); // a 5x2 matrix 
   
   Tensor<double> T = Tensor<double>(dimensions);
   
   for(int i=0; i<dimensions[0]; i++)
     {
             for(int j=0; j<dimensions[1]; j++)
             {
                     T(i,j) = i*dimensions[1] + j;
             }
      }   
      

Data Structures
----------------

The `data_structures` module in `nn4mc` contains all the built-in data structures, such as weights, layers, tensors and neural networks.

Parser
--------

`Parser` is the first interface between the model file and `nn4mc` this is independent of `code_generator`, however, `code_generator` takes as input an object that may be generated using a `Parser`. It takes as input the file that contains the model and outputs a `NeuralNetwork` object with all the complete information.


Code Generator
-----------------

`code_generator` takes as input the `NeuralNetwork` object generated and populated using any of the `Parser` instances and outputs a set of C/C++ files with all the code that can execute the neural network operations.


data_structures/Weight
----------------------

`Weights` contain a single `Tensor`. Even though layers contain both weights and biases, these weights and biases are saved as instances of weight. This means that a layer will have two pointers to weight objects; one for the weights and one for the biases. `Weights` have a specific method that might come in handy and it is called `Weight::get_weight_tensor()`. This allows us to copy the values for the weight tensor.  


data_structures/Layer
---------------------

`Layers` are the most functional objects for neural networks. Different layer types will yield different outputs and will process differently the data, e.g. a fully connected (Dense) layer's output will be different from a convolutional layer output. To declare a new layer we just instantiate the name of the layer type because layer type objects derive from `Layer`, which is an abstract class. Currently, the layer type objects that can be instantiated are the following:

:Dense: This is a fully connected or dense layer. An MLP will have only Dense layers.
:Activation: Sometimes Keras users add activations as if they were independent layers. This accounts for when the user does that.
:Conv1D: Performs 1D convolutions for 1D signal processing. This object fills out all the required arguments needed for these layer types.
:Conv2D: Contains all the necessary components to perform 2D convolutions.
:MaxPooling1D: Contains all the necessary components to perform 1D maxpooling.
:MaxPooling2D: Contains all the necessary components to perform 2D maxpooling.
:Activation: Contains all the necessary components to perform activation layers as separate layers.
:Dropout: Contains all the necessary components to at least read dropout layers even though the feedforward process does not require any additional processing from the dropout part. 

In the future, we will add the following layer types:

:GRU: Will contain the necessary components to perform GRUs.
:LSTM: Will contain the necessary components to perform LSTMs.
:SimpleRNN: Will contain the necessary components to perform simple RNNs.

data_structures/NeuralNetwork
-----------------------------

`NeuralNetwork` is a directed graph that can be transversed using BFS. Each node of `NeuralNetwork` points at a layer type object and at a weight and bias tensor.


parser/HDF5Parser
-------------------

`HDF5Parser` takes as input an `.hdf5` file and extracts all the information to output a `NeuralNetwork` object with all of the necessary pieces filled out from the information in the file.  

parser/PickleParser
--------------------

`PickleParser` will soon be a capability in `nn4mc`. This will take as input a `.pth` file coming from PyTorch and will generate the same neural network that `HDF5Parser` exports.



