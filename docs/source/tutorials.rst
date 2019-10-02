Tutorials
==========


Using nn4mc in Arduino:
=========================

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
