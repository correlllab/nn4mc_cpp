#include <stdio.h>
#include "../neural_network.h"
#include "../neural_network.c"

int main(){
    float input_window[2][6] = {{3.5, 3.5, 3.5, 3.5, 3.5, 3.5}, {2.5, 2.5, 2.5, 2.5, 2.5, 2.5}}; 
    
    struct Conv1D L1;
    printf("here\n"); 
    set_conv1D(L1, 6, 2, 2);
    
    return 0;
}
