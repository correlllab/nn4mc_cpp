/**
* File Creator: This object's job is to
* create files given a path in a string. 
* It also provides a way to check for the 
* existence of a file.
*/

#include "boost/filesystem.hpp"
#include <string>

#ifndef __FILE_CREATOR_H__
#define __FILE_CREATOR_H__

class FileCreator
{
	private:
        boost::filesystem::path boost_path;

	public:
        FileCreator(std::string);
        ~FileCreator();

        bool checkExists(); 
        void createDirectory();
};

#endif
