#include "generator/file_creator.h"

using namespace H5;

int main(int argc, char** argv)
{
	const H5std_string FILE_NAME("blah.h5");	
	H5File file(FILE_NAME, H5F_ACC_RDONLY);
	return 0;
}
