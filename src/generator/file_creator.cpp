#include <iostream>
#include "generator/file_creator.h"
#include <sstream>
#include <string>

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

void FileCreator::createNewDirectory(){

    if (this->checkExists() == true){
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

void FileCreator::create_codegen_file_tree(){

    boost::filesystem::create_directory(boost_path);
    boost::filesystem::create_directory(boost_path / "include");
    boost::filesystem::create_directory(boost_path / "src");
    boost::filesystem::create_directory(boost_path / "include" / "layers");
    boost::filesystem::create_directory(boost_path / "/src" / "layers");

}
