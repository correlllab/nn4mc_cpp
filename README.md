# nn4mp: Neural Networks for Microcontrollers
### Started by Sarah Aguasvivas (January 2019)

In multiple areas of our research, we become interested in online estimation through regression or classification. Specifically, we want to be able to flash a microcontroller with our trained neural network model (which we trained offline, in another computer) with a code that is easy to use and reusable.  


This package is intended to be used in any microcontroller programmed in C after the neural network has been trained in a machine with Keras, Tensorflow, etc. and the parameters are saved. This enables the microcontroller to make online predictions. It is compatible with any freeRTOS code, the ESP32 and Arduino systems.

`example_usage` contains `testing.c`, which shows a sample case of usage of the neural network. Right now the usage is a little rough around the edges but the dream is that we can just call those functions just like we declare keras layer objects. 

If you are interested in running that example case, you can use the following

```
gcc -g testing.c
```

That will allow you to compile and even print partial results by typing `a.out` for debugging purposes. 

This repo is a generalization of the repository created by Dana Hughes https://github.com/danathughes/esp32_neural_net 

