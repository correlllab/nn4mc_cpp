#include "generator/file_creator.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    std::string path = "generator_test_v2";
    std::cout << path << std::endl; 
    FileCreator file_creator(path);
    std::cout << file_creator.checkExists() << std::endl;;
    std::cout << "FileCreator: end of file creator example " << std::endl;
	return 0;
}
