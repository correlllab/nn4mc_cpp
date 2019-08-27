#include "generator/file_creator.h"
#include <iostream>
#include <string>

int main()
{
    std::cout << std::getenv("DUMP_PATH_ROOT")<<std::endl;
    std::string path = "generator_test_v2";
    std::cout << path << std::endl; 
    FileCreator file_creator(path);
    std::cout << file_creator.checkExists() << std::endl;;
    std::cout << "FileCreator: end of file creator example " << std::endl;
	return 0;
}
