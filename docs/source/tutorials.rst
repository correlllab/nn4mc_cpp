Tutorials
==========


Using nn4mc in Arduino:
=========================

First, open a new sketch in Arduino, then, open all the files that were generated using nn4mc in Arduino.

The following code is an example of what it would take to get `nn4mc` to work on your Arduino code. In this example, we allocate and send to the neural network an input of ones. This code looks as follows:

::

  void buildLayers();
  float * fwdNN(float* data);

  void setup() {
      Serial.begin(115200); // feel free to adjust this as desired
      buildLayers();

  }

  void loop() {
        // put your main code here, to run repeatedly:
        float * input= (float*)malloc(10*sizeof(float));
        float * output;
        for (int i=0; i<10; i++) input[i] = 1.0;

        unsigned long elapsed= millis();
        output = fwdNN(input);

        for (int i=0; i<3; i++) {
        Serial.print(output[i]);
        Serial.print(" ");

        }
        Serial.println();

        free(output); // output needs to be freed. It is the only variable that does. Please do not free input. 
        delay(1);
      }
