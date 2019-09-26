
#include "neural_network.h"

void buildLayers(){

   
        conv1d_1 = malloc(sizeof(struct Conv1D));  
        conv1d_1 = buildConv1D(&conv1d_1[0][0][0], conv1d_1, 4, 1, 197, 8, 8);

        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1[0][0], dense_1, 1576, 20, 0x06);

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2[0][0], dense_2, 20, 10, 0xB);

        dense_3 = malloc(sizeof(struct Dense));
        dense_3 = buildDense(&dense_3[0][0], dense_3, 10, 2, 0xB);
 

}


float * fwdNN(float* data)
{

   
        data = fwdConv1D(conv1d_1, data);

        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdDense(dense_3, data);
 

    return data;
}

float* data_flatten(float *data, int dims)
{
  if (dims == 2)
  {
    int size = sizeof(data)/sizeof(data[0][0]);
    int c = sizeof(data[0])/sizeof(data[0][0]);
    int r = size/c;
    float* flat = new float[size];

    for(int i=0; i<r; i++)
    {
      for(int j=0; j<c; j++)
      {
        flat[i*j] = data[i][j];
      }
    }
  }
  else if (dims == 3)
  {
    int size = sizeof(array2d)/sizeof(array2d[0][0][0]);
    int d = sizeof(array2d[0][0])/sizeof(array2d[0][0][0]);
    int c = sizeof(array2d[0])/sizeof(array2d[0][0]);
    int r = size/c/d;
    float* flat = new float[size];

    for(int i=0; i<r; i++)
    {
      for(int j=0; j<c; j++)
      {
        for(int k=0; k<d; k++)
        {
          flat[i*j*k] = data[i][j][k];
        }
      }
    }
  }

  return flat;
}

