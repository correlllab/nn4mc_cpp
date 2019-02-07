/*****************
* tensor.cpp
*
* A lightweight tensor object, used to simplify storing and accessing tensors in C++
*
*/

#include "tensor.h"
#include <stdarg.h>
#include <iostream>


/*******************
* Tensor(int n, ...)
*
* The constructor takes a variable number of arguments, and populates 
* the dimensions array and offset array.
*/
template <class DataType, unsigned int NumDims>
Tensor<DataType, NumDims>::Tensor(unsigned int dimension_0, ...)
{
	// Initialize dimensions to 0, and offsets to be 1
	for(int i=0; i<NumDims; i++)
	{
		dimensions[i] = 0;
		offsets[i] = 1;
	}

	// Iterate through the passed arguments and assign to dimension
	// Assign the first dimension
	dimensions[0] = dimension_0;

	// Iterate through the remaining arguments
	va_list arguments;
	va_start(arguments, dimension_0);

	for(int idx=1; idx<NumDims; idx++)
	{
		dimensions[idx] = va_arg(arguments, unsigned int);
	}

	va_end(arguments);

	// Now calculate the offsets for each index - this will simply
	// be the product of the dimensionality of all indices following
	// the current one
	// Also, calculate the total number of elements - this will 
	// be the product of the dimensionality of all indices
	unsigned int offset = 1;
	num_elements = 1;

	for(int idx=NumDims-1; idx >= 0; idx--)
	{
		offsets[idx] = offset;
		offset *= dimensions[idx];

		num_elements *= dimensions[idx];

	}

	// Allocate the actual data array
	data = new DataType[num_elements];
}


/**********
* ~Tensor()
*
* The destructor simply cleans up the data allocated to storing the 
* actual tensor
*/
template <class DataType, unsigned int NumDims>
Tensor<DataType, NumDims>::~Tensor()
{
	// Delete the allocated memory and free up the memory, and set it
	// to NULL so it won't be de-allocated again by accident (somehow)
	delete[] data;
//	data = NULL;
}


/**********
* array_index(unsigned int, ...)
*
* Converts from the tensor indexing to the 1D index used by the actual data
*/
template <class DataType, unsigned int NumDims>
unsigned int Tensor<DataType, NumDims>::array_index(unsigned int idx_0, ...)
{
	// Start with the first index multiplied by the appropriate offset
	unsigned int index = idx_0 * offsets[0];

	// Iterate through the remaining index values
	va_list arguments;
	va_start(arguments, idx_0);

	for(int idx = 1; idx < NumDims; idx++)
	{
		index += offsets[idx] * va_arg(arguments, unsigned int);
	}

	va_end(arguments);

	return index;
}


/**********
* operator()(unsigned int, ...)
*
* Access the element at the given index
*/
template <class DataType, unsigned int NumDims>
DataType& Tensor<DataType, NumDims>::operator()(unsigned int idx_0, ...)
{
	// What is the array index to access?

	// Start with the first index multiplied by the appropriate offset
	unsigned int index = idx_0 * offsets[0];

	// Iterate through the remaining index values
	va_list arguments;
	va_start(arguments, idx_0);

	for(int idx = 1; idx < NumDims; idx++)
	{
		index += offsets[idx] * va_arg(arguments, unsigned int);

	}

	va_end(arguments);

	return data[index];
}


/**********
* operator()(unsigned int, ...) const
*
* Access the element at the given index
*/
template <class DataType, unsigned int NumDims>
DataType Tensor<DataType, NumDims>::operator()(unsigned int idx_0, ...) const
{
	// What is the array index to access?

	// Start with the first index multiplied by the appropriate offset
	unsigned int index = idx_0 * offsets[0];

	// Iterate through the remaining index values
	va_list arguments;
	va_start(arguments, idx_0);

	for(int idx = 1; idx < NumDims; idx++)
	{
		index += offsets[idx] * va_arg(arguments, unsigned int);
	}

	va_end(arguments);

	return data[index];
}
















/** SIMPLE EXAMPLE
**/
int main(int argc, char** argv)
{
	std::cout << "Tensor class example" << std::endl;

	std::cout << "Example 1:  A 2x3 Matrix" << std::endl;

	// Create the Tensor with dimensionality 2x3
	int NUM_ROWS = 2;
	int NUM_COLS = 3;

	Tensor<int, 2> matrix = Tensor<int, 2>(NUM_ROWS, NUM_COLS);
	// Assign values equal to the index
	for(int i=0; i<NUM_ROWS; i++)
	{
		for(int j=0; j<NUM_COLS; j++)
		{
			matrix(i,j) = i*NUM_COLS + j;
		}
	}

	// Print it out!
	std::cout << "Resulting Matrix: " << std::endl;
	for(int i=0; i<NUM_ROWS; i++)
	{
		if(i==0)	std::cout << "[  ";
		else		std::cout << "   ";


		for(int j=0; j<NUM_COLS; j++)
		{
			std::cout << matrix(i,j) << "  ";
		}

		if(i==NUM_ROWS-1)	std::cout << "]";
		std::cout << std::endl;
	}


	std::cout << "Example 2:  A 2x3x4x5 Tensor" << std::endl;

	// Create the Tensor with dimensionality 2x3
	int DIM_0 = 2;
	int DIM_1 = 3;
	int DIM_2 = 4;
	int DIM_3 = 5;

	Tensor<int, 4> tensor = Tensor<int, 4>(DIM_0, DIM_1, DIM_2, DIM_3);
	// Assign values equal to the index
	for(int i=0; i<DIM_0; i++)
	{
		for(int j=0; j<DIM_1; j++)
		{
			for(int k=0; k<DIM_2; k++)
			{
				for(int l=0; l<DIM_3; l++)
				{
					tensor(i,j,k,l) = i*DIM_1*DIM_2*DIM_3 + j*DIM_2*DIM_3 + k*DIM_3 + l;
				}
			}
		}
	}

	// Print it out!
	std::cout << "Resulting Matrix: " << std::endl;

	for(int i=0; i<DIM_0; i++)
	{
		if(i==0)	std::cout << "[";
		else		std::cout << " ";
		
		for(int j=0; j<DIM_1; j++)
		{
			if(j==0)	std::cout << "[";
			else		std::cout << " ";			

			for(int k=0; k<DIM_2; k++)
			{
				if(k==0)	std::cout << "[";
				else		std::cout << " ";
				
				for(int l=0; l<DIM_3; l++)
				{
					if(l==0)	std::cout << "[";
					else		std::cout << " ";

					std::cout << tensor(i,j,k,l);

					if(l==DIM_3-1)	std::cout << "]";
					else			std::cout << " ";

					if(k != DIM_2-1 && l==DIM_3-1)	std::cout << std::endl;
				}

				if(k==DIM_2-1)	std::cout << "]";
				else			std::cout << " ";

				if(j != DIM_1-1 && k==DIM_2-1)		std::cout << std::endl;
			}

			if(j==DIM_1-1)	std::cout << "]";
			else			std::cout << " ";

			if(i != DIM_0 - 1 && j==DIM_1-1)			std::cout << std::endl;
		}

		if(i==DIM_0-1)	std::cout << "]" << std::endl;
		else			std::cout << " ";
	}
}