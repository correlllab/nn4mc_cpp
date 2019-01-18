#include <stdio.h>
#include "../neural_network.h"
#include "../neural_network.c"

int main(){

// This will feed forward the neural newtork. 
// First, we need to declare the structures 
// for each layer. 

float window[50][2]= {{1, 1}, {1, 1}, {1,1}, {1, 1}, {1, 1},{1, 1}, {1, 1}, {1,1}, {1, 1},{ 1, 1 },{1, 1}, {1,     1}, {1,1}, {1, 1}, {1, 1},{1, 1},{ 1, 1 }, {1,1}, {1, 1},{ 1, 1 },{1, 1}, {1, 1}, {1,1},{ 1, 1 }, {1, 1}, 
{1, 1}, {1, 1}, {1,1}, {1, 1}, {1, 1},{1, 1}, {1, 1}, {1,1}, {1, 1},{ 1, 1 },{1, 1}, {1, 1},   {1,1}, {1, 1}, {1, 1},{1, 1},{ 1, 1 }, {1,1}, {1, 1},{ 1, 1 },{1, 1}, {1, 1}, {1,1},{ 1, 1 }, {1, 1}};

struct Conv1D L1; 
set_conv1D(&L1, WINDOW_SIZE, NUM_ADC, 4, 8); 
fwd_conv1D(&L1, 4, 2, 8, W_0, b_0, L1.input_sh1, L1.input_sh2, window);

struct Conv1D L2; 
set_conv1D(&L2, 47, 8, 4, 8); 
fwd_conv1D(&L2, 4, 8, 8, W_1, b_1, 47, 8, L1.h);

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
set_dense(&D5, D4.output_size, 3, 'n');
fwd_dense(&D5, D5.input_size, D5.output_size, W_6, b_6, D4.h);


printf("Prediction:");
for (int i=0; i<D5.output_size; i++){
    printf("%.6f  ", D5.h[i]);
}
printf("\n");
// should be [[ 0.01106095  0.02823588 -1.213638   ]] from python implementation

return 0;
}
