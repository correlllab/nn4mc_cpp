#include "datastructures/tensor.h"
#include <iostream>
#include <vector>

/** SIMPLE EXAMPLE
**/
int main(int argc, char** argv)
{
	std::cout << "Tensor class example" << std::endl;

	std::cout << "Example 1:  A 2x3 Matrix" << std::endl;

	// Create the Tensor with dimensionality 2x3
	std::vector<unsigned int> shape1 = std::vector<unsigned int>({2,3});
	Tensor<int> matrix = Tensor<int>(shape1);
	// Assign values equal to the index
	for(int i=0; i<shape1[0]; i++)
	{
		for(int j=0; j<shape1[1]; j++)
		{
			matrix(i,j) = i*shape1[1] + j;
		}
	}

	// Print it out!
	std::cout << "Resulting Matrix: " << std::endl;
	for(int i=0; i<shape1[0]; i++)
	{
		if(i==0)	std::cout << "[  ";
		else		std::cout << "   ";


		for(int j=0; j<shape1[1]; j++)
		{
			std::cout << matrix(i,j) << "  ";
		}

		if(i==shape1[0]-1)	std::cout << "]";
		std::cout << std::endl;
	}


	// Uncomment this to try accessing a bad index
//	std::cout << matrix(1,6);

	std::cout << "Example 2:  A 2x3x4x5 Tensor" << std::endl;

	// Create the Tensor with dimensionality 2x3
	std::vector<unsigned int> shape2 = std::vector<unsigned int>({2,3,4,5});

	Tensor<int> tensor = Tensor<int>(shape2);
	// Assign values equal to the index
	for(int i=0; i<shape2[0]; i++)
	{
		for(int j=0; j<shape2[1]; j++)
		{
			for(int k=0; k<shape2[2]; k++)
			{
				for(int l=0; l<shape2[3]; l++)
				{
					tensor(i,j,k,l) = i*shape2[1]*shape2[2]*shape2[3] + j*shape2[2]*shape2[3] + k*shape2[3] + l;
				}
			}
		}
	}

	// Print it out!
	std::cout << "Resulting Matrix: " << std::endl;

	for(int i=0; i<shape2[0]; i++)
	{
		if(i==0)	std::cout << "[";
		else		std::cout << " ";
		
		for(int j=0; j<shape2[1]; j++)
		{
			if(j==0)	std::cout << "[";
			else		std::cout << " ";			

			for(int k=0; k<shape2[2]; k++)
			{
				if(k==0)	std::cout << "[";
				else		std::cout << " ";
				
				for(int l=0; l<shape2[3]; l++)
				{
					if(l==0)	std::cout << "[";
					else		std::cout << " ";

					std::cout << tensor(i,j,k,l);

					if(l==shape2[3]-1)	std::cout << "]";
					else			std::cout << " ";

					if(k != shape2[2]-1 && l==shape2[3]-1)	std::cout << std::endl;
				}

				if(k==shape2[2]-1)	std::cout << "]";
				else			std::cout << " ";

				if(j != shape2[1]-1 && k==shape2[2]-1)		std::cout << std::endl;
			}

			if(j==shape2[1]-1)	std::cout << "]";
			else			std::cout << " ";

			if(i != shape2[0] - 1 && j==shape2[1]-1)			std::cout << std::endl;
		}

		if(i==shape2[0]-1)	std::cout << "]" << std::endl;
		else			std::cout << " ";
	}
	
}
