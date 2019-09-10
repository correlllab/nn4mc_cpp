#include "generator/file_creator.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    std::string path = "test_file";
    std::cout << path << std::endl; 
    FileCreator file_creator(path);
    std::cout << file_creator.checkExists() << std::endl;
    file_creator.createNewDirectory();
    std::cout << "FileCreator: end of file creator example " << std::endl;
	return 0;
}
