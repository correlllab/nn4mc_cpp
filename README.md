# nn4mp: Neural Networks for Microcontrollers
### Started by Sarah Aguasvivas (January 2019)



This repo is a generalization of the neural network created by Dana Hughes https://github.com/danathughes/esp32_neural_net 

In multiple areas of our research, we become interested in online estimation through regression or classification. Specifically, we want to be able to flash a microcontroller with our trained neural network model (which we trained offline, in another computer) with a code that is easy to use and reusable.  


This package is intended to be used in any microcontroller programmed in C after the neural network has been trained in a machine with Keras, Tensorflow, etc. and the parameters are saved. This enables the microcontroller to make online predictions. It is compatible with any freeRTOS code, the ESP32 and Arduino systems.

`example_usage` contains `testing.c`, which shows a sample case of usage of the neural network. Right now the usage is a little rough around the edges but the dream is that we can just call those functions just like we declare keras layer objects. 

If you are interested in running that example case, you can use the following

```
gcc testing.c
```

That will allow you to compile and even print partial results by typing `./a.out` for debugging purposes.


#### REPO TREE:
``` bash .
|-- neural_network.c
|-- neural_network_params.h
|-- neural_network.h
|-- data
    |-- loadModel.py
    |-- nn_file.hdf5
|-- example_usage
    |-- testing.c

```


`neural_network.c`: Here the functions and operations with the neural network objects are performed. <br/>
`neural_network.h`: Here the structures and main characteristics of the neural network are defined.<br/>
`neural_network_params.h`: Here the parameters learned in a desktop machine are declared.<br/>
`data/`: This file contains functions and scripts to help generate  `neural_network_params.h`.<br/>
`example_usage/`: This file contains a test case, which is currently a neural network that Radhen wrote in Keras.

### Usage:



At the moment, we have to declare the structures and the input sizes of the data coming in the layer. To declare a new layer, you can use the following format:

```
struct LayerType Layer;
```
Currently, this package has support for layer types of the following classes:

`Conv1D`: 1D convolution 

`MaxPooling1D`: 1D max pooling layer

`Flatten2D1D`: It is not a layer per se, but prepares data coming out of a convolution or maxpooling to be used by a dense layer. 

`Dense`: dense or MLP layer

#### Conv1D:

Contains the following attributes: `kernel_size`, `filters`, `input_sh1`, `input_sh2`. Some hidden attributes that will be modified automatically are `output_shape` and `**h`, which do not have to be introduced by the user. 

To setup these layer objects, we call:
```
set_conv1D(
struct Conv1D * Layer, //on call, send a reference to the layer i.e. &L1
int input_sh1, // specify the size of the input data (first dimension)
int input_sh2,  // specify the size of the input data (second dimension)
int kernel_size, // size of the kernel
int filters); // number of filters
```
To feed forward this layer one has to call the following function:

```
fwd_conv1D(
struct Conv1D * Layer, //on call, send a reference to the layer struct i.e. &L1
float **window); //the array from input layer or past layers and not the reference
```

Something important to keep in mind, on the conceptual sense is that this layer will not be performing 2D convolutions on 2D data, if your input array is 2D, it will apply the convolution row- or column wise without having any 2D extension. It is to be noted at the moment one designs the neural network on another computer (e.g. Keras, Tensorflow, etc).

#### MaxPooling1D:

Contains the following attributes: `pool_size`, `input_shape`, `strides`, `input_sh1`, `input_sh2`. Two hidden attributes are `output_shape` and `**h`.

To setup these layer objects, we call:

```
set_maxpool1D(
struct MaxPooling1D * Layer, // again, send the reference to the layer 
int input_sh1,
int input_sh2,
int pool_size,
int strides
);
```

To feed forward this layer, we call the following function:

```
fwd_maxpool1D(
struct MaxPooling1D * Layer,
float **window
);
```

#### Dense:

Contains the following attributes: `input_size`, `output_size`, `activation`. It also contains a hidden attribute `*h`. 

To setup a dense layer, we call:

```
set_dense(
struct Dense * L, //send a reference to the corresponding layer
int input_size, 
int output_size,
char activation,
);
```

For `activation`, we currently have support for ReLU and linear actication. Therefore, if you would like to declare this layer as a ReLu layer, set `activation=r`, if you would like to use a linear activation, set `activation=n`, if you would like to use the sigmoid function use `activation=’s’`, for inverse tangent, set `activation=’t’`. We are currently working on a custom activation function support. 

To feed forward your layer set:

```
fwd_dense(
struct Dense * Layer,
float *window // make sure this window is already flattened, meaning a 1D array
);
```

#### Flatten2D1D:

This is not a layer on its own, however, it is very handy at the moment we would like data to go from a 2D array to a 1D array. This layer only has the following function:

```
flatten2D1D(
struct Flatten2D1D * Layer, 
float ** window // 2D array that we are interested in flattening
);
```

### Example Usage Case

Let us say we have trained the following neural network architecture on another platform and learned the weights and biases:

```
Input: An array of ADC signals of size (50, 2)
1D Convolution with kernel size of 4, and 8 filters
1D Convolution with kernel size of 4 and 8 filters
Dense layer with output of 64 neurons and ReLU activation
Dense layer with output of 32 neurons and ReLU activation
Dense layer with output of 16 neurons and ReLU activation
Dense layer with output of 8 neurons and ReLU activation
Dense layer with output of 3 neurons and linear activation
```

The corresponding code that will feed forward your input, which is assumed to be a preallocated array of size 50x2 is:


```
struct Conv1D L1; 
 set_conv1D(&L1, WINDOW_SIZE, NUM_ADC, 4, 8); 
 fwd_conv1D(&L1, 4, 2, 8, W_0, b_0, window);
 
 struct Conv1D L2; 
 set_conv1D(&L2, 47, 8, 4, 8); 
 fwd_conv1D(&L2, 4, 8, 8, W_1, b_1, L1.h);
 
 struct Flatten2D1D FL; 
 flatten2D1D(&FL, 44, 8, L2.h);
 
 struct Dense D1; 
 set_dense(&D1, FL.output_size, 64, 'r');
 fwd_dense(&D1, D1.input_size, D1.output_size, W_2, b_2, FL.h);
 
 struct Dense D2; 
 set_dense(&D2, D1.output_size, 32, 'r');
 fwd_dense(&D2, D2.input_size, D2.output_size, W_3, b_3, D1.h);
 
 struct Dense D3; 
 set_dense(&D3, D2.output_size, 16, 'r');
 fwd_dense(&D3, D3.input_size, D3.output_size, W_4, b_4, D2.h);
 
 struct Dense D4; 
 set_dense(&D4, D3.output_size, 8, 'r');
 fwd_dense(&D4, D4.input_size, D4.output_size, W_5, b_5, D3.h);
 
 struct Dense D5; 
 set_dense(&D5, D4.output_size, 3, 'l');
 fwd_dense(&D5, D5.input_size, D5.output_size, W_6, b_6, D4.h);
```

If you would like to access the results from this neural network, just refer to the `h` array in the last layer of the neural network. For example:

```
 printf("Prediction:");
 for (int i=0; i<D5.output_size; i++){
     printf("%.6f  ", D5.h[i]);
 }
 printf("\n");
```

![Alt text](/docs/uml/nn4mp_network_diagram.pdf?raw=true "UML Diagram")
