#include "neural_network.h"
#include "neural_network_params.h"
#include <stdlib.h>
#include "esp_log.h"

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))
#define TAG "neural network. c: "

#define exp(x) 1.0 + x + x*x/2.0 + x*x*x/6.0 + x*x*x*x/24.0+ x*x*x*x*x/120.0 + x*x*x*x*x*x/720.0 + x*x*x*x*x*x*x/5040.0
#define sigmoid(x) 1.0/(1.0 + exp(-1.0*x)) 

void set_conv1D(struct Conv1D * LL, int input_sh1, int input_sh2, int kernel_size, int filters){
    // These will emulate the constructors
    struct Conv1D L; 
    L= *LL;
    L.input_sh1= input_sh1;
    L.input_sh2= input_sh2;
    L.kernel_size = kernel_size;
    L.filters= filters;
    num_layers++;
    L.h = (volatile float**)malloc((int)(L.input_sh1-L.kernel_size+1) * sizeof(volatile float*));
    for (int i=0; i< (int)(L.input_sh1- L.kernel_size+1); i++){
        L.h[i] = (volatile float*)malloc(L.filters * sizeof(volatile float));
    } 
    L.output_shape= (int)(L.input_sh1-L.kernel_size+1);
    *LL = L;
}

void fwd_conv1D(struct Conv1D * LL, int a, int bb, int c, const float W[a][bb][c], const float * b, volatile float ** window){
    struct Conv1D L;
    L= *LL;

     for (int i=0; i<(int)(L.input_sh1-L.kernel_size+1); i++){
        for (int j=0; j<(int)L.filters; j++){
            L.h[i][j]= b[j];
            for (int x=0; x<(int)L.kernel_size; x++){
                for (int y=0; y<bb; y++){
                    L.h[i][j] += W[x][y][j] * window[i+x][y];
                }
            }
         }
      }
     for (int i=0; i< L.input_sh1 ; i++){
         float * currentFloatPtr= window[i];
         free(currentFloatPtr);
     }
    *LL = L;

}

void set_maxpool1D(struct MaxPooling1D * LL, int input_sh1,int input_sh2, int pool_size, int strides){
   // These will emulate the constructors
    
    struct MaxPooling1D L;
    L= *LL;
    L.pool_size = pool_size;
    L.strides= strides;
    L.input_sh1 = input_sh1;
    L.input_sh2= input_sh2;
    num_layers++;
    L.h= malloc((int)L.input_sh1 * sizeof(float*));
    for (int i=0; i<(int)L.input_sh1; i++){
        L.h[i]= malloc((int)L.pool_size * sizeof(float));
    }
    L.output_shape= L.pool_size;
    L.input_sh1= L.input_sh1;
    L.input_sh2= L.pool_size;
    num_layers++;
    *LL = L;
}

void fwd_maxpool1D(struct MaxPooling1D * LL, int a, int bb, int c, const float W[a][bb][c], const float *b, float ** window){
    struct MaxPooling1D L;
    L= *LL;
    for (int i=0; i< L.input_sh1; i++){
        for (int j=0; j<L.pool_size; j++){
            L.h[i][j] = max(window[2*i][j], window[2*i+1][j]);
        }
    }
    for (int i=0; i< L.input_sh1 ; i++){
         float * currentFloatPtr= window[i];
         free(currentFloatPtr);
     }    
    *LL = L;
}

void set_dense(struct Dense * LL, int input_size, int output_size, char activation){
   // These will emulate the constructor
   
   struct Dense L;
   L= *LL;
   L.input_size= input_size;
   L.output_size= output_size;
   L.activation = activation;
   num_layers++;
   L.h= malloc((int)L.output_size * sizeof (float));
   *LL = L;
}

void fwd_dense(struct Dense * LL, int a, int bb, const float W[a][bb], const float * b, float window[a]){
    struct Dense L;
    L= *LL;

    for (int i=0; i<L.output_size; i++){
        L.h[i] = b[i];
        for (int j=0; j<L.input_size; j++){
            L.h[i]+= W[j][i] * window[j]; 
        }
        if (L.activation=='r'){
            L.h[i]= max(L.h[i], 0.0);
        } 
    }
    free(window);
    *LL = L;
}

void setflatten2D1D(struct Flatten2D1D * FLATFLAT, int a, int b){
    struct Flatten2D1D FLAT; 
    FLAT = *FLATFLAT;
    FLAT.h= (float *)malloc(a*b*sizeof(float));
    FLAT.in_shape_0 = a; 
    FLAT.in_shape_1 = b;
    FLAT.output_size= a*b;
    *FLATFLAT= FLAT;
}

void flatten2D1D(struct Flatten2D1D * FLATFLAT, volatile float ** incoming){
    ESP_LOGI(TAG, "here1");
    struct Flatten2D1D FLAT;
    FLAT= *FLATFLAT;
    //num_layers++; //does the flatten count?
    if (FLAT.h==NULL){
        ESP_LOGI(TAG, "herehere");
        FLAT.h= malloc(FLAT.in_shape_0*FLAT.in_shape_1*sizeof(float));
    }
    //ESP_LOGI(TAG, "NULL? %d, in0= %d, in1=%d", FLAT.h==NULL, FLAT.in_shape_0, FLAT.in_shape_1);
    ESP_LOGI(TAG, "NULL? %d, in0= %d, in1=%d", FLAT.h==NULL, FLAT.in_shape_0, FLAT.in_shape_1);
    for (int i=0; i<FLAT.in_shape_0; i++){
        for (int j=0; j<FLAT.in_shape_1; j++){
            int idx= FLAT.in_shape_1*i+j;
            FLAT.h[idx] = (float)incoming[i][j];
        }
    }
    for (int i=0; i< FLAT.in_shape_0; i++){
        float * currentFloatPtr= incoming[i];
        free(currentFloatPtr);
    }
    *FLATFLAT= FLAT;
}


