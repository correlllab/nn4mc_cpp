#include <iostream>
#include "generator/file_creator.h"
#include <sstream>
/*
FileCreator::FileCreator()
{
    std::cout << "file_creator.cpp: zero argument constructor" << std::endl;
}
*/

FileCreator::FileCreator(std::string path_string){
    boost::filesystem::path path{path_string};
    boost_path = path;
}

FileCreator::~FileCreator()
{

}

bool FileCreator::checkExists(){
    // checks if exists wrt to directory that is building
    // won't be a problem cause will make environment variable
    // with root of nn4mc
    
    return (bool)boost::filesystem::exists(boost_path);
}

void FileCreator::createDirectory(){

    if (this->checkExists() == true){
        std::cout << "file existed so created new file!" <<std::endl;
        int i=0;
        while (boost::filesystem::exists(boost_path)){
            i++;
            std::stringstream ss;
            ss<< boost_path.string() << "_" << i;
            boost_path = ss.str();
        }
    }
    boost::filesystem::create_directory(boost_path);                
    
}




